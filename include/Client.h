#ifndef CLIENT_H
#define CLIENT_H

#include "Persoana.h"
#include <string>
#include <iostream>

using namespace std;

class Client : public Persoana {
private:
    int idClient;
    string telefon;

public:
    // Constructor cu parametri
    Client(int idClient, const string& nume, const string& prenume, const string& CNP, const string& telefon);

    // Getteri
    int getIdClient() const;
    string getTelefon() const;

    // Metoda toString
    string toString() const override;

    // Operator << (ostream)
    friend ostream& operator<<(ostream& out, const Client& client);

    // Operator >> (istream)
    friend istream& operator>>(istream& in, Client& client);
};

#endif // CLIENT_H
