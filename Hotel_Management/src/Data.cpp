#include "Data.h"
#include <string>
#include <iostream>
#include <ctime>
#include <windows.h>

using namespace std;

void setColorData(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Data::Data(int _zi, int _luna, int _an) : zi(_zi), luna(_luna), an(_an) {}


bool Data::esteValida() const {
    if (luna < 1 || luna > 12) return false;
    int zileInLuna[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (luna == 2 && (an % 4 == 0 && (an % 100 != 0 || an % 400 == 0)) && zi == 29) return true;
    if (zi < 1 || zi > zileInLuna[luna]) return false;
    return true;
}

bool Data::operator<(const Data& other) const {
        if (an != other.an) return an < other.an;
        if (luna != other.luna) return luna < other.luna;
        return zi < other.zi;

}

string Data::toString() const {
    return to_string(zi) + "." + to_string(luna) + "." + to_string(an);
}
int Data::getZi() const { return zi; }
int Data::getLuna() const { return luna; }
int Data::getAn() const { return an; }

ostream& operator<<(ostream& out, const Data& data) {
    out << data.toString();
    return out;
}

istream& operator>>(istream& in, Data& data) {
    string input;
    setColorData(14);
    in >> input;

    if (input.length() != 10 || input[2] != '.' || input[5] != '.' ||
        !isdigit(input[0]) || !isdigit(input[1]) ||
        !isdigit(input[3]) || !isdigit(input[4]) ||
        !isdigit(input[6]) || !isdigit(input[7]) || !isdigit(input[8]) || !isdigit(input[9])) {

        setColorData(12);
        cout << "\nEroare: Formatul trebuie sa fie DD.MM.YYYY!" << endl;

        data.zi = data.luna = data.an = 0;
        return in;
    }

    int zi = stoi(input.substr(0, 2));
    int luna = stoi(input.substr(3, 2));
    int an = stoi(input.substr(6, 4));

    data.zi = zi;
    data.luna = luna;
    data.an = an;

    return in;
}


int Data::getZileInLuna(int luna, int an) {
    if (luna < 1 || luna > 12 || an < 0) {
        return 0;
    }
    if (luna == 2) {
        if ((an % 4 == 0 && an % 100 != 0) || (an % 400 == 0)) {
            return 29;
        } else {
            return 28;
        }
    } else if (luna == 4 || luna == 6 || luna == 9 || luna == 11) {
        return 30;
    } else {
        return 31;
    }
}

Data Data::getDataCurenta() {
    time_t t = time(0);
    tm* now = localtime(&t);
    if (now) {
        return Data(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    }
    return Data(1, 1, 2000);
}

