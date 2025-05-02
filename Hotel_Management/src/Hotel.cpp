#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "Hotel.h"
#include "Data.h"

using namespace std;

Hotel::Hotel() : nextClientId(1), nextRezervareId(1) {}

int Hotel::calculeazaNrNopti(const Data& checkIn, const Data& checkOut) {
    int zile = 0;
    Data temp = checkIn;
    while (temp < checkOut) {
        int maxZile = temp.getZileInLuna();
        temp.zi++;
        if (temp.zi > maxZile) {
            temp.zi = 1;
            temp.luna++;
            if (temp.luna > 12) {
                temp.luna = 1;
                temp.an++;
            }
        }
        zile++;
    }
    return zile;
}

double Hotel::calculeazaPretTotal(int nrNopti, double pretNoapte) {
    return nrNopti * pretNoapte;
}

Data Hotel::citesteData() {
    int zi, luna, an;
    scanf("%d.%d.%d", &zi, &luna, &an);
    return Data(zi, luna, an);
}

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

    if (!Client::validareTelefon(telefon)) {
        cout << "Numar de telefon invalid! Trebuie sa aiba 10 cifre." << endl;
        return;
    }
    if (!Client::validareCNP(CNP)) {
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
void Hotel::salveazaDate() {
    salveazaClienti();
    salveazaCamere();
    salveazaRezervari();
}

Client* Hotel::obtineClientDupaId(int id) {
    for (auto& client : clienti) {
        if (client.getIdClient() == id) return &client;
    }
    return nullptr;
}

bool Hotel::areRezervareSuprapusa(int numarCamera, const Data& checkIn, const Data& checkOut) const {
    for (const auto& res : rezervari) {
        if (res.getIdCamera() == numarCamera && res.getStare() != StareRezervare::Anulata && res.getStare() != StareRezervare::CheckOut) {
            if (checkIn < res.getCheckOut() && res.getCheckIn() < checkOut) {
                return true;
            }
        }
    }
    return false;
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

void Hotel::creeazaRezervare(int idClient, int numarCamera, const Data& checkIn, const Data& checkOut) {
    Client* client = obtineClientDupaId(idClient);
    if (!client) {
        cout << "Eroare: Clientul cu ID " << idClient << " nu exista." << endl;
        return;
    }

    Camera* camera = obtineCameraDupaNumar(numarCamera);
    if (!camera) {
        cout << "Eroare: Camera cu numarul " << numarCamera << " nu exista." << endl;
        return;
    }

    if (!checkIn.esteValida() || !checkOut.esteValida()) {
        cout << "Eroare: Datele de check-in sau check-out nu sunt valide." << endl;
        return;
    }

    if (!(checkIn < checkOut)) {
        cout << "Eroare: Data de check-out trebuie sa fie mai mare decat data de check-in." << endl;
        return;
    }

    int nrNopti = calculeazaNrNopti(checkIn, checkOut);
    double pretTotal = calculeazaPretTotal(nrNopti, camera->getPretNoapte());

    rezervari.emplace_back(nextRezervareId++, idClient, numarCamera, checkIn, checkOut,
                           StareRezervare::InAsteptare, nrNopti, pretTotal);
    salveazaRezervari();
    cout << "Rezervare creata cu succes! ID: " << rezervari.back().getIdRezervare() << endl;
}

void Hotel::incarcaRezervari() {
    ifstream file("data/Rezervari.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Rezervari.txt" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, idClientStr, idCameraStr, checkInZi, checkInLuna, checkInAn,
               checkOutZi, checkOutLuna, checkOutAn, stareStr, nrNoptiStr, pretTotalStr;
        getline(ss, idStr, ',');
        getline(ss, idClientStr, ',');
        getline(ss, idCameraStr, ',');
        getline(ss, checkInZi, ',');
        getline(ss, checkInLuna, ',');
        getline(ss, checkInAn, ',');
        getline(ss, checkOutZi, ',');
        getline(ss, checkOutLuna, ',');
        getline(ss, checkOutAn, ',');
        getline(ss, stareStr, ',');
        getline(ss, nrNoptiStr, ',');
        getline(ss, pretTotalStr, ',');
        try {
            int id = stoi(idStr);
            int idClient = stoi(idClientStr);
            int idCamera = stoi(idCameraStr);
            Data checkIn(stoi(checkInZi), stoi(checkInLuna), stoi(checkInAn));
            Data checkOut(stoi(checkOutZi), stoi(checkOutLuna), stoi(checkOutAn));
            StareRezervare stare;
            int stareInt = stoi(stareStr);
            switch (stareInt) {
                case 0: stare = StareRezervare::InAsteptare; break;
                case 1: stare = StareRezervare::Confirmata; break;
                case 2: stare = StareRezervare::CheckIn; break;
                case 3: stare = StareRezervare::CheckOut; break;
                case 4: stare = StareRezervare::Anulata; break;
                default: continue;
            }
            int nrNopti = stoi(nrNoptiStr);
            double pretTotal = stod(pretTotalStr);
            rezervari.emplace_back(id, idClient, idCamera, checkIn, checkOut, stare, nrNopti, pretTotal);
            if (id >= nextRezervareId) nextRezervareId = id + 1;
        } catch (const exception& e) {
            continue;
        }
    }
    file.close();
}

void Hotel::salveazaRezervari() {
    ofstream file("data/Rezervari.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Rezervari.txt" << endl;
        return;
    }
    for (const auto& res : rezervari) {
        string stareStr;
        switch (res.getStare()) {
            case StareRezervare::InAsteptare: stareStr = "InAsteptare"; break;
            case StareRezervare::Confirmata: stareStr = "Confirmata"; break;
            case StareRezervare::CheckIn: stareStr = "CheckIn"; break;
            case StareRezervare::CheckOut: stareStr = "CheckOut"; break;
            case StareRezervare::Anulata: stareStr = "Anulata"; break;
        }
        file << res.getIdRezervare() << "," << res.getIdClient() << "," << res.getIdCamera() << ","
             << res.getCheckIn().zi << "," << res.getCheckIn().luna << "," << res.getCheckIn().an << ","
             << res.getCheckOut().zi << "," << res.getCheckOut().luna << "," << res.getCheckOut().an << ","
             << stareStr << "," << res.getNrNopti() << "," << res.getPretTotal() << "\n";
    }
    file.close();
}

void Hotel::afiseazaClienti() {
    if (clienti.empty()) {
        cout << "Nu exista clienti inregistrati." << endl;
        return;
    }
    cout << "Lista clienti:" << endl;
    for (const auto& client : clienti) {
        cout << client.toString() << "----------------" << endl;
    }
}

void Hotel::afiseazaToateCamerele() {
    if (camere.empty()) {
        cout << "Nu exista camere inregistrate." << endl;
        return;
    }
    cout << "Lista camere:" << endl;
    for (const auto& camera : camere) {
        cout << camera.toString() << "----------------" << endl;
    }
}

void Hotel::afiseazaRezervari() {
    if (rezervari.empty()) {
        cout << "Nu exista rezervari inregistrate." << endl;
        return;
    }
    cout << "Lista rezervari:" << endl;
    for (const auto& rezervare : rezervari) {
        cout << rezervare.toString() << "----------------" << endl;
    }
}
void Hotel::afiseazaCamereLibere() {
    cout << "Introduceti data de inceput(DD.MM.YYYY): ";
    Data startData = citesteData();
    cout << "Introduceti data de sfarsit(DD.MM.YYYY): ";
    Data endData = citesteData();

    if (!startData.esteValida() || !endData.esteValida() || !(startData < endData)) {
        cout << "Eroare: Interval de date invalid." << endl;
        return;
    }

    system("cls");
    bool found = false;

    cout << "Camere libere in perioada " << startData.toString() << " - " << endData.toString() << ":" << endl;
    cout << "\n";
    cout << left << setw(8) << "Numar" << setw(12) << "Tip" << setw(14) << "Pret/noapte" << setw(8) << "WiFi" << setw(6) << "TV" << setw(9) << "Minibar" << setw(10) << "AerCond." << endl;
    cout << string(67, '-') << endl;

    for (const auto& room : camere) {
        if (!areRezervareSuprapusa(room.getNumarCamera(), startData, endData)) {
            cout << left << setw(8) << room.getNumarCamera()
                 << setw(12) << room.getTipCamera()
                 << setw(14) << room.getPretNoapte()
                 << setw(8) << (room.getAreWiFi() ? "Da" : "Nu")
                 << setw(6) << (room.getAreTV() ? "Da" : "Nu")
                 << setw(9) << (room.getAreMinibar() ? "Da" : "Nu")
                 << setw(10) << (room.getAreAerConditionat() ? "Da" : "Nu") << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Nu exista camere libere in perioada specificata.\n";
    }
}


void Hotel::afiseazaCamereOcupate() {
    cout << "Introduceti data de inceput(DD.MM.YYYY): ";
    Data startData = citesteData();
    cout << "Introduceti data de sfarsit(DD.MM.YYYY): ";
    Data endData = citesteData();

    if (!startData.esteValida() || !endData.esteValida() || !(startData < endData)) {
        cout << "Eroare: Interval de date invalid." << endl;
        return;
    }

    system("cls");
    bool found = false;

    cout << "Camere ocupate in perioada " << startData.toString() << " - " << endData.toString() << ":" << endl;
    cout << "\n";
    cout << left << setw(8) << "Numar" << setw(12) << "Tip" << setw(14) << "Pret/noapte" << setw(8) << "WiFi" << setw(6) << "TV" << setw(9) << "Minibar" << setw(10) << "AerCond." << endl;
    cout << string(67, '-') << endl;

    for (const auto& room : camere) {
        if (areRezervareSuprapusa(room.getNumarCamera(), startData, endData)) {
            cout << left << setw(8) << room.getNumarCamera()
                 << setw(12) << room.getTipCamera()
                 << setw(14) << room.getPretNoapte()
                 << setw(8) << (room.getAreWiFi() ? "Da" : "Nu")
                 << setw(6) << (room.getAreTV() ? "Da" : "Nu")
                 << setw(9) << (room.getAreMinibar() ? "Da" : "Nu")
                 << setw(10) << (room.getAreAerConditionat() ? "Da" : "Nu") << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Nu exista camere ocupate in perioada specificata.\n";
    }
}

void Hotel::gestioneazaRezervare(int idRezervare, StareRezervare nouaStare) {
    for (auto& rezervare : rezervari) {
        if (rezervare.getIdRezervare() == idRezervare) {
            switch (nouaStare) {
                case StareRezervare::Confirmata:
                    if (rezervare.getStare() == StareRezervare::InAsteptare) {
                        rezervare.setStare(StareRezervare::Confirmata);
                        salveazaDate();
                        cout << "Rezervare confirmata cu succes!" << endl;
                    } else {
                        cout << "Rezervarea nu este in stare InAsteptare." << endl;
                    }
                    break;
                case StareRezervare::Anulata:
                    if (rezervare.getStare() != StareRezervare::Anulata && rezervare.getStare() != StareRezervare::CheckOut) {
                        rezervare.setStare(StareRezervare::Anulata);
                        Camera* camera = obtineCameraDupaNumar(rezervare.getIdCamera());
                        if (camera) {
                            bool esteIncaOcupata = false;
                            for (const auto& altaRezervare : rezervari) {
                                if (altaRezervare.getIdCamera() == rezervare.getIdCamera() && altaRezervare.getIdRezervare() != idRezervare &&
                                    altaRezervare.getStare() != StareRezervare::Anulata && altaRezervare.getStare() != StareRezervare::CheckOut) {
                                    esteIncaOcupata = true;
                                    break;
                                }
                            }
                            if (!esteIncaOcupata) {
                                camera->setOcupata(false);
                            }
                        }
                        salveazaDate();
                        cout << "Rezervare anulata cu succes!" << endl;
                    } else {
                        cout << "Rezervarea este deja anulata sau finalizata." << endl;
                    }
                    break;
                case StareRezervare::CheckIn:
                    if (rezervare.getStare() == StareRezervare::Confirmata) {
                        rezervare.setStare(StareRezervare::CheckIn);
                        salveazaDate();
                        cout << "Check-in realizat cu succes!" << endl;
                    } else {
                        cout << "Rezervarea nu este in stare Confirmata." << endl;
                    }
                    break;
                case StareRezervare::CheckOut:
                    if (rezervare.getStare() == StareRezervare::CheckIn) {
                        rezervare.setStare(StareRezervare::CheckOut);
                        Camera* camera = obtineCameraDupaNumar(rezervare.getIdCamera());
                        if (camera) {
                            bool esteIncaOcupata = false;
                            for (const auto& altaRezervare : rezervari) {
                                if (altaRezervare.getIdCamera() == rezervare.getIdCamera() && altaRezervare.getIdRezervare() != idRezervare &&
                                    altaRezervare.getStare() != StareRezervare::Anulata && altaRezervare.getStare() != StareRezervare::CheckOut) {
                                    esteIncaOcupata = true;
                                    break;
                                }
                            }
                            if (!esteIncaOcupata) {
                                camera->setOcupata(false);
                            }
                        }
                        salveazaDate();
                        cout << "Check-out realizat cu succes!" << endl;
                    } else {
                        cout << "Rezervarea nu este in stare CheckIn." << endl;
                    }
                    break;
                default:
                    cout << "Stare invalida." << endl;
                    break;
            }
            return;
        }
    }
    cout << "Rezervare cu ID-ul " << idRezervare << " nu a fost gasita." << endl;
}


void Hotel::modificaRezervare(int idRezervare, int idClient, int numarCamera, const Data& checkIn, const Data& checkOut) {
    for (auto& rezervare : rezervari) {
        if (rezervare.getIdRezervare() == idRezervare) {
            // Verificăm dacă rezervarea este într-o stare modificabilă
            if (rezervare.getStare() != StareRezervare::InAsteptare && rezervare.getStare() != StareRezervare::Confirmata) {
                cout << "Eroare: Rezervarea nu poate fi modificata." << endl;
                return;
            }

            // Verificăm clientul
            Client* client = obtineClientDupaId(idClient);
            if (!client) {
                cout << "Eroare: Clientul cu ID " << idClient << " nu exista." << endl;
                return;
            }

            // Verificăm camera
            Camera* camera = obtineCameraDupaNumar(numarCamera);
            if (!camera) {
                cout << "Eroare: Camera cu numarul " << numarCamera << " nu exista." << endl;
                return;
            }

            // Verificăm validitatea datelor
            if (!checkIn.esteValida() || !checkOut.esteValida()) {
                cout << "Eroare: Datele de check-in sau check-out nu sunt valide." << endl;
                return;
            }

            if (!(checkIn < checkOut)) {
                cout << "Eroare: Data de check-out trebuie sa fie mai mare decat data de check-in." << endl;
                return;
            }

            // Verificăm suprapunerile (excluzând rezervarea curentă)
            for (const auto& altaRezervare : rezervari) {
                if (altaRezervare.getIdRezervare() != idRezervare &&
                    altaRezervare.getIdCamera() == numarCamera &&
                    altaRezervare.getStare() != StareRezervare::Anulata &&
                    altaRezervare.getStare() != StareRezervare::CheckOut) {
                    if (checkIn < altaRezervare.getCheckOut() && altaRezervare.getCheckIn() < checkOut) {
                        cout << "Eroare: Camera este deja rezervata in acest interval." << endl;
                        return;
                    }
                }
            }

            // Calculăm noile valori
            int nrNopti = calculeazaNrNopti(checkIn, checkOut);
            double pretTotal = calculeazaPretTotal(nrNopti, camera->getPretNoapte());

            // Actualizăm rezervarea
            rezervare.setIdClient(idClient);
            rezervare.setIdCamera(numarCamera);
            rezervare.setCheckIn(checkIn);
            rezervare.setCheckOut(checkOut);
            rezervare.setNrNopti(nrNopti);
            rezervare.setPretTotal(pretTotal);

            salveazaDate();
            cout << "Rezervarea " << idRezervare << " a fost modificata cu succes!" << endl;
            return;
        }
    }
    cout << "Eroare: Rezervarea cu ID " << idRezervare << " nu a fost gasita." << endl;
}
