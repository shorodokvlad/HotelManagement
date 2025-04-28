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

    // Test calculeazaNrNopti
    cout << "Test calculeazaNrNopti:" << endl;
    Data data1(1, 5, 2025);
    Data data2(3, 5, 2025);
    cout << "1.05.2025 - 3.05.2025: " << calculeazaNrNopti(data1, data2) << " nopti (asteptat: 2)" << endl;
    Data data3(30, 4, 2025);
    Data data4(2, 5, 2025);
    cout << "30.04.2025 - 2.05.2025: " << calculeazaNrNopti(data3, data4) << " nopti (asteptat: 2)" << endl;
    Data data5(28, 2, 2024);
    Data data6(1, 3, 2024);
    cout << "28.02.2024 - 1.03.2024: " << calculeazaNrNopti(data5, data6) << " nopti (asteptat: 2)" << endl;
    cout << endl;

    // Test calculeazaPretTotal
    cout << "Test calculeazaPretTotal:" << endl;
    cout << "2 nopti la 100 RON/noapte: " << calculeazaPretTotal(2, 100.0) << " RON (asteptat: 200)" << endl;
    cout << "3 nopti la 150 RON/noapte: " << calculeazaPretTotal(3, 150.0) << " RON (asteptat: 450)" << endl;
    return 0;
}
