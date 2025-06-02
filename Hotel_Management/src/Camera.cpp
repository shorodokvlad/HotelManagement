#include "Camera.h"
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

void setColorCamera(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Camera::Camera(int _nrCamera, const string& _tipCamera, double _pretNoate, bool _esteOcupata, bool _areAC,
               bool _areWifi, bool _areTV, bool _areMiniBar)
    : numarCamera(_nrCamera), tipCamera(_tipCamera), pretNoapte(_pretNoate), esteOcupata(_esteOcupata),
      areAerConditionat(_areAC), areWiFi(_areWifi), areTV(_areTV), areMinibar(_areMiniBar) {}

int Camera::getNumarCamera() const
{
    return numarCamera;
}
string Camera::getTipCamera() const
{
    return tipCamera;
}
double Camera::getPretNoapte() const
{
    return pretNoapte;
}
bool Camera::getEsteOcupata() const
{
    return esteOcupata;
}
bool Camera::getAreAerConditionat() const
{
    return areAerConditionat;
}
bool Camera::getAreWiFi() const
{
    return areWiFi;
}
bool Camera::getAreTV() const
{
    return areTV;
}
bool Camera::getAreMinibar() const
{
    return areMinibar;
}

void Camera::setOcupata(bool status)
{
    esteOcupata = status;
}

string Camera::toString() const
{
    return "Numar Camera: " + to_string(numarCamera) + "\n" +
           "Tip Camera: " + tipCamera + "\n" +
           "Pret per noapte: " + to_string(pretNoapte) + "\n" +
           "Ocupata: " + (esteOcupata ? "Da" : "Nu") + "\n" +
           "Aer conditionat: " + (areAerConditionat ? "Da" : "Nu") + "\n" +
           "WiFi: " + (areWiFi ? "Da" : "Nu") + "\n" +
           "TV: " + (areTV ? "Da" : "Nu") + "\n" +
           "Minibar: " + (areMinibar ? "Da" : "Nu") + "\n";
}

bool Camera::validareNumarCamera(const string& input, int& numarOut)
{
    for (char c : input)
    {
        if (!isdigit(c))
        {
            setColorCamera(12);
            cout << "\nNumarul camerei trebuie sa contina doar cifre!\n";
            return false;
        }
    }

    numarOut = stoi(input);

    if (numarOut <= 0)
    {
        setColorCamera(12);
        cout << "\nNumarul camerei trebuie sa fie pozitiv!\n";
        return false;
    }

    return true;
}

bool Camera::validarePret(const string& input, double& pretOut)
{
    for (char c : input)
    {
        if (isalpha(c))
        {
            setColorCamera(12);
            cout << "\nPretul nu trebuie sa contina litere!\n";
            return false;
        }
    }

    try
    {
        pretOut = stod(input);
    }
    catch (...)
    {
        setColorCamera(12);
        cout << "\nPretul introdus nu este valid!\n";
        return false;
    }

    if (pretOut <= 0)
    {
        setColorCamera(12);
        cout << "\nPretul trebuie sa fie pozitiv!\n";
        return false;
    }

    return true;
}



ostream& operator<<(ostream& out, const Camera& camera)
{
    out << camera.toString();
    return out;
}

istream& operator>>(istream& in, Camera& camera)
{
    string inputNumar;
    do
    {
        setColorCamera(8);
        cout << "Numar camera: ";
        setColorCamera(14);
        in >> inputNumar;
    }
    while (!Camera::validareNumarCamera(inputNumar, camera.numarCamera));
    in.ignore();

    setColorCamera(8);
    cout << "Tip camera: ";
    setColorCamera(14);
    getline(in, camera.tipCamera);

    string inputPret;
    do
    {
        setColorCamera(8);
        cout << "Pret pe noapte: ";
        setColorCamera(14);
        in >> inputPret;
    }
    while (!Camera::validarePret(inputPret, camera.pretNoapte));

    char raspuns;

    setColorCamera(8);
    cout << "Are aer conditionat? (d/n): ";
    setColorCamera(14);
    in >> raspuns;
    camera.areAerConditionat = (raspuns == 'd' || raspuns == 'D');

    setColorCamera(8);
    cout << "Are WiFi? (d/n): ";
    setColorCamera(14);
    in >> raspuns;
    camera.areWiFi = (raspuns == 'd' || raspuns == 'D');

    setColorCamera(8);
    cout << "Are TV? (d/n): ";
    setColorCamera(14);
    in >> raspuns;
    camera.areTV = (raspuns == 'd' || raspuns == 'D');

    setColorCamera(8);
    cout << "Are minibar? (d/n): ";
    setColorCamera(14);
    in >> raspuns;
    camera.areMinibar = (raspuns == 'd' || raspuns == 'D');

    return in;
}

