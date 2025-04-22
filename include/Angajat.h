#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>

class Angajat {
private:
    int idAngajat;
    std::string pozitie;
    double salariu;

public:
    // Constructor cu parametri
    Angajat(int idAngajat, const std::string& pozitie, double salariu);

    // Getteri
    int getIdAngajat() const;
    std::string getPozitie() const;
    double getSalariu() const;

    // Setteri
    void setIdAngajat(int idAngajat);
    void setPozitie(const std::string& pozitie);
    void setSalariu(double salariu);

    // Metoda toString
    std::string toString() const;
};

#endif
