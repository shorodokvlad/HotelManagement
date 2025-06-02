#include "Client.h"
#include <windows.h>

using namespace std;

void setColorClient(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Client::Client() : Persoana(), idClient(0), telefon("") {}

Client::Client(int _idClient, const string& _nume, const string& _prenume, const string& _cnp, const string& _telefon)
    : Persoana(_nume, _prenume, _cnp), idClient(_idClient), telefon(_telefon) {}

int Client::getIdClient() const { return idClient; }
string Client::getTelefon() const { return telefon; }

void Client::setIdClient(int id) { idClient = id; }
void Client::setTelefon(const string& _telefon) { telefon = _telefon; }

bool Client::validareTelefon(const string& telefon) {
    for (char c : telefon) if (!isdigit(c))
    {
        setColorClient(12);
        cout << "Numarul de telefon trebuie sa contina numai cifre!\n";
        return false;
    }

    if (telefon.length() != 10)
    {
        setColorClient(12);
        cout << "Numarul de telefon trebuie sa contina 10 cifre!\n";
        return false;
    }
    return true;
}

string Client::toString() const {
    return "ID Client: " + to_string(idClient) + "\n" +
           Persoana::toString() +
           "Telefon: " + telefon + "\n";
}

ostream& operator<<(ostream& out, const Client& client) {
    out << client.toString();
    return out;
}

istream& operator>>(istream& in, Client& client) {
    in >> (Persoana&)client;
    do {
        setColorClient(8);
        cout << "Telefon: ";
        setColorClient(14);
        in >> client.telefon;
    } while (!Client::validareTelefon(client.telefon));
    return in;
}
