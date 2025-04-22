#include "Angajat.h"

// Constructor
Angajat::Angajat(int idAngajat, const std::string& pozitie, double salariu)
    : idAngajat(idAngajat), pozitie(pozitie), salariu(salariu) {}

// Getteri
int Angajat::getIdAngajat() const { return idAngajat; }
std::string Angajat::getPozitie() const { return pozitie; }
double Angajat::getSalariu() const { return salariu; }

// Setteri
void Angajat::setIdAngajat(int idAngajat) { this->idAngajat = idAngajat; }
void Angajat::setPozitie(const std::string& pozitie) { this->pozitie = pozitie; }
void Angajat::setSalariu(double salariu) { this->salariu = salariu; }

// Metoda toString
std::string Angajat::toString() const {
    return "ID Angajat: " + std::to_string(idAngajat) + "\n" +
           "Pozitie: " + pozitie + "\n" +
           "Salariu: " + std::to_string(salariu) + " Lei";
}
