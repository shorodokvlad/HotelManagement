#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include <vector>
#include <iostream>
#include "Hotel.h"
#include "Angajat.h"
#include "Data.h"

using namespace std;

class Administrator {
private:
    string username;
    string encryptedPassword;
    Hotel* hotel;
    vector<Angajat> angajati;
    vector<Camera> camere;
    static int nextAngajatId;

    static string criptareDecriptare(const string& text, char key);
    void verificaSauCreeazaFisierAdmin(const string& defaultUser, const string& defaultPass);

public:
    static const char XOR_KEY = 'K';

    Administrator(Hotel* h, const string& adminFileUser = "admin", const string& adminFilePass = "admin123");
    ~Administrator();

    bool login();
    void salveazaCredentialeNoi(const string& newUsername, const string& newPassword);

    void incarcaAngajati();
    void salveazaDateAngajati() const;
    void adaugaAngajat();
    void afiseazaAngajati() const;
    void schimbaCredentiale();

    double getIncasariPerioada(const Data& start, const Data& end) const;
    void vizualizeazaIncasari() const;

    double getGradOcuparePerioada(const Data& start, const Data& end) const;
    void statisticiGradOcupare() const;
};

#endif // ADMINISTRATOR_H
