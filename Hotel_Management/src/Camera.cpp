#include "Camera.h"
#include <iostream>

using namespace std;

// Constructor implicit
Camera::Camera()
    : numarCamera(0), tipCamera(""), etaj(0), pretNoapte(0.0),
      esteOcupata(false), areAerConditionat(false), areWiFi(false),
      areTV(false), areMinibar(false), capacitateMaxima(0),
      checkInDate(""), checkOutDate(""), curatenieStatus("") {}

// Constructor cu parametri
Camera::Camera(int numar, const string& tip, int etaj, double pret, bool ocupata,
               bool aerCond, bool wifi, bool tv, bool minibar, int capacitate,
               const string& checkIn, const string& checkOut, const string& curatenie)
    : numarCamera(numar), tipCamera(tip), etaj(etaj), pretNoapte(pret),
      esteOcupata(ocupata), areAerConditionat(aerCond), areWiFi(wifi),
      areTV(tv), areMinibar(minibar), capacitateMaxima(capacitate),
      checkInDate(checkIn), checkOutDate(checkOut), curatenieStatus(curatenie) {}

// Destructor
Camera::~Camera() {}

// Getteri și setteri
int Camera::getNumarCamera() const { return numarCamera; }
void Camera::setNumarCamera(int numar) { numarCamera = numar; }

string Camera::getTipCamera() const { return tipCamera; }
void Camera::setTipCamera(const string& tip) { tipCamera = tip; }

int Camera::getEtaj() const { return etaj; }
void Camera::setEtaj(int etaj) { this->etaj = etaj; }

double Camera::getPretNoapte() const { return pretNoapte; }
void Camera::setPretNoapte(double pret) { pretNoapte = pret; }

bool Camera::getEsteOcupata() const { return esteOcupata; }
void Camera::setEsteOcupata(bool status) { esteOcupata = status; }

bool Camera::getAreAerConditionat() const { return areAerConditionat; }
void Camera::setAreAerConditionat(bool status) { areAerConditionat = status; }

bool Camera::getAreWiFi() const { return areWiFi; }
void Camera::setAreWiFi(bool status) { areWiFi = status; }

bool Camera::getAreTV() const { return areTV; }
void Camera::setAreTV(bool status) { areTV = status; }

bool Camera::getAreMinibar() const { return areMinibar; }
void Camera::setAreMinibar(bool status) { areMinibar = status; }

int Camera::getCapacitateMaxima() const { return capacitateMaxima; }
void Camera::setCapacitateMaxima(int capacitate) { capacitateMaxima = capacitate; }

string Camera::getCheckInDate() const { return checkInDate; }
void Camera::setCheckInDate(const string& data) { checkInDate = data; }

string Camera::getCheckOutDate() const { return checkOutDate; }
void Camera::setCheckOutDate(const string& data) { checkOutDate = data; }

string Camera::getCuratenieStatus() const { return curatenieStatus; }
void Camera::setCuratenieStatus(const string& status) { curatenieStatus = status; }

// Metode specifice
bool Camera::esteDisponibila(const string& dataCheckIn, const string& dataCheckOut) const {
    return !esteOcupata;
}

double Camera::calculeazaPretTotal(int numarNopti) const {
    return pretNoapte * numarNopti;
}

void Camera::actualizeazaStatusCuratenie(const string& status) {
    curatenieStatus = status;
}

// Metoda toString
string Camera::toString() const {
    return "Numar Camera: " + to_string(numarCamera) + "\n" +
           "Tip Camera: " + tipCamera + "\n" +
           "Etaj: " + to_string(etaj) + "\n" +
           "Pret per noapte: " + to_string(pretNoapte) + "\n" +
           "Status ocupare: " + (esteOcupata ? "Ocupata" : "Libera") + "\n" +
           "Aer conditionat: " + (areAerConditionat ? "Da" : "Nu") + "\n" +
           "WiFi: " + (areWiFi ? "Da" : "Nu") + "\n" +
           "TV: " + (areTV ? "Da" : "Nu") + "\n" +
           "Minibar: " + (areMinibar ? "Da" : "Nu") + "\n" +
           "Capacitate maxima: " + to_string(capacitateMaxima) + "\n" +
           "Check-in: " + checkInDate + "\n" +
           "Check-out: " + checkOutDate + "\n" +
           "Status curatenie: " + curatenieStatus;
}

// Operator << (ostream)
ostream& operator<<(ostream& out, const Camera& camera) {
    out << camera.toString();
    return out;
}

// Operator >> (istream)
istream& operator>>(istream& in, Camera& camera) {
    cout << "Introduceti numarul camerei: ";
    in >> camera.numarCamera;

    cout << "Introduceti tipul camerei: ";
    in >> camera.tipCamera;

    cout << "Introduceti etajul: ";
    in >> camera.etaj;

    cout << "Introduceti pretul per noapte: ";
    in >> camera.pretNoapte;

    cout << "Este camera ocupata? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.esteOcupata;

    cout << "Are aer conditionat? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areAerConditionat;

    cout << "Are WiFi? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areWiFi;

    cout << "Are TV? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areTV;

    cout << "Are minibar? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areMinibar;

    cout << "Introduceti capacitatea maxima: ";
    in >> camera.capacitateMaxima;

    cout << "Introduceti data check-in (format: DD-MM-YYYY): ";
    in >> camera.checkInDate;

    cout << "Introduceti data check-out (format: DD-MM-YYYY): ";
    in >> camera.checkOutDate;

    cout << "Introduceti statusul curateniei: ";
    in >> camera.curatenieStatus;

    return in;
}
