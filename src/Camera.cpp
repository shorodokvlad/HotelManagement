#include "Camera.h"

// Constructor implicit
Camera::Camera()
    : numarCamera(0), tipCamera(""), pretNoapte(0.0), esteOcupata(false),
      areAerConditionat(false), areWiFi(false), areTV(false), areMinibar(false) {}

// Constructor cu parametri
Camera::Camera(int numarCamera, const std::string& tipCamera, double pretNoapte,
               bool esteOcupata, bool areAerConditionat, bool areWiFi, bool areTV, bool areMinibar)
    : numarCamera(numarCamera), tipCamera(tipCamera), pretNoapte(pretNoapte),
      esteOcupata(esteOcupata), areAerConditionat(areAerConditionat),
      areWiFi(areWiFi), areTV(areTV), areMinibar(areMinibar) {}

// Getteri și setteri
int Camera::getNumarCamera() const {
    return numarCamera;
}

void Camera::setNumarCamera(int numarCamera) {
    this->numarCamera = numarCamera;
}

std::string Camera::getTipCamera() const {
    return tipCamera;
}

void Camera::setTipCamera(const std::string& tipCamera) {
    this->tipCamera = tipCamera;
}

double Camera::getPretNoapte() const {
    return pretNoapte;
}

void Camera::setPretNoapte(double pretNoapte) {
    this->pretNoapte = pretNoapte;
}

bool Camera::getEsteOcupata() const {
    return esteOcupata;
}

void Camera::setEsteOcupata(bool esteOcupata) {
    this->esteOcupata = esteOcupata;
}

bool Camera::getAreAerConditionat() const {
    return areAerConditionat;
}

void Camera::setAreAerConditionat(bool areAerConditionat) {
    this->areAerConditionat = areAerConditionat;
}

bool Camera::getAreWiFi() const {
    return areWiFi;
}

void Camera::setAreWiFi(bool areWiFi) {
    this->areWiFi = areWiFi;
}

bool Camera::getAreTV() const {
    return areTV;
}

void Camera::setAreTV(bool areTV) {
    this->areTV = areTV;
}

bool Camera::getAreMinibar() const {
    return areMinibar;
}

void Camera::setAreMinibar(bool areMinibar) {
    this->areMinibar = areMinibar;
}

// Metoda toString
std::string Camera::toString() const {
    return "Numar Camera: " + std::to_string(numarCamera) + "\n" +
           "Tip Camera: " + tipCamera + "\n" +
           "Pret per noapte: " + std::to_string(pretNoapte) + "\n" +
           "Status ocupare: " + (esteOcupata ? "Ocupata" : "Libera") + "\n" +
           "Aer conditionat: " + (areAerConditionat ? "Da" : "Nu") + "\n" +
           "WiFi: " + (areWiFi ? "Da" : "Nu") + "\n" +
           "TV: " + (areTV ? "Da" : "Nu") + "\n" +
           "Minibar: " + (areMinibar ? "Da" : "Nu");
}

// Operator << (ostream)
std::ostream& operator<<(std::ostream& out, const Camera& camera) {
    out << camera.toString();
    return out;
}

// Operator >> (istream)
std::istream& operator>>(std::istream& in, Camera& camera) {
    std::cout << "Introduceti numarul camerei: ";
    in >> camera.numarCamera;

    std::cout << "Introduceti tipul camerei: ";
    in >> camera.tipCamera;

    std::cout << "Introduceti pretul per noapte: ";
    in >> camera.pretNoapte;

    std::cout << "Este camera ocupata? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.esteOcupata;

    std::cout << "Are aer conditionat? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areAerConditionat;

    std::cout << "Are WiFi? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areWiFi;

    std::cout << "Are TV? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areTV;

    std::cout << "Are minibar? (1 pentru Da, 0 pentru Nu): ";
    in >> camera.areMinibar;

    return in;
}
