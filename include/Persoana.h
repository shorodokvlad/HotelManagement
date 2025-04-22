#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <iostream>

class Persoana {
protected:
    std::string nume;
    std::string prenume;
    std::string CNP;

public:
    // Constructori
    Persoana(const std::string& nume, const std::string& prenume, const std::string& CNP);
    virtual ~Persoana();

    // Getteri
    std::string getNume() const;
    std::string getPrenume() const;
    std::string getCNP() const;

    // Metoda toString
    virtual std::string toString() const;

    // Operator << (ostream)
    friend std::ostream& operator<<(std::ostream& out, const Persoana& persoana);

    // Operator >> (istream)
    friend std::istream& operator>>(std::istream& in, Persoana& persoana);
};

#endif // PERSOANA_H
