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
    Client(int id, const string& n, const string& p, const string& c, const string& t);
    int getIdClient() const;
    string getNume() const;
    string getPrenume() const;
    string getCNP() const;
    string getTelefon() const;
    static bool valideazaTelefon(const string& tel);
    static bool valideazaCNP(const string& cnp);
    string toString() const;
};

#endif
