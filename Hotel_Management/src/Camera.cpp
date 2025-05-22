#include "Camera.h"
#include <string>
#include <iostream>

using namespace std;

Camera::Camera(int _nrCamera, const string& _tipCamera, double _pretNoate, bool _esteOcupata, bool _areAC,
                bool _areWifi, bool _areTV, bool _areMiniBar)
    : numarCamera(_nrCamera), tipCamera(_tipCamera), pretNoapte(_pretNoate), esteOcupata(_esteOcupata),
      areAerConditionat(_areAC), areWiFi(_areWifi), areTV(_areTV), areMinibar(_areMiniBar) {}

int Camera::getNumarCamera() const { return numarCamera; }
string Camera::getTipCamera() const { return tipCamera; }
double Camera::getPretNoapte() const { return pretNoapte; }
bool Camera::getEsteOcupata() const { return esteOcupata; }
bool Camera::getAreAerConditionat() const { return areAerConditionat; }
bool Camera::getAreWiFi() const { return areWiFi; }
bool Camera::getAreTV() const { return areTV; }
bool Camera::getAreMinibar() const { return areMinibar; }

void Camera::setOcupata(bool status) { esteOcupata = status; }

string Camera::toString() const {
    return "Numar Camera: " + to_string(numarCamera) + "\n" +
           "Tip Camera: " + tipCamera + "\n" +
           "Pret per noapte: " + to_string(pretNoapte) + "\n" +
           "Ocupata: " + (esteOcupata ? "Da" : "Nu") + "\n" +
           "Aer conditionat: " + (areAerConditionat ? "Da" : "Nu") + "\n" +
           "WiFi: " + (areWiFi ? "Da" : "Nu") + "\n" +
           "TV: " + (areTV ? "Da" : "Nu") + "\n" +
           "Minibar: " + (areMinibar ? "Da" : "Nu") + "\n";
}

ostream& operator<<(ostream& out, const Camera& camera) {
    out << camera.toString();
    return out;
}

istream& operator>>(istream& in, Camera& camera) {
    cout << "Numar camera: ";
    in >> camera.numarCamera;
    in.ignore();

    cout << "Tip camera: ";
    getline(in, camera.tipCamera);

    cout << "Pret pe noapte: ";
    in >> camera.pretNoapte;

    char raspuns;

    cout << "Are aer conditionat? (d/n): ";
    in >> raspuns;
    camera.areAerConditionat = (raspuns == 'd' || raspuns == 'D');

    cout << "Are WiFi? (d/n): ";
    in >> raspuns;
    camera.areWiFi = (raspuns == 'd' || raspuns == 'D');

    cout << "Are TV? (d/n): ";
    in >> raspuns;
    camera.areTV = (raspuns == 'd' || raspuns == 'D');

    cout << "Are minibar? (d/n): ";
    in >> raspuns;
    camera.areMinibar = (raspuns == 'd' || raspuns == 'D');

    return in;
}

