#ifndef REZERVARE_H
#define REZERVARE_H

#include <string>
#include <iostream>
#include <ctime>
#include "Client.h"
#include "Camera.h"

class Rezervare {
private:
    int idRezervare;
    Client* client;
    Camera* camera;
    std::tm dataCheckIn;
    std::tm dataCheckOut;
    std::string status;
    int numarNopti;
    double totalPlata;

    bool esteDataValidă() const;
    void calculeazaNumarNopti();
    void calculeazaTotalPlata();

public:
    Rezervare(int idRezervare, Client* client, Camera* camera,
              const std::tm& dataCheckIn, const std::tm& dataCheckOut, const std::string& status);

    int getIdRezervare() const;
    int getNumarNopti() const;
    double getTotalPlata() const;
    std::string getStatus() const;

    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& out, const Rezervare& rezervare);
    friend std::istream& operator>>(std::istream& in, Rezervare& rezervare);
};

#endif
