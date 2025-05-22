#include "Persoana.h"

using namespace std;

Persoana::Persoana() : nume(""), prenume(""), CNP("") {}

Persoana::Persoana(const string& _nume, const string& _prenume, const string& _cnp)
    : nume(_nume), prenume(_prenume), CNP(_cnp) {}

string Persoana::getNume() const { return nume; }
string Persoana::getPrenume() const { return prenume; }
string Persoana::getCNP() const { return CNP; }

void Persoana::setNume(const string& _nume) { nume = _nume; }
void Persoana::setPrenume(const string& _prenume) { prenume = _prenume; }
void Persoana::setCNP(const string& _cnp) { CNP = _cnp; }

bool Persoana::validareCNP(const string& cnp) {
    if (cnp.length() != 13) return false;
    for (char c : cnp) if (!isdigit(c)) return false;
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
    cout << "Nume: ";
    in >> persoana.nume;

    cout << "Prenume: ";
    in >> persoana.prenume;

    do {
        cout << "CNP (13 cifre): ";
        in >> persoana.CNP;
    } while (!Persoana::validareCNP(persoana.CNP));

    return in;
}
