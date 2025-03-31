#ifndef CLIENT_H
#define CLIENT_H

#include "Persoana.h"
#include <string>
#include <iostream>

class Client : public Persoana {
private:
    int clientID;
    std::string checkInDate;
    std::string checkOutDate;
    int nrNopti;
    std::string metodaPlata;
    double totalPlata;
    bool micDejunInclus;
    std::string cereriSpeciale;

public:
    // Constructor implicit
    Client();

    // Constructor cu parametri
    Client(const string& nume, const string& prenume, const string& CNP, const string& gen, int id, const string& checkIn, const std::string& checkOut,
           int nopti, const string& plata, double total, bool micDejun, const string& cereri);

    // Destructor
    ~Client();

    // Getteri
    int getClientID() const;
    const std::string& getCheckInDate() const;
    const std::string& getCheckOutDate() const;
    int getNrNopti() const;
    const std::string& getMetodaPlata() const;
    double getTotalPlata() const;
    bool isMicDejunInclus() const;
    const std::string& getCereriSpeciale() const;

    // Setteri
    void setClientID(int id);
    void setCheckInDate(const std::string& checkIn);
    void setCheckOutDate(const std::string& checkOut);
    void setNrNopti(int nopti);
    void setMetodaPlata(const std::string& plata);
    void setTotalPlata(double total);
    void setMicDejunInclus(bool inclus);
    void setCereriSpeciale(const std::string& cereri);

    // Metoda toString
    std::string toString() const;

    // Supraincarcare operatori
    friend std::ostream& operator<<(std::ostream& out, const Client& client);
    friend std::istream& operator>>(std::istream& in, Client& client);
};

#endif // CLIENT_H
