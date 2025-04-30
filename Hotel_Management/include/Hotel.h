#ifndef HOTEL_H
#define HOTEL_H

#include "Client.h"
#include "Camera.h"
#include <vector>
#include <string>

class Hotel {
private:
    vector<Client> clienti;
    vector<Camera> camere;
    int nextClientId;

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
};

#endif
