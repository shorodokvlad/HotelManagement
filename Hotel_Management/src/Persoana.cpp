#include "Persoana.h"
#include <windows.h>

using namespace std;

void setColorPersoana(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Persoana::Persoana() : nume(""), prenume(""), CNP("") {}

Persoana::Persoana(const string& _nume, const string& _prenume, const string& _cnp)
    : nume(_nume), prenume(_prenume), CNP(_cnp) {}

string Persoana::getNume() const { return nume; }
string Persoana::getPrenume() const { return prenume; }
string Persoana::getCNP() const { return CNP; }

void Persoana::setNume(const string& _nume) { nume = _nume; }
void Persoana::setPrenume(const string& _prenume) { prenume = _prenume; }
void Persoana::setCNP(const string& _cnp) { CNP = _cnp; }

bool Persoana::validareNume(const string& nume)
{
    if (nume.length() < 3)
    {
        setColorPersoana(12);
        cout << "Numele trebuie sa contina cel putin 3 caractere!\n";
        return false;
    }

    for (char n : nume)
    {
        if (!isalpha(n))
        {
            setColorPersoana(12);
            cout << "Numele poate contine doar litere!\n";
            return false;
        }
    }
    return true;
}

bool Persoana::validarePrenume(const string& prenume)
{
    if (prenume.length() < 3)
    {
        setColorPersoana(12);
        cout << "Prenumele trebuie sa contina cel putin 3 caractere!\n";
        return false;
    }

    for (char n : prenume)
    {
        if (!isalpha(n))
        {
            setColorPersoana(12);
            cout << "Prenumele poate contine doar litere!\n";
            return false;
        }
    }
    return true;
}

bool Persoana::validareCNP(const string& cnp) {
    for (char c : cnp) if (!isdigit(c))
    {
        setColorPersoana(12);
        cout << "CNP-ul trebuie sa contina numai cifre!\n";
        return false;
    }

    if (cnp.length() != 13)
    {
        setColorPersoana(12);
        cout << "CNP-ul trebuie sa contina 13 cifre!\n";
        return false;
    }
    return true;
}


string Persoana::toString() const {
    return "Nume: " + nume + "\n" +
           "Prenume: " + prenume + "\n" +
           "CNP: " + CNP + "\n";
}

ostream& operator<<(ostream& out, const Persoana& persoana) {
    out << persoana.toString();
    return out;
}

istream& operator>>(istream& in, Persoana& persoana) {
    do {
        setColorPersoana(8);
        cout << "Nume: ";
        setColorPersoana(14);
        in >> persoana.nume;
    } while (!Persoana::validareNume(persoana.nume));


    do {
        setColorPersoana(8);
        cout << "Prenume: ";
        setColorPersoana(14);
        in >> persoana.prenume;
    } while (!Persoana::validarePrenume(persoana.prenume));

    do {
        setColorPersoana(8);
        cout << "CNP: ";
        setColorPersoana(14);
        in >> persoana.CNP;
    } while (!Persoana::validareCNP(persoana.CNP));

    return in;
}
