#ifndef REZERVARE_H
#define REZERVARE_H

#include "Data.h"
#include <string>
using namespace std;

enum class StareRezervare {
    InAsteptare,
    Confirmata,
    CheckIn,
    CheckOut,
    Anulata
};

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
    Rezervare() : idRezervare(0), idClient(0), idCamera(0), checkIn(), checkOut(), stare(StareRezervare::InAsteptare), nrNopti(0), pretTotal(0.0) {}
    Rezervare(int _idRezervare, int _idClient, int _idCamera, const Data& _checkIn, const Data& _checkOut, StareRezervare _stare, int _nrNopti, double _pretTotal);
    int getIdRezervare() const;
    int getIdClient() const;
    int getIdCamera() const;
    Data getCheckIn() const;
    Data getCheckOut() const;
    StareRezervare getStare() const;
    int getNrNopti() const;
    double getPretTotal() const;
    void setIdClient(int id);
    void setIdCamera(int id);
    void setStare(StareRezervare _stare);
    void setCheckIn(const Data& _checkIn);
    void setCheckOut(const Data& _checkOut);
    void setNrNopti(int _nrNopti);
    void setPretTotal(double _pretTotal);

    string stareToString() const;
    string toString() const;
    friend ostream& operator<<(ostream& out, const Rezervare& rezervare);
    friend istream& operator>>(istream& in, Rezervare& rezervare);
};


#endif
