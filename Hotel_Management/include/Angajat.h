#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include "Data.h"
#include <string>

class Angajat : public Persoana {
private:
    int idAngajat;
    std::string functie;
    double salariu;
    Data dataAngajare;

public:
    Angajat();
    Angajat(int _idAngajat, const std::string& _nume, const std::string& _prenume,
            const std::string& _cnp, const std::string& _functie, double _salariu,
            const Data& _dataAngajare);

    int getIdAngajat() const;
    std::string getFunctie() const;
    double getSalariu() const;
    Data getDataAngajare() const;

    void setIdAngajat(int id);
    void setFunctie(const std::string& _functie);
    void setSalariu(double _salariu);
    void setDataAngajare(const Data& _dataAngajare);

    std::string toString() const override;

    friend std::ostream& operator<<(std::ostream& out, const Angajat& angajat);
    friend std::istream& operator>>(std::istream& in, Angajat& angajat);
};

#endif
