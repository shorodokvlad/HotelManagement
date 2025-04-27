#include "Client.h"
#include "Camera.h"
#include "Rezervare.h"
#include <iostream>

using namespace std;

int main() {
    // Test Client
    Client client(1, "Popescu", "Ion", "1234567890123", "0712345678");
    cout << client.toString() << endl;
    cout << "Telefon 0712345678: " << (Client::valideazaTelefon("0712345678") ? "Valid" : "Invalid") << endl;
    cout << "CNP 1234567890123: " << (Client::valideazaCNP("1234567890123") ? "Valid" : "Invalid") << endl;
    cout << "Telefon 12345: " << (Client::valideazaTelefon("12345") ? "Valid" : "Invalid") << endl;
    cout << "CNP 123: " << (Client::valideazaCNP("123") ? "Valid" : "Invalid") << endl;
    cout << endl;

    // Test Camera
    Camera camera(101, "Single", 100.0, false, true, true, true, false);
    cout << camera.toString() << endl;
    camera.seteazaOcupata(true);
    cout << "Dupa setare ocupata: " << endl;
    cout << "Ocupata: " << (camera.getEsteOcupata() ? "Da" : "Nu") << endl;
    cout << "Numar camera: " << camera.getNumarCamera() << endl;
    cout << "Tip camera: " << camera.getTipCamera() << endl;
    cout << "Pret/noapte: " << camera.getPretNoapte() << endl;
    cout << endl;

    // Test Rezervare
    Data checkIn(1, 5, 2025);
    Data checkOut(3, 5, 2025);
    Rezervare rezervare(1, 1, 101, checkIn, checkOut, StareRezervare::InAsteptare, 2, 200.0);
    cout << rezervare.toString() << endl;
    rezervare.seteazaStare(StareRezervare::Confirmata);
    cout << "Dupa setare stare Confirmata: " << endl;
    cout << "Stare: " << rezervare.stareToString() << endl;
    cout << "Check-In valid: " << (rezervare.getCheckIn().esteValida() ? "Valid" : "Invalid") << endl;
    cout << "Check-Out mai mare decat Check-In: " << (rezervare.getCheckIn().esteMaiMicaDecat(rezervare.getCheckOut()) ? "True" : "False") << endl;

    return 0;
}
