#include "Persoana.h"
#include <iostream>

using namespace std;

// Constructor implicit
Persoana::Persoana() {
    nume = "Necunoscut";
    prenume = "Necunoscut";
    CNP = "0000000000000";
    gen = "N/A";
}

// Constructor cu parametri
Persoana::Persoana(const string& nume, const string& prenume, const string& CNP, const string& gen) {
    this->nume = nume;
    this->prenume = prenume;
    this->CNP = CNP;
    this->gen = gen;
}

// Destructor
Persoana::~Persoana() {
}

// Getteri
string Persoana::getNume() const { return nume; }
string Persoana::getPrenume() const { return prenume; }
string Persoana::getCNP() const { return CNP; }
string Persoana::getGen() const { return gen; }

// Setteri
void Persoana::setNume(const string& nume) { this->nume = nume; }
void Persoana::setPrenume(const string& prenume) { this->prenume = prenume; }
void Persoana::setCNP(const string& CNP) { this->CNP = CNP; }
void Persoana::setGen(const string& gen) { this->gen = gen; }

// Metoda toString
string Persoana::toString() const {
    return "Nume: " + nume + " " + prenume + "\n" +
           "CNP: " + CNP + "\n" +
           "Gen: " + gen;
}

// Operator << (ostream)
ostream& operator<<(ostream& out, const Persoana& p) {
    out << p.toString();
    return out;
}

// Operator >> (istream)
istream& operator>>(istream& in, Persoana& p) {
    cout << "Introduceti numele: ";
    in >> p.nume;
    cout << "Introduceti prenumele: ";
    in >> p.prenume;
    cout << "Introduceti CNP: ";
    in >> p.CNP;
    cout << "Introduceti genul: ";
    in >> p.gen;
    return in;
}
