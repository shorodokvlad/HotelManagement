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
