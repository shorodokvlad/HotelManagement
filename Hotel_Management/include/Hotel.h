#ifndef HOTEL_H
#define HOTEL_H

#include "Client.h"
#include "Camera.h"
#include "Rezervare.h"
#include "Data.h"
#include <vector>
#include <string>

class Hotel {
private:
    vector<Client> clienti;
    vector<Camera> camere;
    vector<Rezervare> rezervari;

    int nextClientId;
    int nextRezervareId;

    bool areRezervareSuprapusa(int numarCamera, const Data& checkIn, const Data& checkOut) const;


public:
    Hotel();
    Data citesteData();
    int calculeazaNrNopti(const Data& checkIn, const Data& checkOut);
    double calculeazaPretTotal(int nrNopti, double pretNoapte);
    Client* obtineClientDupaId(int id);
    Camera* obtineCameraDupaNumar(int numarCamera);
    void incarcaClienti();
    void salveazaClienti();
    void incarcaCamere();
    void salveazaCamere();
    void incarcaRezervari();
    void salveazaRezervari();
    void adaugaClient();
    void salveazaDate();
    void adaugaCamera(int numarCamera, const string& tipCamera, double pretNoapte,
                     bool areAerConditionat, bool areWiFi, bool areTV, bool areMinibar);
    void creeazaRezervare(int idClient, int numarCamera, const Data& checkIn, const Data& checkOut);
    void afiseazaClienti();
    void afiseazaToateCamerele();
    void afiseazaRezervari();
    void afiseazaCamereLibere();
    void afiseazaCamereOcupate();
    void gestioneazaRezervare(int idRezervare, StareRezervare nouaStare);
};

#endif
