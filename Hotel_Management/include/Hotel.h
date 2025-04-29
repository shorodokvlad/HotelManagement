#ifndef HOTEL_H
#define HOTEL_H

#include "Client.h"
#include <vector>
#include <string>

class Hotel {
private:
    vector<Client> clienti;
    int nextClientId;

public:
    Hotel();
    void adaugaClient();
    Client* obtineClientDupaId(int id);
    void incarcaClienti();
    void salveazaClienti();
};

#endif
