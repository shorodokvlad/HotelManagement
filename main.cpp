#include <iostream>
#include <string>
#include "Angajat.h"
#include "Client.h"
#include "Camera.h"
#include "Rezervare.h"

using namespace std;

int main() {
    // Creare Angajat
    Angajat angajat1(1, "Receptioner", 2500.0);

    // Creare Client
    Client client1(1, "Ion", "Popescu", "1234567890123", "0712345678");

    // Creare Camera
    Camera camera1(101, "Single", 1, 100.0, false, true, true, true);

    // Creare date Check-in și Check-out
    std::tm checkIn = {};
    checkIn.tm_year = 2025 - 1900; // Anul (de exemplu 2025)
    checkIn.tm_mon = 2; // Martie (Luna 2 pentru martie)
    checkIn.tm_mday = 25; // Ziua (25 martie)

    std::tm checkOut = {};
    checkOut.tm_year = 2025 - 1900; // Anul (2025)
    checkOut.tm_mon = 3; // Aprilie (Luna 3 pentru aprilie)
    checkOut.tm_mday = 5; // Ziua (5 aprilie)

    // Creare Rezervare
    Rezervare rezervare1(1, &client1, &camera1, checkIn, checkOut, "Efectuata");

    // Afișare detalii Angajat
    cout << "Detalii Angajat: \n";
    cout << angajat1.toString() << endl;

    // Afișare detalii Rezervare
    cout << "Detalii Rezervare: \n";
    cout << rezervare1 << endl;

    // Testare calculul numărului de nopți și totalul de plată
    cout << "Numar nopti: " << rezervare1.getNumarNopti() << endl;
    cout << "Total plata: " << rezervare1.getTotalPlata() << " Lei" << endl;

    return 0;
}
