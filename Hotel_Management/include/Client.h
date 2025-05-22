#ifndef CLIENT_H
#define CLIENT_H

#include "Persoana.h"
#include <string>
using namespace std;

class Client : public Persoana {
private:
    int idClient;
    string telefon;

public:
    Client();
    Client(int _idClient, const string& _nume, const string& _prenume,
           const string& _cnp, const string& _telefon);

    int getIdClient() const;
    string getTelefon() const;

    void setIdClient(int id);
    void setTelefon(const string& _telefon);

    static bool validareTelefon(const string& telefon);

    string toString() const override;

    friend ostream& operator<<(ostream& out, const Client& client);
    friend istream& operator>>(istream& in, Client& client);
};

#endif
