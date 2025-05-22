#include "Data.h"
#include <string>
#include <iostream>

using namespace std;


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

ostream& operator<<(ostream& out, const Data& data) {
    out << data.toString();
    return out;
}

istream& operator>>(istream& in, Data& data) {
    scanf("%d.%d.%d", &data.zi, &data.luna, &data.an);

    return in;
}

