#include "Rezervare.h"
#include <iostream>

Rezervare::Rezervare(int idRezervare, Client* client, Camera* camera,
                     const std::tm& dataCheckIn, const std::tm& dataCheckOut, const std::string& status)
    : idRezervare(idRezervare), client(client), camera(camera),
      dataCheckIn(dataCheckIn), dataCheckOut(dataCheckOut), status(status) {

    if (!esteDataValidă()) {
        std::cerr << "Eroare: Data Check-out este inainte de Data Check-in!" << std::endl;
        return;
    }

    calculeazaNumarNopti();
    calculeazaTotalPlata();
}

bool Rezervare::esteDataValidă() const {
    // Verificăm dacă Check-out este după Check-in
    if (dataCheckOut.tm_year < dataCheckIn.tm_year) return false;
    if (dataCheckOut.tm_year == dataCheckIn.tm_year) {
        if (dataCheckOut.tm_mon < dataCheckIn.tm_mon) return false;
        if (dataCheckOut.tm_mon == dataCheckIn.tm_mon) {
            if (dataCheckOut.tm_mday < dataCheckIn.tm_mday) return false;
        }
    }
    return true; // Data Check-out este validă
}

void Rezervare::calculeazaNumarNopti() {
    if (!esteDataValidă()) return;  // Dacă datele sunt invalide, nu calculăm

    // Calculăm diferența de zile între Check-in și Check-out
    int zileCheckIn = dataCheckIn.tm_year * 365 + dataCheckIn.tm_mon * 30 + dataCheckIn.tm_mday;
    int zileCheckOut = dataCheckOut.tm_year * 365 + dataCheckOut.tm_mon * 30 + dataCheckOut.tm_mday;

    // Calculăm diferența de zile (număr de nopți)
    numarNopti = zileCheckOut - zileCheckIn;
}

void Rezervare::calculeazaTotalPlata() {
    totalPlata = numarNopti * camera->getPretNoapte();
}

int Rezervare::getIdRezervare() const { return idRezervare; }
int Rezervare::getNumarNopti() const { return numarNopti; }
double Rezervare::getTotalPlata() const { return totalPlata; }
std::string Rezervare::getStatus() const { return status; }

std::string Rezervare::toString() const {
    return "Id Rezervare: " + std::to_string(idRezervare) + "\n" +
           "Client: " + client->getNume() + " " + client->getPrenume() + "\n" +
           "Camera: " + std::to_string(camera->getNumarCamera()) + " " + camera->getTipCamera() + "\n" +
           "Check-in: " + std::to_string(dataCheckIn.tm_mday) + "-" + std::to_string(dataCheckIn.tm_mon + 1) + "-" + std::to_string(dataCheckIn.tm_year + 1900) + "\n" +
           "Check-out: " + std::to_string(dataCheckOut.tm_mday) + "-" + std::to_string(dataCheckOut.tm_mon + 1) + "-" + std::to_string(dataCheckOut.tm_year + 1900) + "\n" +
           "Status: " + status;
}

std::ostream& operator<<(std::ostream& out, const Rezervare& rezervare) {
    out << rezervare.toString();
    return out;
}


std::istream& operator>>(std::istream& in, Rezervare& rezervare) {
    std::cout << "Introduceti id rezervare: ";
    in >> rezervare.idRezervare;

    std::cout << "Introduceti id client: ";
    int idClient;
    in >> idClient;
    // presupunem că avem deja un client
    // rezervare.client = client (clientul poate fi adus dintr-o lista sau baza de date)

    std::cout << "Introduceti numarul camerei: ";
    int numarCamera;
    in >> numarCamera;
    // presupunem că avem deja o camera
    // rezervare.camera = camera (camera poate fi selectata dintr-o lista)

    std::cout << "Introduceti data check-in (zi luna an): ";
    in >> rezervare.dataCheckIn.tm_mday >> rezervare.dataCheckIn.tm_mon >> rezervare.dataCheckIn.tm_year;

    std::cout << "Introduceti data check-out (zi luna an): ";
    in >> rezervare.dataCheckOut.tm_mday >> rezervare.dataCheckOut.tm_mon >> rezervare.dataCheckOut.tm_year;

    std::cout << "Introduceti statusul: ";
    in.ignore(); // pentru a ignora newline-ul rămas
    std::getline(in, rezervare.status);

    rezervare.calculeazaNumarNopti();
    rezervare.calculeazaTotalPlata();

    return in;
}
