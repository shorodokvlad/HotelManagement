#ifndef HOTEL_H
#define HOTEL_H

#include "Client.h"
#include "Camera.h"
#include "Rezervare.h"
#include <vector>
#include <string>

class Hotel {
private:
    vector<Client> clienti;
    vector<Camera> camere;
    vector<Rezervare> rezervari;

    int nextClientId;
    int nextRezervareId;

public:
    Hotel();
    void adaugaClient();
    Client* obtineClientDupaId(int id);
    void incarcaClienti();
    void salveazaClienti();
    void adaugaCamera(int numarCamera, const string& tipCamera, double pretNoapte,
                     bool areAerConditionat, bool areWiFi, bool areTV, bool areMinibar);
    Camera* obtineCameraDupaNumar(int numarCamera);
    void incarcaCamere();
    void salveazaCamere();
    void creeazaRezervare(int idClient, int numarCamera, const Data& checkIn, const Data& checkOut);
    void incarcaRezervari();
    void salveazaRezervari();
};

#endif
