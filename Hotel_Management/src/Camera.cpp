#include "Camera.h"
#include <string>

using namespace std;

Camera::Camera(int nc, const string& tc, double pn, bool eo, bool ac, bool w, bool tv, bool mb)
    : numarCamera(nc), tipCamera(tc), pretNoapte(pn), esteOcupata(eo),
      areAerConditionat(ac), areWiFi(w), areTV(tv), areMinibar(mb) {}

int Camera::getNumarCamera() const { return numarCamera; }
string Camera::getTipCamera() const { return tipCamera; }
double Camera::getPretNoapte() const { return pretNoapte; }
bool Camera::getEsteOcupata() const { return esteOcupata; }
void Camera::seteazaOcupata(bool status) { esteOcupata = status; }

bool Camera::getAreAerConditionat() const { return areAerConditionat; }
bool Camera::getAreWiFi() const { return areWiFi; }
bool Camera::getAreTV() const { return areTV; }
bool Camera::getAreMinibar() const { return areMinibar; }

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
