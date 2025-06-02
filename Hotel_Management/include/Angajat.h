#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include "Data.h"
#include <string>

using namespace std;

class Angajat : public Persoana {
private:
    int idAngajat;
    string functie;
    double salariu;
    Data dataAngajare;

public:
    Angajat();
    Angajat(int _idAngajat, const string& _nume, const string& _prenume,
            const string& _cnp, const string& _functie, double _salariu,
            const Data& _dataAngajare);

    int getIdAngajat() const;
    string getFunctie() const;
    double getSalariu() const;
    Data getDataAngajare() const;

    void setIdAngajat(int id);
    void setFunctie(const string& _functie);
    void setSalariu(double _salariu);
    void setDataAngajare(const Data& _dataAngajare);

    string toString() const override;

    static bool validareSalariu(const string& input, double& salariuOut);

    friend ostream& operator<<(ostream& out, const Angajat& angajat);
    friend istream& operator>>(istream& in, Angajat& angajat);
};

#endif
