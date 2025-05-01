#include "Client.h"
#include <string>
#include <cctype>

using namespace std;

Client::Client(int _idClient, const string& _nume, const string& _prenume, const string& _cnp, const string& _telefon)
    : idClient(_idClient), nume(_nume), prenume(_prenume), CNP(_cnp), telefon(_telefon) {}

int Client::getIdClient() const { return idClient; }
string Client::getNume() const { return nume; }
string Client::getPrenume() const { return prenume; }
string Client::getCNP() const { return CNP; }
string Client::getTelefon() const { return telefon; }

bool Client::validareTelefon(const string& telefon) {
    if (telefon.length() != 10 ) return false;
    for (char c : telefon) if (!isdigit(c)) return false;
    return true;
}

bool Client::validareCNP(const string& cnp) {
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
