#include "Rezervare.h"
#include <string>
#include <iostream>

using namespace std;

Rezervare::Rezervare(int _idRezervare, int _idClient, int _idCamera, const Data& _checkIn, const Data& _checkOut, StareRezervare _stare, int _nrNopti, double _pretTotal)
    : idRezervare(_idRezervare), idClient(_idClient), idCamera(_idCamera), checkIn(_checkIn), checkOut(_checkOut),
     stare(_stare), nrNopti(_nrNopti), pretTotal(_pretTotal) {}

int Rezervare::getIdRezervare() const { return idRezervare; }
int Rezervare::getIdClient() const { return idClient; }
int Rezervare::getIdCamera() const { return idCamera; }
Data Rezervare::getCheckIn() const { return checkIn; }
Data Rezervare::getCheckOut() const { return checkOut; }
StareRezervare Rezervare::getStare() const { return stare; }
int Rezervare::getNrNopti() const { return nrNopti; }
double Rezervare::getPretTotal() const { return pretTotal; }

void Rezervare::setIdClient(int id) { idClient = id; };
void Rezervare::setIdCamera(int id) { idCamera = id; };
void Rezervare::setStare(StareRezervare _stare) { stare = _stare; }
void Rezervare::setCheckIn(const Data& _checkIn) { checkIn = _checkIn; }
void Rezervare::setCheckOut(const Data& _checkOut) { checkOut = _checkOut; }
void Rezervare::setNrNopti(int _nrNopti) { nrNopti = _nrNopti; }
void Rezervare::setPretTotal(double _pretTotal) { pretTotal = _pretTotal; }


string Rezervare::stareToString() const {
    switch (stare) {
        case StareRezervare::InAsteptare: return "In asteptare";
        case StareRezervare::Confirmata: return "Confirmata";
        case StareRezervare::CheckIn: return "Check-in";
        case StareRezervare::CheckOut: return "Check-out";
        case StareRezervare::Anulata: return "Anulata";
        default: return "Necunoscut";
    }
}

string Rezervare::toString() const {
    return "ID Rezervare: " + to_string(idRezervare) + "\n" +
           "ID Client: " + to_string(idClient) + "\n" +
           "Camera: " + to_string(idCamera) + "\n" +
           "Check-In: " + checkIn.toString() + "\n" +
           "Check-Out: " + checkOut.toString() + "\n" +
           "Stare: " + stareToString() + "\n" +
           "Numar nopti: " + to_string(nrNopti) + "\n" +
           "Pret Total: " + to_string(pretTotal) + " RON\n";
}

ostream& operator<<(ostream& out, const Rezervare& rezervare) {
    out << rezervare.toString();
    return out;
}

istream& operator>>(istream& in, Rezervare& rezervare) {
    cout << "ID Client: ";
    in >> rezervare.idClient;

    cout << "ID Camera: ";
    in >> rezervare.idCamera;

    cout << "Check-In (data in format dd/mm/yyyy): ";
    in >> rezervare.checkIn;

    cout << "Check-Out (data in format dd/mm/yyyy): ";
    in >> rezervare.checkOut; //

    int stareInt;
    cout << "Stare Rezervare (0 - InAsteptare, 1 - Confirmata, 2 - CheckIn, 3 - CheckOut, 4 - Anulata): ";
    in >> stareInt;

    if (stareInt == 0) {
        rezervare.stare = StareRezervare::InAsteptare;
    } else if (stareInt == 1) {
        rezervare.stare = StareRezervare::Confirmata;
    } else if (stareInt == 2) {
        rezervare.stare = StareRezervare::CheckIn;
    } else if (stareInt == 3) {
        rezervare.stare = StareRezervare::CheckOut;
    } else if (stareInt == 4) {
        rezervare.stare = StareRezervare::Anulata;
    } else {
        cout << "Eroare: Stare rezervare invalida." << endl;
        rezervare.stare = StareRezervare::InAsteptare;
    }

    cout << "Numar Nopti: ";
    in >> rezervare.nrNopti;

    cout << "Pret Total: ";
    in >> rezervare.pretTotal;

    return in;
}
