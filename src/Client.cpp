#include "Client.h"

using namespace std;

// Constructor cu parametri
Client::Client(int idClient, const string& nume, const string& prenume, const string& CNP, const string& telefon)
    : Persoana(nume, prenume, CNP), idClient(idClient), telefon(telefon) {}

// Getteri
int Client::getIdClient() const {
    return idClient;
}

string Client::getTelefon() const {
    return telefon;
}

// Metoda toString
string Client::toString() const {
    return "ID Client: " + to_string(idClient) + "\n" +
           "Nume: " + getNume() + "\n" +
           "Prenume: " + getPrenume() + "\n" +
           "CNP: " + getCNP() + "\n" +
           "Telefon: " + telefon;
}

// Operator << (ostream)
ostream& operator<<(ostream& out, const Client& client) {
    out << client.toString();
    return out;
}

// Operator >> (istream)
istream& operator>>(istream& in, Client& client) {
    cout << "Introduceti ID Client: ";
    in >> client.idClient;

    cout << "Introduceti Numele: ";
    in >> client.nume;

    cout << "Introduceti Prenumele: ";
    in >> client.prenume;

    cout << "Introduceti CNP: ";
    in >> client.CNP;

    cout << "Introduceti Telefon: ";
    in >> client.telefon;

    return in;
}
