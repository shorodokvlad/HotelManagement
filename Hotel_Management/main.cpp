#include "Hotel.h"
#include "Camera.h"
#include "Rezervare.h"
#include "Client.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Hotel hotel;

    // Încărcăm clienții și camerele din fișiere
    cout << "Test incarcaClienti:" << endl;
    hotel.incarcaClienti();
    if (hotel.obtineClientDupaId(1) == nullptr) {
        cout << "Eroare: Nu exista client cu ID 1 in Clienti.txt" << endl;
        return 1;
    }
    cout << "Clienti incarcati cu succes." << endl;
    cout << endl;

    cout << "Test incarcaCamere:" << endl;
    hotel.incarcaCamere();
    if (hotel.obtineCameraDupaNumar(101) == nullptr) {
        cout << "Eroare: Nu exista camera cu numarul 101 in Camere.txt" << endl;
        return 1;
    }
    cout << "Camere incarcate cu succes." << endl;
    cout << endl;

    // Testăm crearea rezervării
    cout << "Test creeazaRezervare:" << endl;
    hotel.creeazaRezervare(1, 101, Data(1, 5, 2025), Data(3, 5, 2025));
    cout << endl;

    // Testăm metodele de afișare
    cout << "Test afiseazaClienti:" << endl;
    hotel.afiseazaClienti();
    cout << endl;

    cout << "Test afiseazaToateCamerele:" << endl;
    hotel.afiseazaToateCamerele();
    cout << endl;

    cout << "Test afiseazaRezervari:" << endl;
    hotel.afiseazaRezervari();
    cout << endl;

    // Testăm salvarea și încărcarea rezervărilor
    cout << "Test salveazaRezervari si incarcaRezervari:" << endl;
    hotel.salveazaRezervari();
    hotel.incarcaRezervari();
    cout << "Rezervari dupa incarcare:" << endl;
    hotel.afiseazaRezervari();

    cout << "Test afiseazaCamereLibere:" << endl;
    hotel.afiseazaCamereLibere();
    cout << endl;

    cout << "Test afiseazaCamereOcupate:" << endl;
    hotel.afiseazaCamereOcupate();
    cout << endl;

    return 0;
}
