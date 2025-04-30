#ifndef REZERVARE_H
#define REZERVARE_H


#include "Data.h"
#include <string>
using namespace std;


enum class StareRezervare { InAsteptare, Confirmata, CheckIn, CheckOut, Anulata };

int calculeazaNrNopti(const Data& start, const Data& end);
double calculeazaPretTotal(int nrNopti, double pretNoapte);

class Rezervare {
private:
    int idRezervare;
    int idClient;
    int idCamera;
    Data checkIn;
    Data checkOut;
    StareRezervare stare;
    int nrNopti;
    double pretTotal;

public:
    Rezervare(int idR, int idC, int idCa, const Data& ci, const Data& co, StareRezervare s, int nn, double pt);
    int getIdRezervare() const;
    int getIdClient() const;
    int getIdCamera() const;
    Data getCheckIn() const;
    Data getCheckOut() const;
    StareRezervare getStare() const;
    int getNrNopti() const;
    double getPretTotal() const;
    void seteazaStare(StareRezervare s);
    void seteazaCheckIn(const Data& ci);
    void seteazaCheckOut(const Data& co);
    void seteazaNrNopti(int nn);
    void seteazaPretTotal(double pt);
    string stareToString() const;
    string toString() const;
};


#endif
