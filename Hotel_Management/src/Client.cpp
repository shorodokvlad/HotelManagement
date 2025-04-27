#include "Client.h"
#include <string>
#include <cctype>

using namespace std;

Client::Client(int id, const string& n, const string& p, const string& c, const string& t)
    : idClient(id), nume(n), prenume(p), CNP(c), telefon(t) {}

int Client::getIdClient() const { return idClient; }
string Client::getNume() const { return nume; }
string Client::getPrenume() const { return prenume; }
string Client::getCNP() const { return CNP; }
string Client::getTelefon() const { return telefon; }

bool Client::valideazaTelefon(const string& tel) {
    if (tel.length() != 10 || tel.substr(0, 2) != "07") return false;
    for (char c : tel) if (!isdigit(c)) return false;
    return true;
}

bool Client::valideazaCNP(const string& cnp) {
    if (cnp.length() != 13) return false;
    for (char c : cnp) if (!isdigit(c)) return false;
    return true;
}

string Client::toString() const {
    return "ID Client: " + to_string(idClient) + "\n" +
           "Nume: " + nume + "\n" +
           "Prenume: " + prenume + "\n" +
           "CNP: " + CNP + "\n" +
           "Telefon: " + telefon + "\n";
}
