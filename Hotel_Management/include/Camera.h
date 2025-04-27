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
    Camera(int nc, const string& tc, double pn, bool eo, bool ac, bool w, bool tv, bool mb);
    int getNumarCamera() const;
    string getTipCamera() const;
    double getPretNoapte() const;
    bool getEsteOcupata() const;
    void seteazaOcupata(bool status);
    bool getAreAerConditionat() const;
    bool getAreWiFi() const;
    bool getAreTV() const;
    bool getAreMinibar() const;
    string toString() const;
};

#endif
