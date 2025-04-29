#include "Hotel.h"
#include <iostream>

using namespace std;

int main() {
    Hotel hotel;

    hotel.adaugaClient();
    hotel.adaugaClient();

    Client* client = hotel.obtineClientDupaId(1);
    if (client) {
        cout << "Client gasit: " << client->toString() << endl;
    } else {
        cout << "Client cu ID 1 nu a fost gasit." << endl;
    }

    hotel.incarcaClienti();
    client = hotel.obtineClientDupaId(1);
    if (client) {
        cout << "Client incarcat: " << client->toString() << endl;
    } else {
        cout << "Client nu a fost incarcat." << endl;
    }

    return 0;
}
