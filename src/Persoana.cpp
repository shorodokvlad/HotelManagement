#include "Persoana.h"

// Constructor
Persoana::Persoana(const std::string& nume, const std::string& prenume, const std::string& CNP)
    : nume(nume), prenume(prenume), CNP(CNP) {}

// Destructor
Persoana::~Persoana() {}

// Getteri
std::string Persoana::getNume() const {
    return nume;
}

std::string Persoana::getPrenume() const {
    return prenume;
}

std::string Persoana::getCNP() const {
    return CNP;
}

// Metoda toString
std::string Persoana::toString() const {
    return "Nume: " + nume + "\n" +
           "Prenume: " + prenume + "\n" +
           "CNP: " + CNP;
}

// Operator << (ostream)
std::ostream& operator<<(std::ostream& out, const Persoana& persoana) {
    out << persoana.toString();
    return out;
}

// Operator >> (istream)
std::istream& operator>>(std::istream& in, Persoana& persoana) {
    std::cout << "Introduceti numele: ";
    in >> persoana.nume;

    std::cout << "Introduceti prenumele: ";
    in >> persoana.prenume;

    std::cout << "Introduceti CNP-ul: ";
    in >> persoana.CNP;

    return in;
}
