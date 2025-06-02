#include "Hotel.h"
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <conio.h>
#include <windows.h>

using namespace std;

void setColorHotel(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int Hotel::nextClientId = 1;
int Hotel::nextRezervareId = 1;

Hotel::Hotel() {}

int Hotel::calculeazaNrNopti(const Data& checkIn, const Data& checkOut) {
    int zile = 0;
    Data temp = checkIn;

    while (temp < checkOut) {
        int maxZile = temp.getZileInLuna(temp.luna, temp.an);

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
    Data data;
    setColorHotel(14);
    cin >> data;
    return data;
}

void Hotel::adaugaClient() {
    Client client;
    cin >> client;

    for (const auto& c : clienti) {
        if (c.getCNP() == client.getCNP()) {
            setColorHotel(12);
            cout << "\nEroare: Exista deja un client cu acest CNP. ID: " << c.getIdClient() << endl;
            return;
        }
    }

    client.setIdClient(nextClientId++);
    clienti.push_back(client);
    salveazaDate();

    setColorHotel(10);
    cout << "\nClient adaugat cu succes! ID: " << client.getIdClient() << endl;
}

int Hotel::validareNumar(const string& mesaj) {
    string input;
    bool valid = false;

    while (!valid) {
        setColorHotel(8);
        cout << mesaj;
        setColorHotel(14);
        cin >> input;

        valid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            setColorHotel(12);
            cout << "\nEroare: Trebuie sa introduceti un numar!\n";
        }
    }

    return stoi(input);
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
    Camera camera;
    cin >> camera;

    for (const auto& room : camere) {
        if (room.getNumarCamera() == camera.getNumarCamera()) {
            cout << "Camera cu numarul " << camera.getNumarCamera() << " exista deja." << endl;
            return;
        }
    }

    camere.push_back(camera);
    salveazaDate();
    setColorHotel(10);
    cout << "\nCamera adaugata cu succes!" << endl;
}

void Hotel::incarcaClienti() {
    ifstream file("data/Clienti.txt");
    if (!file.is_open()) {
        setColorHotel(12);
        cerr << "\nEroare la deschiderea Clienti.txt" << endl;
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
        cerr << "\nEroare la deschiderea Camere.txt" << endl;
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
        cerr << "\nEroare la deschiderea Rezervari.txt" << endl;
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
    ofstream file("data/Clienti.txt");
    if (!file.is_open()) {
        cerr << "\nEroare la deschiderea Clienti.txt" << endl;
        return;
    }
    for (const auto& client : clienti) {
        file << client.getIdClient() << "," << client.getNume() << "," << client.getPrenume() << ","
             << client.getCNP() << "," << client.getTelefon() << "\n";
    }
    file.close();
}

void Hotel::salveazaCamere() {
    ofstream file("data/Camere.txt");
    if (!file.is_open()) {
        cerr << "\nEroare la deschiderea Camere.txt" << endl;
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
    ofstream file("data/Rezervari.txt");
    if (!file.is_open()) {
        cerr << "\nEroare la deschiderea Rezervari.txt" << endl;
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
        cout << "\nNu exista clienti inregistrati." << endl;
        return;
    }

    const int clientiPePagina = 46;
    int totalPagini = (clienti.size() + clientiPePagina - 1) / clientiPePagina;
    int paginaCurenta = 1;
    int tasta;

    do {
        system("cls");

        int start = (paginaCurenta - 1) * clientiPePagina;
        int end = min(start + clientiPePagina, (int)clienti.size());

        // Antet
        setColorHotel(3);
        cout << left << setw(6) << "ID" << setw(15) << "Prenume" << setw(15) << "Nume"
             << setw(20) << "CNP" << setw(15) << "Telefon" << endl;
        cout << string(71, '-') << endl;

        // Afișare clienți
        setColorHotel(8);
        for (int i = start; i < end; ++i) {
            const auto& client = clienti[i];
            cout << left << setw(6) << client.getIdClient()
                 << setw(15) << client.getPrenume()
                 << setw(15) << client.getNume()
                 << setw(20) << client.getCNP()
                 << setw(15) << client.getTelefon() << endl;
        }

        // Bara de paginare
        setColorHotel(7);
        cout << "\nNavigare: ";
        if (paginaCurenta > 1) cout << "< ";
        for (int i = 1; i <= totalPagini; ++i) {
            if (i == paginaCurenta)
                cout << "[" << i << "] ";
            else
                cout << i << " ";
        }
        if (paginaCurenta < totalPagini) cout << ">";

        cout << "\n\nFoloseste sageti <- -> pentru navigare, ESC pentru iesire.";

        tasta = _getch();

        if (tasta == 224) {
            int tastaSpeciala = _getch();
            if (tastaSpeciala == 75 && paginaCurenta > 1)
                paginaCurenta--;
            else if (tastaSpeciala == 77 && paginaCurenta < totalPagini)
                paginaCurenta++;
        }

    } while (tasta != 27);
     system("cls");
}



void Hotel::afiseazaToateCamerele() {
    if (camere.empty()) {
        cout << "Nu exista camere inregistrate." << endl;
        return;
    }
    setColorHotel(14);
    cout << left << setw(8) << "Numar" << setw(12) << "Tip" << setw(14) << "Pret/noapte" << setw(8) << "WiFi" << setw(6) << "TV" << setw(9) << "Minibar" << setw(10) << "AerCond." << endl;
    cout << string(65, '-') << endl;
    for (const auto& room : camere) {
        setColorHotel(8);
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
    setColorHotel(8);
    cout << "Introduceti data de inceput (DD.MM.YYYY): ";
    setColorHotel(14);
    Data startData = citesteData();
    setColorHotel(8);
    cout << "Introduceti data de sfarsit (DD.MM.YYYY): ";
    setColorHotel(14);
    Data endData = citesteData();

    if (!startData.esteValida() || !endData.esteValida() || !(startData < endData)) {
        setColorHotel(12);
        cout << "Eroare: Interval de date invalid." << endl;
        return;
    }

    system("cls");
    bool found = false;
    setColorHotel(3);
    cout << "Camere libere in perioada " << startData.toString() << " - " << endData.toString() << ":" << endl;
    cout << "\n";
    setColorHotel(14);
    cout << left << setw(8) << "Numar" << setw(12) << "Tip" << setw(14) << "Pret/noapte" << setw(8) << "WiFi" << setw(6) << "TV" << setw(9) << "Minibar" << setw(10) << "AerCond." << endl;
    cout << string(67, '-') << endl;

    for (const auto& room : camere) {
        if (!areRezervareSuprapusa(room.getNumarCamera(), startData, endData)) {
            setColorHotel(8);
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
        setColorHotel(12);
        cout << "Nu exista camere libere in perioada specificata." << endl;
    }
}

void Hotel::afiseazaCamereOcupate() {
    setColorHotel(8);
    cout << "Introduceti data de inceput (DD.MM.YYYY): ";
    setColorHotel(14);
    Data startData = citesteData();
    setColorHotel(8);
    cout << "Introduceti data de sfarsit (DD.MM.YYYY): ";
    setColorHotel(14);
    Data endData = citesteData();

    if (!startData.esteValida() || !endData.esteValida() || !(startData < endData)) {
        setColorHotel(12);
        cout << "Eroare: Interval de date invalid." << endl;
        return;
    }

    system("cls");
    bool found = false;
    setColorHotel(3);
    cout << "Camere ocupate in perioada " << startData.toString() << " - " << endData.toString() << ":" << endl;
    cout << "\n";
    setColorHotel(14);
    cout << left << setw(8) << "Numar" << setw(12) << "Tip" << setw(14) << "Pret/noapte" << setw(8) << "WiFi" << setw(6) << "TV" << setw(9) << "Minibar" << setw(10) << "AerCond." << endl;
    cout << string(67, '-') << endl;

    for (const auto& camera : camere) {
        if (areRezervareSuprapusa(camera.getNumarCamera(), startData, endData)) {
            setColorHotel(8);
            cout << left << setw(8) << camera.getNumarCamera()
                 << setw(12) << camera.getTipCamera()
                 << setw(14) << camera.getPretNoapte()
                 << setw(8) << (camera.getAreWiFi() ? "Da" : "Nu")
                 << setw(6) << (camera.getAreTV() ? "Da" : "Nu")
                 << setw(9) << (camera.getAreMinibar() ? "Da" : "Nu")
                 << setw(10) << (camera.getAreAerConditionat() ? "Da" : "Nu") << endl;
            found = true;
        }
    }

    if (!found) {
        setColorHotel(12);
        cout << "\nNu exista camere ocupate in perioada specificata." << endl;
    }
}

void Hotel::adaugaRezervare() {

    int clientId = validareNumar("Introduceti ID-ul clientului: ");

    if (!getClientDupaId(clientId)) {
        setColorHotel(12);
        cout << "Eroare: Clientul cu ID-ul " << clientId << " nu exista." << endl;
        return;
    }

    if (!getClientDupaId(clientId)) {
        setColorHotel(12);
        cout << "Eroare: Clientul cu ID-ul " << clientId << " nu exista." << endl;
        return;
    }

    int numarCamera = validareNumar("Introduceti numarul camerei: ");

    Camera* camera = getCameraDupaNumar(numarCamera);
    if (!camera) {
        setColorHotel(12);
        cout << "Eroare: Camera cu numarul " << numarCamera << " nu exista." << endl;
        return;
    }

    setColorHotel(8);
    cout << "Introduceti data de check-in (DD.MM.YYYY): ";
    Data checkIn = citesteData();
    if (!checkIn.esteValida()) {
        setColorHotel(12);
        cout << "Eroare: Data de check-in invalida." << endl;
        return;
    }

    Data dataCurenta = Data::getDataCurenta();
    if (checkIn < dataCurenta) {
        setColorHotel(12);
        cout << "Eroare: Data de check-in nu poate fi in trecut." << endl;
        return;
    }

    setColorHotel(8);
    cout << "Introduceti data de check-out (DD.MM.YYYY): ";
    Data checkOut = citesteData();
    if (!checkOut.esteValida()) {
        setColorHotel(12);
        cout << "Eroare: Data de check-out invalida." << endl;
        return;
    }

    for (const auto& rezervare : rezervari) {
        if (rezervare.getIdClient() == clientId &&
            rezervare.getStare() != StareRezervare::Anulata &&
            rezervare.getStare() != StareRezervare::CheckOut) {
            setColorHotel(12);
            cout << "Eroare: Clientul cu ID-ul " << clientId << " are deja o rezervare activa cu ID-ul " << rezervare.getIdRezervare() << "." << endl;
            return;
        }
    }

    if (!(checkIn < checkOut)) {
        setColorHotel(12);
        cout << "Eroare: Data de check-in trebuie sa fie inainte de data de check-out." << endl;
        return;
    }
    if (areRezervareSuprapusa(numarCamera, checkIn, checkOut)) {
        setColorHotel(12);
        cout << "Eroare: Camera este ocupata in perioada selectata." << endl;
        return;
    }
    int nrNopti = calculeazaNrNopti(checkIn, checkOut);
    double pretTotal = calculeazaPretTotal(nrNopti, camera->getPretNoapte());

    rezervari.emplace_back(nextRezervareId++, clientId, numarCamera, checkIn, checkOut, StareRezervare::InAsteptare, nrNopti, pretTotal);
    camera->setOcupata(true);
    salveazaDate();

    setColorHotel(10);
    cout << "\nRezervare adaugata cu succes! ID: " << rezervari.back().getIdRezervare() << endl;
}

void Hotel::afiseazaRezervari() {
    int lunaSelectata;
    const string numeLuni[] = {"", "Ianuarie", "Februarie", "Martie", "Aprilie", "Mai", "Iunie",
                               "Iulie", "August", "Septembrie", "Octombrie", "Noiembrie", "Decembrie"};

    cout << "Vizualizare rezervari pe luni: \n";
    setColorHotel(3);
    cout << "1. Ianuarie\n2. Februarie\n3. Martie\n4. Aprilie\n5. Mai\n6. Iunie\n"
         << "7. Iulie\n8. August\n9. Septembrie\n10. Octombrie\n11. Noiembrie\n12. Decembrie\n";
    setColorHotel(8);
    cout << "Introduceti luna (1-12): ";
    setColorHotel(14);
    cin >> lunaSelectata;

    if (lunaSelectata < 1 || lunaSelectata > 12) {
        setColorHotel(12);
        cout << "Luna invalida! Va rugam introduceti o valoare intre 1 si 12." << endl;
        return;
    }

    vector<Rezervare> rezervariFiltrate;
    for (const auto& res : rezervari) {
        if (res.getCheckIn().getLuna() == lunaSelectata) {
            rezervariFiltrate.push_back(res);
        }
    }

    if (rezervariFiltrate.empty()) {
        system("cls");
        setColorHotel(12);
        cout << "Nu exista rezervari inregistrate pentru luna selectata." << endl;
        return;
    }

    const int rezervariPePagina = 43;
    int totalPagini = (rezervariFiltrate.size() + rezervariPePagina - 1) / rezervariPePagina;
    int paginaCurenta = 1;
    int tasta;

    Data dataCurenta = Data::getDataCurenta();
    do {
        system("cls");

        setColorHotel(3);
        cout << string(46, '-');
        cout << "Rezervari " << numeLuni[lunaSelectata] <<" " << dataCurenta.getAn();
        cout << string(46, '-') << "\n\n";

        // Antet tabel
        setColorHotel(14);
        cout << left << setw(6) << "ID" << setw(8) << "Camera" << setw(12) << "ID Client"
             << setw(12) << "Prenume" << setw(12) << "Nume" << setw(12) << "Check-In"
             << setw(12) << "Check-Out" << setw(15) << "Stare" << setw(8) << "Nopti"
             << setw(10) << "Pret(RON)" << endl;
        cout << string(105, '-') << endl;

        // Afișare rezervări paginat
        int start = (paginaCurenta - 1) * rezervariPePagina;
        int end = min(start + rezervariPePagina, (int)rezervariFiltrate.size());

        for (int i = start; i < end; ++i) {
            const auto& res = rezervariFiltrate[i];
            string prenume = "N/A", nume = "N/A";
            for (const auto& client : clienti) {
                if (client.getIdClient() == res.getIdClient()) {
                    prenume = client.getPrenume();
                    nume = client.getNume();
                    break;
                }
            }

            setColorHotel(8);
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

        // Navigare pagini
        setColorHotel(7);
        cout << "\nNavigare: ";
        if (paginaCurenta > 1) cout << "< ";
        for (int i = 1; i <= totalPagini; ++i) {
            if (i == paginaCurenta)
                cout << "[" << i << "] ";
            else
                cout << i << " ";
        }
        if (paginaCurenta < totalPagini) cout << ">";

        // Mesaj navigare
        cout << "\n\nFoloseste sageti <- -> pentru navigare, ESC pentru iesire.";

        // Așteaptă tastă
        tasta = _getch();
        if (tasta == 224) {
            int tastaSpeciala = _getch();
            if (tastaSpeciala == 75 && paginaCurenta > 1)
                paginaCurenta--;
            else if (tastaSpeciala == 77 && paginaCurenta < totalPagini)
                paginaCurenta++;
        }

    } while (tasta != 27);
    system("cls");
}

void Hotel::modificaStareRezervare(StareRezervare nouaStare) {
    int idRezervare = validareNumar("Introduceti ID-ul rezervarii: ");

    for (auto& rezervare : rezervari) {
        if (rezervare.getIdRezervare() == idRezervare) {
            switch (nouaStare) {
                case StareRezervare::Confirmata:
                    if (rezervare.getStare() == StareRezervare::InAsteptare) {
                        rezervare.setStare(StareRezervare::Confirmata);
                        salveazaDate();
                        setColorHotel(10);
                        cout << "\nRezervare confirmata cu succes!" << endl;
                    } else {
                        setColorHotel(12);
                        cout << "\nRezervarea nu este in starea: In Asteptare." << endl;
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
                        setColorHotel(10);
                        cout << "\nRezervare anulata cu succes!" << endl;
                    } else {
                        setColorHotel(12);
                        cout << "\nRezervarea este deja anulata sau finalizata." << endl;
                    }
                    break;
                case StareRezervare::CheckIn:
                    if (rezervare.getStare() == StareRezervare::Confirmata) {
                        Data dataCurenta = Data::getDataCurenta();
                        if (rezervare.getCheckIn().getZi() == dataCurenta.getZi() &&
                            rezervare.getCheckIn().getLuna() == dataCurenta.getLuna() &&
                            rezervare.getCheckIn().getAn() == dataCurenta.getAn()) {
                            rezervare.setStare(StareRezervare::CheckIn);
                            salveazaDate();
                            setColorHotel(10);
                            cout << "\nCheck-in realizat cu succes!" << endl;
                        } else {
                            setColorHotel(12);
                            cout << "\nEroare: Check-in-ul se poate realiza doar in data de check-in specificata (" << rezervare.getCheckIn().toString() << ")." << endl;
                        }
                    } else {
                        setColorHotel(12);
                        cout << "\nRezervarea nu este in stare Confirmata." << endl;
                    }
                    break;
                case StareRezervare::CheckOut:
                    if (rezervare.getStare() == StareRezervare::CheckIn) {
                        Data dataCurenta = Data::getDataCurenta();
                        if (rezervare.getCheckOut().getZi() == dataCurenta.getZi() &&
                            rezervare.getCheckOut().getLuna() == dataCurenta.getLuna() &&
                            rezervare.getCheckOut().getAn() == dataCurenta.getAn()) {
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
                            setColorHotel(10);
                            cout << "\nCheck-out realizat cu succes!" << endl;
                        } else {
                            setColorHotel(12);
                            cout << "\nEroare: Check-out-ul se poate realiza doar in data de check-out specificata (" << rezervare.getCheckOut().toString() << ")." << endl;
                        }
                    } else {
                        setColorHotel(12);
                        cout << "\nRezervarea nu este in stare CheckIn." << endl;
                    }
                    break;
                default:
                    setColorHotel(12);
                    cout << "Stare invalida." << endl;
                    break;
            }
            return;
        }
    }
    setColorHotel(12);
    cout << "\nRezervare cu ID-ul " << idRezervare << " nu a fost gasita." << endl;
}

void Hotel::modificaRezervare() {

    int idRezervare = validareNumar("Introduceti ID-ul rezervarii de modificat: ");
    int idClient = validareNumar("Introduceti ID-ul clientului: ");
    int numarCamera = validareNumar("Introduceti numarul camerei: ");

    setColorHotel(8);
    cout << "Introduceti data de check-in (DD.MM.YYYY): ";
    setColorHotel(14);
    Data checkIn = citesteData();

    setColorHotel(8);
    cout << "Introduceti data de check-out (DD.MM.YYYY): ";
    setColorHotel(8);
    Data checkOut = citesteData();

    for (auto& rezervare : rezervari) {
        if (rezervare.getIdRezervare() == idRezervare) {
            if (rezervare.getStare() != StareRezervare::InAsteptare && rezervare.getStare() != StareRezervare::Confirmata) {
                setColorHotel(12);
                cout << "\nEroare: Rezervarea nu poate fi modificata." << endl;
                return;
            }

            Client* client = getClientDupaId(idClient);
            if (!client) {
                setColorHotel(12);
                cout << "\nEroare: Clientul cu ID " << idClient << " nu exista." << endl;
                return;
            }

            Camera* camera = getCameraDupaNumar(numarCamera);
            if (!camera) {
                setColorHotel(12);
                cout << "\nEroare: Camera cu numarul " << numarCamera << " nu exista." << endl;
                return;
            }

            if (!checkIn.esteValida() || !checkOut.esteValida()) {
                setColorHotel(12);
                cout << "\nEroare: Datele de check-in sau check-out nu sunt valide." << endl;
                return;
            }

            if (!(checkIn < checkOut)) {
                setColorHotel(12);
                cout << "\nEroare: Data de check-out trebuie sa fie mai mare decat data de check-in." << endl;
                return;
            }

            for (const auto& altaRezervare : rezervari) {
                if (altaRezervare.getIdRezervare() != idRezervare &&
                    altaRezervare.getIdCamera() == numarCamera &&
                    altaRezervare.getStare() != StareRezervare::Anulata &&
                    altaRezervare.getStare() != StareRezervare::CheckOut) {
                    if (checkIn < altaRezervare.getCheckOut() && altaRezervare.getCheckIn() < checkOut) {
                        setColorHotel(12);
                        cout << "\nEroare: Camera este deja rezervata in acest interval." << endl;
                        return;
                    }
                }
            }

            int nrNopti = calculeazaNrNopti(checkIn, checkOut);
            double pretTotal = calculeazaPretTotal(nrNopti, camera->getPretNoapte());

            rezervare.setIdClient(idClient);
            rezervare.setIdCamera(numarCamera);
            rezervare.setCheckIn(checkIn);
            rezervare.setCheckOut(checkOut);
            rezervare.setNrNopti(nrNopti);
            rezervare.setPretTotal(pretTotal);

            salveazaDate();
            setColorHotel(10);
            cout << "\nRezervarea " << idRezervare << " a fost modificata cu succes!" << endl;
            return;
        }
    }
    setColorHotel(10);
    cout << "\nEroare: Rezervarea cu ID " << idRezervare << " nu a fost gasita." << endl;
}
