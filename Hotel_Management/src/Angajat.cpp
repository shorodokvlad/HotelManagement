#include "Angajat.h"
#include <iostream>

using namespace std;

// Constructor implicit
Angajat::Angajat()
    : Persoana(), angajatID(0), departament(""), pozitie(""), salariu(0.0),
      dataAngajare(""), programMunca("") {}

// Constructor cu parametri
Angajat::Angajat(const std::string& nume, const std::string& prenume, const std::string& CNP,
                 const std::string& gen, int id, const std::string& departament,
                 const std::string& pozitie, double salariu, const std::string& dataAngajare,
                 const std::string& programMunca)
    : Persoana(nume, prenume, CNP, gen) {
    angajatID = id;
    this->departament = departament;
    this->pozitie = pozitie;
    this->salariu = salariu;
    this->dataAngajare = dataAngajare;
    this->programMunca = programMunca;
}

// Destructor
Angajat::~Angajat() {
}

// Getteri și setteri
int Angajat::getAngajatID() const { return angajatID; }
void Angajat::setAngajatID(int id) { angajatID = id; }

string Angajat::getDepartament() const { return departament; }
void Angajat::setDepartament(const string& departament) { this->departament = departament; }

string Angajat::getPozitie() const { return pozitie; }
void Angajat::setPozitie(const string& pozitie) { this->pozitie = pozitie; }

double Angajat::getSalariu() const { return salariu; }
void Angajat::setSalariu(double salariu) { this->salariu = salariu; }

string Angajat::getDataAngajare() const { return dataAngajare; }
void Angajat::setDataAngajare(const string& data) { dataAngajare = data; }

string Angajat::getProgramMunca() const { return programMunca; }
void Angajat::setProgramMunca(const string& program) { programMunca = program; }

// Metoda toString
string Angajat::toString() const {
    return "AngajatID: " + to_string(angajatID) + "\n" +
           "Nume: " + getNume() + " " + getPrenume() + "\n" +
           "CNP: " + getCNP() + "\n" +
           "Gen: " + getGen() + "\n" +
           "Departament: " + departament + "\n" +
           "Pozitie: " + pozitie + "\n" +
           "Salariu: " + to_string(salariu) + "\n" +
           "Data angajare: " + dataAngajare + "\n" +
           "Program munca: " + programMunca;
}

// Operator << (ostream)
ostream& operator<<(ostream& out, const Angajat& angajat) {
    out << angajat.toString();
    return out;
}

// Operator >> (istream)
istream& operator>>(istream& in, Angajat& angajat) {
    cout << "Introduceti AngajatID: ";
    in >> angajat.angajatID;

    cout << "Introduceti Numele: ";
    in >> angajat.nume;

    cout << "Introduceti Prenumele: ";
    in >> angajat.prenume;

    cout << "Introduceti CNP: ";
    in >> angajat.CNP;

    cout << "Introduceti genul: ";
    in >> angajat.gen;

    cout << "Introduceti Departamentul: ";
    in >> angajat.departament;

    cout << "Introduceti Pozitia: ";
    in >> angajat.pozitie;

    cout << "Introduceti Salariul: ";
    in >> angajat.salariu;

    cout << "Introduceti Data angajare (format: DD-MM-YYYY): ";
    in >> angajat.dataAngajare;

    cout << "Introduceti Program munca: ";
    in >> angajat.programMunca;

    return in;
}
