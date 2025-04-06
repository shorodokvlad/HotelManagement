#ifndef PERSOANA_H
#define PERSOANA_H

#include <iostream>
#include <string>

using namespace std;

class Persoana {
protected:
    string nume;
    string prenume;
    string CNP;
    string gen;

public:
    // Constructor implicit
    Persoana();

    // Constructor cu parametri
    Persoana(const string& nume, const string& prenume, const string& CNP, const string& gen);

    // Destructor
    ~Persoana();

    // Getteri
    string getNume() const;
    string getPrenume() const;
    string getCNP() const;
    string getGen() const;

    // Setteri
    void setNume(const string& nume);
    void setPrenume(const string& prenume);
    void setCNP(const string& CNP);
    void setGen(const string& gen);

    // Metoda toString
    string toString() const;

    // Supraincarcare operatori
    friend ostream& operator<<(ostream& out, const Persoana& p);
    friend istream& operator>>(istream& in, Persoana& p);
};

#endif // PERSOANA_H
