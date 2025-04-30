#include "Hotel.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Hotel::Hotel() : nextClientId(1) {}

void Hotel::adaugaClient() {
    string nume, prenume, CNP, telefon;
    cout << "Introduceti prenumele: ";
    getchar();
    getline(cin, prenume);
    cout << "Introduceti numele: ";
    getline(cin, nume);
    cout << "Introduceti CNP-ul: ";
    getline(cin, CNP);
    cout << "Introduceti telefonul: ";
    getline(cin, telefon);

    if (!Client::valideazaTelefon(telefon)) {
        cout << "Numar de telefon invalid! Trebuie sa aiba 10 cifre si sa inceapa cu 07." << endl;
        return;
    }
    if (!Client::valideazaCNP(CNP)) {
        cout << "CNP invalid! Trebuie sa aiba 13 cifre." << endl;
        return;
    }

    try {
        clienti.emplace_back(nextClientId++, nume, prenume, CNP, telefon);
        salveazaClienti();
        cout << "Client adaugat cu succes! ID: " << clienti.back().getIdClient() << endl;
    } catch (const invalid_argument& e) {
        cout << "Eroare: " << e.what() << endl;
    }
}

Client* Hotel::obtineClientDupaId(int id) {
    for (auto& client : clienti) {
        if (client.getIdClient() == id) return &client;
    }
    return nullptr;
}

void Hotel::incarcaClienti() {
    ifstream file("data/Clienti.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Clienti.txt" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, nume, prenume, CNP, telefon;
        getline(ss, idStr, ',');
        getline(ss, nume, ',');
        getline(ss, prenume, ',');
        getline(ss, CNP, ',');
        getline(ss, telefon, ',');
        try {
            int id = stoi(idStr);
            clienti.emplace_back(id, nume, prenume, CNP, telefon);
            if (id >= nextClientId) nextClientId = id + 1;
        } catch (const exception& e) {
            continue;
        }
    }
    file.close();
}

void Hotel::salveazaClienti() {
    ofstream file("data/Clienti.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Clienti.txt" << endl;
        return;
    }
    for (const auto& client : clienti) {
        file << client.getIdClient() << "," << client.getNume() << "," << client.getPrenume() << ","
             << client.getCNP() << "," << client.getTelefon() << "\n";
    }
    file.close();
}

void Hotel::adaugaCamera(int numarCamera, const string& tipCamera, double pretNoapte,
                        bool areAerConditionat, bool areWiFi, bool areTV, bool areMinibar) {
    if (numarCamera == -1) {
        cout << "Introduceti numarul camerei: ";
        cin >> numarCamera;
        getchar();

        string inputTipCamera;
        cout << "Introduceti tipul camerei (ex. Single, Double): ";
        getline(cin, inputTipCamera);
        while (inputTipCamera.empty()) {
            cout << "Tipul camerei nu poate fi gol. Introduceti din nou: ";
            getline(cin, inputTipCamera);
        }

        cout << "Introduceti pretul pe noapte: ";
        cin >> pretNoapte;
        getchar();

        char input;
        cout << "Are aer conditionat? (d/N): ";
        cin >> input;
        areAerConditionat = (input == 'd' || input == 'D');
        getchar();

        cout << "Are WiFi? (d/N): ";
        cin >> input;
        areWiFi = (input == 'd' || input == 'D');
        getchar();

        cout << "Are TV? (d/N): ";
        cin >> input;
        areTV = (input == 'd' || input == 'D');
        getchar();

        cout << "Are minibar? (d/N): ";
        cin >> input;
        areMinibar = (input == 'd' || input == 'D');
        getchar();
    } else {
        if (tipCamera.empty()) {
            cout << "Eroare: Tipul camerei nu poate fi gol." << endl;
            return;
        }
        if (pretNoapte <= 0) {
            cout << "Eroare: Pretul pe noapte trebuie sa fie pozitiv." << endl;
            return;
        }
    }

    for (const auto& room : camere) {
        if (room.getNumarCamera() == numarCamera) {
            cout << "Camera cu numarul " << numarCamera << " exista deja." << endl;
            return;
        }
    }
    camere.emplace_back(numarCamera, tipCamera, pretNoapte, false, areAerConditionat, areWiFi, areTV, areMinibar);
    salveazaCamere();
    cout << "Camera adaugata cu succes!" << endl;
}

Camera* Hotel::obtineCameraDupaNumar(int numarCamera) {
    for (auto& camera : camere) {
        if (camera.getNumarCamera() == numarCamera) return &camera;
    }
    return nullptr;
}

void Hotel::incarcaCamere() {
    ifstream file("data/Camere.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Camere.txt" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string numarStr, tipCamera, pretStr, ocupataStr, acStr, wifiStr, tvStr, minibarStr;
        getline(ss, numarStr, ',');
        getline(ss, tipCamera, ',');
        getline(ss, pretStr, ',');
        getline(ss, ocupataStr, ',');
        getline(ss, acStr, ',');
        getline(ss, wifiStr, ',');
        getline(ss, tvStr, ',');
        getline(ss, minibarStr, ',');
        try {
            int numar = stoi(numarStr);
            double pret = stod(pretStr);
            bool ocupata = stoi(ocupataStr);
            bool ac = stoi(acStr);
            bool wifi = stoi(wifiStr);
            bool tv = stoi(tvStr);
            bool minibar = stoi(minibarStr);
            camere.emplace_back(numar, tipCamera, pret, ocupata, ac, wifi, tv, minibar);
        } catch (const exception& e) {
            continue;
        }
    }
    file.close();
}

void Hotel::salveazaCamere() {
    ofstream file("data/Camere.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Camere.txt" << endl;
        return;
    }
    for (const auto& room : camere) {
        file << room.getNumarCamera() << "," << room.getTipCamera() << "," << room.getPretNoapte() << ","
             << room.getEsteOcupata() << "," << room.getAreAerConditionat() << "," << room.getAreWiFi() << ","
             << room.getAreTV() << "," << room.getAreMinibar() << "\n";
    }
    file.close();
}
