#ifndef CLIENT_H
#define CLIENT_H

#include <string>
using namespace std;

class Client {
private:
    int idClient;
    string nume;
    string prenume;
    string CNP;
    string telefon;
public:
    Client(int _idClient, const string& _nume, const string& _prenume, const string& _cnp, const string& _telefon);
    int getIdClient() const;
    string getNume() const;
    string getPrenume() const;
    string getCNP() const;
    string getTelefon() const;
    static bool validareTelefon(const string& telefon);
    static bool validareCNP(const string& cnp);
    string toString() const;
};

#endif
