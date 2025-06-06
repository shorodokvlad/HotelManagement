#ifndef CAMERA_H
#define CAMERA_H

#include <string>

using namespace std;

class Camera {
private:
    int numarCamera;
    string tipCamera;
    double pretNoapte;
    bool esteOcupata;
    bool areAerConditionat;
    bool areWiFi;
    bool areTV;
    bool areMinibar;
public:
    Camera() : numarCamera(0), tipCamera(""), pretNoapte(0.0), esteOcupata(false), areAerConditionat(false), areWiFi(false), areTV(false), areMinibar(false) {}
    Camera(int _nrCamera, const string& _tipCamera, double _pretNoate, bool _esteOcupata, bool _areAC, bool _areWifi, bool _areTV, bool _areMiniBar);
    int getNumarCamera() const;
    string getTipCamera() const;
    double getPretNoapte() const;
    bool getEsteOcupata() const;
    void setOcupata(bool status);
    bool getAreAerConditionat() const;
    bool getAreWiFi() const;
    bool getAreTV() const;
    bool getAreMinibar() const;

    string toString() const;

    static bool validareNumarCamera(const string& input, int& numarOut);
    static bool validarePret(const string& input, double& pretOut);

    friend ostream& operator<<(ostream& out, const Camera& camera);
    friend istream& operator>>(istream& in, Camera& camera);

};

#endif
