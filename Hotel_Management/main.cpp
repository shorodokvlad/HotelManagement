#include "Hotel.h"
#include "Camera.h"
#include "Rezervare.h"
#include "Client.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    Hotel hotel;

    // Adăugăm un client pentru a evita eroarea "client inexistent"
    cout << "Test adaugaClient:" << endl;
    try {
        hotel.adaugaClient(); // Permite introducerea manuală a datelor clientului
        // Exemplu: Introduci ID 1, Popescu, Ion, 1234567890123, 0712345678
    } catch (const exception& e) {
        cout << "Eroare la adaugarea clientului: " << e.what() << endl;
        return 1;
    }
    cout << endl;

    // Adăugăm o cameră pentru a evita eroarea "camera inexistenta"
    cout << "Test adaugaCamera:" << endl;
    hotel.adaugaCamera(101, "Single", 100.0, true, true, true, false);
    cout << endl;

    // Testăm crearea rezervării
    cout << "Test creeazaRezervare:" << endl;
    hotel.creeazaRezervare(1, 101, Data(1, 5, 2025), Data(3, 5, 2025));
    cout << endl;

    // Testăm salvarea și încărcarea rezervărilor
    cout << "Test salveazaRezervari si incarcaRezervari:" << endl;
    hotel.salveazaRezervari();
    hotel.incarcaRezervari();
    // Verificăm dacă rezervarea există citind direct din fișier pentru simplitate
    ifstream file("data/Rezervari.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("1,1,101") != string::npos) {
                cout << "Rezervare incarcata corect din fisier: " << line << endl;
                break;
            }
        }
        file.close();
    } else {
        cout << "Eroare: Nu s-a putut deschide Rezervari.txt pentru verificare." << endl;
    }

    return 0;
}
