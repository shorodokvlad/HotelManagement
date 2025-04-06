#ifndef CAMERA_H
#define CAMERA_H

#include <string>

class Camera {
private:
    int numarCamera;
    std::string tipCamera;
    int etaj;
    double pretNoapte;
    bool esteOcupata;
    bool areAerConditionat;
    bool areWiFi;
    bool areTV;
    bool areMinibar;
    int capacitateMaxima;
    std::string checkInDate;
    std::string checkOutDate;
    std::string curatenieStatus;

public:
    // Constructori
    Camera();
    Camera(int numar, const std::string& tip, int etaj, double pret, bool ocupata,
           bool aerCond, bool wifi, bool tv, bool minibar, int capacitate,
           const std::string& checkIn, const std::string& checkOut, const std::string& curatenie);
    ~Camera();

    // Getteri și setteri
    int getNumarCamera() const;
    void setNumarCamera(int numar);

    std::string getTipCamera() const;
    void setTipCamera(const std::string& tip);

    int getEtaj() const;
    void setEtaj(int etaj);

    double getPretNoapte() const;
    void setPretNoapte(double pret);

    bool getEsteOcupata() const;
    void setEsteOcupata(bool status);

    bool getAreAerConditionat() const;
    void setAreAerConditionat(bool status);

    bool getAreWiFi() const;
    void setAreWiFi(bool status);

    bool getAreTV() const;
    void setAreTV(bool status);

    bool getAreMinibar() const;
    void setAreMinibar(bool status);

    int getCapacitateMaxima() const;
    void setCapacitateMaxima(int capacitate);

    std::string getCheckInDate() const;
    void setCheckInDate(const std::string& data);

    std::string getCheckOutDate() const;
    void setCheckOutDate(const std::string& data);

    std::string getCuratenieStatus() const;
    void setCuratenieStatus(const std::string& status);

    // Metode specifice
    bool esteDisponibila(const std::string& dataCheckIn, const std::string& dataCheckOut) const;
    double calculeazaPretTotal(int numarNopti) const;
    void actualizeazaStatusCuratenie(const std::string& status);

    // Metoda toString
    std::string toString() const;

    // Operatori de I/O
    friend std::ostream& operator<<(std::ostream& out, const Camera& camera);
    friend std::istream& operator>>(std::istream& in, Camera& camera);
};

#endif // CAMERA_H
