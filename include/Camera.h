#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <iostream>

class Camera {
private:
    int numarCamera;
    std::string tipCamera;
    double pretNoapte;
    bool esteOcupata;
    bool areAerConditionat;
    bool areWiFi;
    bool areTV;
    bool areMinibar;

public:
    // Constructori
    Camera();
    Camera(int numarCamera, const std::string& tipCamera, double pretNoapte,
           bool esteOcupata, bool areAerConditionat, bool areWiFi, bool areTV, bool areMinibar);

    // Getteri și setteri
    int getNumarCamera() const;
    void setNumarCamera(int numarCamera);

    std::string getTipCamera() const;
    void setTipCamera(const std::string& tipCamera);

    double getPretNoapte() const;
    void setPretNoapte(double pretNoapte);

    bool getEsteOcupata() const;
    void setEsteOcupata(bool esteOcupata);

    bool getAreAerConditionat() const;
    void setAreAerConditionat(bool areAerConditionat);

    bool getAreWiFi() const;
    void setAreWiFi(bool areWiFi);

    bool getAreTV() const;
    void setAreTV(bool areTV);

    bool getAreMinibar() const;
    void setAreMinibar(bool areMinibar);

    // Metoda toString
    std::string toString() const;

    // Operator << (ostream)
    friend std::ostream& operator<<(std::ostream& out, const Camera& camera);

    // Operator >> (istream)
    friend std::istream& operator>>(std::istream& in, Camera& camera);
};

#endif // CAMERA_H
