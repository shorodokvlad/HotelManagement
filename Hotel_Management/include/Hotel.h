#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include "Client.h"
#include "Camera.h"
#include "Rezervare.h"

using namespace std;

class Hotel {
private:
    vector<Client> clienti;
    vector<Camera> camere;
    vector<Rezervare> rezervari;
    static int nextClientId;
    static int nextRezervareId;

    Client* getClientDupaId(int id);
    Camera* getCameraDupaNumar(int numarCamera);
    bool areRezervareSuprapusa(int numarCamera, const Data& checkIn, const Data& checkOut) const;

    void incarcaClienti();
    void incarcaCamere();
    void incarcaRezervari();
    void salveazaClienti();
    void salveazaCamere();
    void salveazaRezervari();

public:
    Hotel();

    Data citesteData();
    int calculeazaNrNopti(const Data& checkIn, const Data& checkOut);
    double calculeazaPretTotal(int nrNopti, double pretNoapte);
    void adaugaClient();
    void adaugaCamera();
    void incarcaDate();
    void salveazaDate();
    void afiseazaClienti();
    void afiseazaToateCamerele();
    void afiseazaCamereLibere();
    void afiseazaCamereOcupate();
    void adaugaRezervare();
    void afiseazaRezervari();
    void modificaRezervare();
    void modificaStareRezervare(StareRezervare nouaStare);

    const vector<Camera>& getCamere() const { return camere; }
    const vector<Rezervare>& getRezervari() const { return rezervari; }
};

#endif
