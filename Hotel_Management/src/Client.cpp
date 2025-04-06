#include "Client.h"
#include <iostream>

using namespace std;

// Constructor implicit
Client::Client() {
    clientID = 0;
    checkInDate = "";
    checkOutDate = "";
    nrNopti = 0;
    metodaPlata = "";
    totalPlata = 0.0;
    micDejunInclus = false;
    cereriSpeciale = "";
}

// Constructor cu parametri
Client::Client(const string& nume, const string& prenume, const string& CNP, const string& gen, int id, const string& checkIn, const std::string& checkOut,
               int nopti, const string& plata, double total, bool micDejun, const string& cereri)
    : Persoana(nume, prenume, CNP, gen) {
    clientID = id;
    checkInDate = checkIn;
    checkOutDate = checkOut;
    nrNopti = nopti;
    metodaPlata = plata;
    totalPlata = total;
    micDejunInclus = micDejun;
    cereriSpeciale = cereri;
}

// Destructor
Client::~Client() {
}

// Getteri
int Client::getClientID() const { return clientID; }
const std::string& Client::getCheckInDate() const { return checkInDate; }
const std::string& Client::getCheckOutDate() const { return checkOutDate; }
int Client::getNrNopti() const { return nrNopti; }
const std::string& Client::getMetodaPlata() const { return metodaPlata; }
double Client::getTotalPlata() const { return totalPlata; }
bool Client::isMicDejunInclus() const { return micDejunInclus; }
const std::string& Client::getCereriSpeciale() const { return cereriSpeciale; }

// Setteri
void Client::setClientID(int id) { clientID = id; }
void Client::setCheckInDate(const std::string& checkIn) { checkInDate = checkIn; }
void Client::setCheckOutDate(const std::string& checkOut) { checkOutDate = checkOut; }
void Client::setNrNopti(int nopti) { nrNopti = nopti; }
void Client::setMetodaPlata(const std::string& plata) { metodaPlata = plata; }
void Client::setTotalPlata(double total) { totalPlata = total; }
void Client::setMicDejunInclus(bool inclus) { micDejunInclus = inclus; }
void Client::setCereriSpeciale(const std::string& cereri) { cereriSpeciale = cereri; }


string Client::toString() const {
    return "ClientID: " + to_string(clientID) + "\n" +
           "Nume: " + getNume() + " " + getPrenume() + "\n" +
           "CNP: " + getCNP() + "\n" +
           "Gen: " + getGen() + "\n" +
           "Check-in: " + checkInDate + "\n" +
           "Check-out: " + checkOutDate + "\n" +
           "Numar nopti: " + to_string(nrNopti) + "\n" +
           "Metoda plata: " + metodaPlata + "\n" +
           "Total plata: " + to_string(totalPlata) + "\n" +
           "Mic dejun inclus: " + (micDejunInclus ? "Da" : "Nu") + "\n" +
           "Cereri speciale: " + cereriSpeciale;
}

ostream& operator<<(ostream& out, const Client& client) {
    out << client.toString();
    return out;
}

istream& operator>>(istream& in, Client& client) {
    cout << "Introduceti ClientID: ";
    in >> client.clientID;

    cout << "Introduceti Numele: ";
    in >> client.nume;

    cout << "Introduceti Prenumele: ";
    in >> client.prenume;

    cout << "Introduceti CNP: ";
    in >> client.CNP;

    cout << "Introduceti genul: ";
    in >> client.gen;

    cout << "Introduceti Check-in (format: DD-MM-YYY): ";
    in >> client.checkInDate;

    cout << "Introduceti Check-out (format: DD-MM-YY): ";
    in >> client.checkOutDate;

    cout << "Introduceti Numar nopti: ";
    in >> client.nrNopti;

    cout << "Introduceti Metoda de plata: ";
    in >> client.metodaPlata;

    cout << "Introduceti Total plata: ";
    in >> client.totalPlata;

    cout << "Mic dejun inclus? (1 pentru Da, 0 pentru Nu): ";
    in >> client.micDejunInclus;

    cout << "Introduceti Cereri speciale: ";
    in >> client.cereriSpeciale;

    return in;
}
