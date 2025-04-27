#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
    int idClient;
    std::string nume;
    std::string prenume;
    std::string CNP;
    std::string telefon;
public:
    Client(int id, const std::string& n, const std::string& p, const std::string& c, const std::string& t);
    int getIdClient() const;
    std::string getNume() const;
    std::string getPrenume() const;
    std::string getCNP() const;
    std::string getTelefon() const;
    static bool valideazaTelefon(const std::string& tel);
    static bool valideazaCNP(const std::string& cnp);
    std::string toString() const;
};

#endif
