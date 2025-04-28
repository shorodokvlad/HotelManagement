#include "Rezervare.h"
#include <string>

using namespace std;

int calculeazaNrNopti(const Data& start, const Data& end) {
    int zilePeLuna[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int zile = 0;
    Data temp = start;
    while (temp.esteMaiMicaDecat(end)) {
        bool esteAnBisect = (temp.an % 4 == 0 && (temp.an % 100 != 0 || temp.an % 400 == 0));
        int maxZile = zilePeLuna[temp.luna];
        if (temp.luna == 2 && esteAnBisect) maxZile = 29;
        temp.zi++;
        if (temp.zi > maxZile) {
            temp.zi = 1;
            temp.luna++;
            if (temp.luna > 12) {
                temp.luna = 1;
                temp.an++;
            }
        }
        zile++;
    }
    return zile;
}

double calculeazaPretTotal(int nrNopti, double pretNoapte) {
    return nrNopti * pretNoapte;
}

Rezervare::Rezervare(int idR, int idC, int idCa, const Data& ci, const Data& co, StareRezervare s, int nn, double pt)
    : idRezervare(idR), idClient(idC), idCamera(idCa), checkIn(ci), checkOut(co), stare(s), nrNopti(nn), pretTotal(pt) {}

int Rezervare::getIdRezervare() const { return idRezervare; }
int Rezervare::getIdClient() const { return idClient; }
int Rezervare::getIdCamera() const { return idCamera; }
Data Rezervare::getCheckIn() const { return checkIn; }
Data Rezervare::getCheckOut() const { return checkOut; }
StareRezervare Rezervare::getStare() const { return stare; }
int Rezervare::getNrNopti() const { return nrNopti; }
double Rezervare::getPretTotal() const { return pretTotal; }

void Rezervare::seteazaStare(StareRezervare s) { stare = s; }
void Rezervare::seteazaCheckIn(const Data& ci) { checkIn = ci; }
void Rezervare::seteazaCheckOut(const Data& co) { checkOut = co; }
void Rezervare::seteazaNrNopti(int nn) { nrNopti = nn; }
void Rezervare::seteazaPretTotal(double pt) { pretTotal = pt; }

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
