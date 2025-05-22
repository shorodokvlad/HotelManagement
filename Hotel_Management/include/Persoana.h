#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <iostream>
using namespace std;

class Persoana {
protected:
    string nume;
    string prenume;
    string CNP;

public:
    Persoana();
    Persoana(const string& _nume, const string& _prenume, const string& _cnp);
    virtual ~Persoana() = default;

    string getNume() const;
    string getPrenume() const;
    string getCNP() const;

    void setNume(const string& _nume);
    void setPrenume(const string& _prenume);
    void setCNP(const string& _cnp);

    static bool validareCNP(const string& cnp);

    virtual string toString() const;

    friend ostream& operator<<(ostream& out, const Persoana& persoana);
    friend istream& operator>>(istream& in, Persoana& persoana);
};

#endif
