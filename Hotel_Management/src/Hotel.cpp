#include "Hotel.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>

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

    for (const auto& client : clienti) {
        if (client.getCNP() == CNP) {
            cout << "Eroare: Exista deja un client cu acest CNP. ID: " << client.getIdClient() << endl;
            return;
        }
    }

    try {
        clienti.emplace_back(nextClientId++, nume, prenume, CNP, telefon);
        salveazaDate();
        cout << "Client adaugat cu succes! ID: " << clienti.back().getIdClient() << endl;
    } catch (const invalid_argument& e) {
        cout << "Eroare: " << e.what() << endl;
    }
}

Client* Hotel::getClientDupaId(int id) {
    for (auto& client : clienti) {
        if (client.getIdClient() == id) return &client;
    }
    return nullptr;
}

Camera* Hotel::getCameraDupaNumar(int numarCamera) {
    for (auto& camera : camere) {
        if (camera.getNumarCamera() == numarCamera) return &camera;
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

void Hotel::adaugaCamera() {
    int numarCamera;
    string tipCamera;
    double pretNoapte;
    bool areAerConditionat, areWiFi, areTV, areMinibar;

    cout << "Introduceti numarul camerei: ";
    cin >> numarCamera;
    getchar();

    cout << "Introduceti tipul camerei (ex. Single, Double): ";
    getline(cin, tipCamera);
    while (tipCamera.empty()) {
        cout << "Tipul camerei nu poate fi gol. Introduceti din nou: ";
        getline(cin, tipCamera);
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

    if (tipCamera.empty()) {
        cout << "Eroare: Tipul camerei nu poate fi gol." << endl;
        return;
    }
    if (pretNoapte <= 0) {
        cout << "Eroare: Pretul pe noapte trebuie sa fie pozitiv." << endl;
        return;
    }

    for (const auto& room : camere) {
        if (room.getNumarCamera() == numarCamera) {
            cout << "Camera cu numarul " << numarCamera << " exista deja." << endl;
            return;
        }
    }

    camere.emplace_back(numarCamera, tipCamera, pretNoapte, false, areAerConditionat, areWiFi, areTV, areMinibar);
    salveazaDate();
    cout << "Camera adaugata cu succes!" << endl;
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
        getline(ss, telefon);
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
        getline(ss, minibarStr);
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

void Hotel::incarcaRezervari() {
    ifstream file("data/Rezervari.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Rezervari.txt" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idResStr, idClientStr, idCameraStr, checkInStr, checkOutStr, stareStr, nrNoptiStr, pretTotalStr;
        getline(ss, idResStr, ',');
        getline(ss, idClientStr, ',');
        getline(ss, idCameraStr, ',');
        getline(ss, checkInStr, ',');
        getline(ss, checkOutStr, ',');
        getline(ss, stareStr, ',');
        getline(ss, nrNoptiStr, ',');
        getline(ss, pretTotalStr);
        try {
            int idRes = stoi(idResStr);
            int idClient = stoi(idClientStr);
            int idCamera = stoi(idCameraStr);
            int ziIn, lunaIn, anIn;
            sscanf(checkInStr.c_str(), "%d.%d.%d", &ziIn, &lunaIn, &anIn);
            Data checkIn(ziIn, lunaIn, anIn);
            int ziOut, lunaOut, anOut;
            sscanf(checkOutStr.c_str(), "%d.%d.%d", &ziOut, &lunaOut, &anOut);
            Data checkOut(ziOut, lunaOut, anOut);
            StareRezervare stare;
            if (stareStr == "InAsteptare") stare = StareRezervare::InAsteptare;
            else if (stareStr == "Confirmata") stare = StareRezervare::Confirmata;
            else if (stareStr == "CheckIn") stare = StareRezervare::CheckIn;
            else if (stareStr == "CheckOut") stare = StareRezervare::CheckOut;
            else if (stareStr == "Anulata") stare = StareRezervare::Anulata;
            else continue;
            int nrNopti = stoi(nrNoptiStr);
            double pretTotal = stod(pretTotalStr);
            rezervari.emplace_back(idRes, idClient, idCamera, checkIn, checkOut, stare, nrNopti, pretTotal);
            if (idRes >= nextRezervareId) nextRezervareId = idRes + 1;
        } catch (const exception& e) {
            continue;
        }
    }
    file.close();
}

void Hotel::salveazaClienti() {
    filesystem::create_directory("data");
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

void Hotel::salveazaCamere() {
    filesystem::create_directory("data");
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

void Hotel::salveazaRezervari() {
    filesystem::create_directory("data");
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
             << res.getCheckIn().toString() << "," << res.getCheckOut().toString() << ","
             << stareStr << "," << res.getNrNopti() << "," << res.getPretTotal() << "\n";
    }
    file.close();
}

void Hotel::incarcaDate() {
    incarcaClienti();
    incarcaCamere();
    incarcaRezervari();
}

void Hotel::salveazaDate() {
    salveazaClienti();
    salveazaCamere();
    salveazaRezervari();
}

void Hotel::afiseazaClienti() {
    if (clienti.empty()) {
        cout << "Nu exista clienti inregistrati." << endl;
        return;
    }
    cout << left << setw(6) << "ID" << setw(15) << "Prenume" << setw(15) << "Nume" << setw(20) << "CNP" << setw(15) << "Telefon" << endl;
    cout << string(71, '-') << endl;
    for (const auto& client : clienti) {
        cout << left << setw(6) << client.getIdClient()
             << setw(15) << client.getPrenume()
             << setw(15) << client.getNume()
             << setw(20) << client.getCNP()
             << setw(15) << client.getTelefon() << endl;
    }
}

void Hotel::afiseazaToateCamerele() {
    if (camere.empty()) {
        cout << "Nu exista camere inregistrate." << endl;
        return;
    }
    cout << left << setw(8) << "Numar" << setw(12) << "Tip" << setw(14) << "Pret/noapte" << setw(8) << "WiFi" << setw(6) << "TV" << setw(9) << "Minibar" << setw(10) << "AerCond." << endl;
    cout << string(65, '-') << endl;
    for (const auto& room : camere) {
        cout << left << setw(8) << room.getNumarCamera()
             << setw(12) << room.getTipCamera()
             << setw(14) << room.getPretNoapte()
             << setw(8) << (room.getAreWiFi() ? "Da" : "Nu")
             << setw(6) << (room.getAreTV() ? "Da" : "Nu")
             << setw(9) << (room.getAreMinibar() ? "Da" : "Nu")
             << setw(10) << (room.getAreAerConditionat() ? "Da" : "Nu") << endl;
    }
}

void Hotel::afiseazaCamereLibere() {
    cout << "Introduceti data de inceput (DD.MM.YYYY): ";
    Data startData = citesteData();
    cout << "Introduceti data de sfarsit (DD.MM.YYYY): ";
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
        cout << "Nu exista camere libere in perioada specificata." << endl;
    }
}

void Hotel::afiseazaCamereOcupate() {
    cout << "Introduceti data de inceput (DD.MM.YYYY): ";
    Data startData = citesteData();
    cout << "Introduceti data de sfarsit (DD.MM.YYYY): ";
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
        cout << "Nu exista camere ocupate in perioada specificata." << endl;
    }
}

void Hotel::adaugaRezervare() {
    int clientId, numarCamera;
    cout << "Introduceti ID-ul clientului: ";
    cin >> clientId;
    getchar();

    cout << "Introduceti numarul camerei: ";
    cin >> numarCamera;
    getchar();

    cout << "Introduceti data de check-in (DD.MM.YYYY): ";
    Data checkIn = citesteData();
    if (!checkIn.esteValida()) {
        cout << "Eroare: Data de check-in invalida." << endl;
        return;
    }

    cout << "Introduceti data de check-out (DD.MM.YYYY): ";
    Data checkOut = citesteData();
    if (!checkOut.esteValida()) {
        cout << "Eroare: Data de check-out invalida." << endl;
        return;
    }

    if (!getClientDupaId(clientId)) {
        cout << "Eroare: Clientul cu ID-ul " << clientId << " nu exista." << endl;
        return;
    }

    for (const auto& rezervare : rezervari) {
        if (rezervare.getIdClient() == clientId &&
            rezervare.getStare() != StareRezervare::Anulata &&
            rezervare.getStare() != StareRezervare::CheckOut) {
            cout << "Eroare: Clientul cu ID-ul " << clientId << " are deja o rezervare activa cu ID-ul " << rezervare.getIdRezervare() << "." << endl;
            return;
        }
    }

    Camera* camera = getCameraDupaNumar(numarCamera);
    if (!camera) {
        cout << "Eroare: Camera cu numarul " << numarCamera << " nu exista." << endl;
        return;
    }
    if (!(checkIn < checkOut)) {
        cout << "Eroare: Data de check-in trebuie sa fie inainte de data de check-out." << endl;
        return;
    }
    if (areRezervareSuprapusa(numarCamera, checkIn, checkOut)) {
        cout << "Eroare: Camera este ocupata in perioada selectata." << endl;
        return;
    }
    int nrNopti = calculeazaNrNopti(checkIn, checkOut);
    double pretTotal = calculeazaPretTotal(nrNopti, camera->getPretNoapte());
    rezervari.emplace_back(nextRezervareId++, clientId, numarCamera, checkIn, checkOut, StareRezervare::InAsteptare, nrNopti, pretTotal);
    camera->setOcupata(true);
    salveazaDate();
    cout << "Rezervare adaugata cu succes! ID: " << rezervari.back().getIdRezervare() << endl;
}

void Hotel::afiseazaRezervari() {
    if (rezervari.empty()) {
        cout << "Nu exista rezervari inregistrate." << endl;
        return;
    }

    cout << left << setw(6) << "ID" << setw(8) << "Camera" << setw(12) << "ID Client" << setw(12) << "Prenume" << setw(12) << "Nume" << setw(12) << "Check-In"
         << setw(12) << "Check-Out" << setw(15) << "Stare" << setw(8) << "Nopti" << setw(10) << "Pret(RON)" << endl;
    cout << string(105, '-') << endl;

    for (const auto& res : rezervari) {
        string prenume = "N/A", nume = "N/A";
        for (const auto& client : clienti) {
            if (client.getIdClient() == res.getIdClient()) {
                prenume = client.getPrenume();
                nume = client.getNume();
                break;
            }
        }

        cout << left
             << setw(6) << res.getIdRezervare()
             << setw(8) << res.getIdCamera()
             << setw(12) << res.getIdClient()
             << setw(12) << prenume
             << setw(12) << nume
             << setw(12) << res.getCheckIn().toString()
             << setw(12) << res.getCheckOut().toString()
             << setw(15) << res.stareToString()
             << setw(8) << res.getNrNopti()
             << setw(10) << fixed << setprecision(2) << res.getPretTotal()
             << endl;
    }
}

void Hotel::modificaStareRezervare(StareRezervare nouaStare) {
    int idRezervare;
    cout << "Introduceti ID-ul rezervarii: ";
    cin >> idRezervare;

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
                        Camera* camera = getCameraDupaNumar(rezervare.getIdCamera());
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
                        Camera* camera = getCameraDupaNumar(rezervare.getIdCamera());
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


void Hotel::modificaRezervare() {
    cout << "\nModificare rezervare." << endl;
    int idRezervare, idClient, numarCamera;
    cout << "Introduceti ID-ul rezervarii de modificat: ";
    cin >> idRezervare;
    getchar();
    cout << "Introduceti ID-ul clientului: ";
    cin >> idClient;
    getchar();
    cout << "Introduceti numarul camerei: ";
    cin >> numarCamera;
    getchar();
    cout << "Introduceti data de check-in (DD.MM.YYYY): ";
    Data checkIn = citesteData();
    cout << "Introduceti data de check-out (DD.MM.YYYY): ";
    Data checkOut = citesteData();

    for (auto& rezervare : rezervari) {
        if (rezervare.getIdRezervare() == idRezervare) {
            // Verificăm dacă rezervarea este într-o stare modificabilă
            if (rezervare.getStare() != StareRezervare::InAsteptare && rezervare.getStare() != StareRezervare::Confirmata) {
                cout << "Eroare: Rezervarea nu poate fi modificata." << endl;
                return;
            }

            // Verificăm clientul
            Client* client = getClientDupaId(idClient);
            if (!client) {
                cout << "Eroare: Clientul cu ID " << idClient << " nu exista." << endl;
                return;
            }

            // Verificăm camera
            Camera* camera = getCameraDupaNumar(numarCamera);
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
