#include "Administrator.h"
#include "Hotel.h"
#include "Angajat.h"
#include "Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>

using namespace std;

int Administrator::nextAngajatId = 1;


string Administrator::encryptDecrypt(const string& text, char key) {
    string output = text;
    for (size_t i = 0; i < text.length(); ++i) {
        output[i] = text[i] ^ key;
    }
    return output;
}

void Administrator::ensureAdminFileExists(const string& defaultUser, const string& defaultPass) {
    ifstream file("data/admin_creds.txt");
    if (!file.good()) {
        file.close();
        cout << "Prima rulare sau fisierul de credentiale lipseste." << endl;
        cout << "Se creeaza credentiale default: " << defaultUser << "/" << defaultPass << endl;

        ofstream outfile("data/admin_creds.txt");
        if (outfile.is_open()) {
            outfile << encryptDecrypt(defaultUser, XOR_KEY) << endl;
            outfile << encryptDecrypt(defaultPass, XOR_KEY) << endl;
            outfile.close();
            cout << "Fisierul de credentiale a fost creat cu valorile default." << endl;
        } else {
            cerr << "Eroare: Nu s-a putut crea fisierul de credentiale admin_creds.txt!" << endl;
        }
    } else {
        file.close();
    }
}

Administrator::Administrator(Hotel* h, const string& adminFileUser, const string& adminFilePass) : hotel(h) {
    ensureAdminFileExists(adminFileUser, adminFilePass);
    ifstream file("data/admin_creds.txt");
    if (file.is_open()) {
        getline(file, username);
        getline(file, encryptedPassword);
        file.close();
    } else {
        cerr << "Eroare: Nu s-au putut citi credentialele administratorului!" << endl;
        cerr << "Se folosesc credentialele default compilate." << endl;
        username = encryptDecrypt(adminFileUser, XOR_KEY);
        encryptedPassword = encryptDecrypt(adminFilePass, XOR_KEY);
    }
    incarcaAngajati();
}

Administrator::~Administrator() {
    salveazaDateAngajati();
}

bool Administrator::login() {
    system("cls");
    string inputUser, inputPass;
    cout << "\n--- Login Administrator ---" << endl;
    cout << "Username: ";
    cin >> inputUser;
    cout << "Parola: ";
    cin >> inputPass;

    if (encryptDecrypt(inputUser, XOR_KEY) == username && encryptDecrypt(inputPass, XOR_KEY) == encryptedPassword) {
        cout << "Login reusit!" << endl;
        return true;
    } else {
        cout << "Username sau parola incorecta!" << endl;
        return false;
    }
}

void Administrator::salveazaCredentialeNoi(const string& newUsername, const string& newPassword) {
    username = encryptDecrypt(newUsername, XOR_KEY);
    encryptedPassword = encryptDecrypt(newPassword, XOR_KEY);
    ofstream file("data/admin_creds.txt");
    if (file.is_open()) {
        file << username << endl;
        file << encryptedPassword << endl;
        file.close();
        cout << "Noile credentiale au fost salvate." << endl;
    } else {
        cerr << "Eroare: Nu s-au putut salva noile credentiale!" << endl;
    }
}

void Administrator::incarcaAngajati() {
    ifstream file("data/Angajati.txt");
    if (!file.is_open()) {
        return;
    }
    angajati.clear();
    string line;
    int maxId = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, nume, prenume, cnp, functie, salariuStr, dataAngStr;

        if (!getline(ss, idStr, ',')) continue;
        if (!getline(ss, nume, ',')) continue;
        if (!getline(ss, prenume, ',')) continue;
        if (!getline(ss, cnp, ',')) continue;
        if (!getline(ss, functie, ',')) continue;
        if (!getline(ss, salariuStr, ',')) continue;
        if (!getline(ss, dataAngStr)) continue;

        try {
            int id = stoi(idStr);
            double salariu = stod(salariuStr);

            int zi, luna, an;
            if (sscanf(dataAngStr.c_str(), "%d.%d.%d", &zi, &luna, &an) != 3) {
                 cerr << "Eroare la parsarea datei pentru angajat: " << dataAngStr << endl;
                 continue;
            }
            Data dataAngajare(zi, luna, an);
            if (!dataAngajare.esteValida()) {
                cerr << "Data angajare invalida pentru angajat: " << dataAngStr << endl;
                continue;
            }

            angajati.emplace_back(id, nume, prenume, cnp, functie, salariu, dataAngajare);
            if (id > maxId) {
                maxId = id;
            }
        } catch (const std::invalid_argument& ia) {
            cerr << "Argument invalid la conversie: " << ia.what() << " pe linia: " << line << endl;
        } catch (const std::out_of_range& oor) {
            cerr << "Valoare in afara intervalului la conversie: " << oor.what() << " pe linia: " << line << endl;
        }
    }
    nextAngajatId = maxId + 1;
    file.close();
}

void Administrator::salveazaDateAngajati() const {
    ofstream file("data/Angajati.txt");
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea Angajati.txt pentru salvare!" << endl;
        return;
    }
    for (const auto& angajat : angajati) {
        file << angajat.getIdAngajat() << ","
             << angajat.getNume() << ","
             << angajat.getPrenume() << ","
             << angajat.getCNP() << ","
             << angajat.getFunctie() << ","
             << angajat.getSalariu() << ","
             << angajat.getDataAngajare().toString() << endl;
    }
    file.close();
}

void Administrator::adaugaAngajat() {
    Angajat angajatNou;
    cin >> angajatNou;

    for (const auto& ang : angajati) {
        if (ang.getCNP() == angajatNou.getCNP()) {
            cout << "Eroare: Un angajat cu acest CNP (" << angajatNou.getCNP() << ") exista deja (ID: " << ang.getIdAngajat() << ")." << endl;
            return;
        }
    }
    if (angajatNou.getNume().empty() || angajatNou.getPrenume().empty() ||
        angajatNou.getCNP().empty() || !Persoana::validareCNP(angajatNou.getCNP()) ||
        angajatNou.getFunctie().empty() || angajatNou.getSalariu() < 0 || !angajatNou.getDataAngajare().esteValida() ) {
        cout << "Datele introduse pentru angajat nu sunt complete sau valide. Angajatul nu a fost adaugat." << endl;
        return;
    }

    angajatNou.setIdAngajat(nextAngajatId++);
    angajati.push_back(angajatNou);
    cout << "Angajat adaugat cu succes! ID: " << angajatNou.getIdAngajat() << endl;
    salveazaDateAngajati();
}

void Administrator::afiseazaAngajati() const {
    cout << "\n--- Lista Angajati ---" << endl;
    if (angajati.empty()) {
        cout << "Nu exista angajati inregistrati." << endl;
        return;
    }
    cout << left
              << setw(6) << "ID" << setw(15) << "Nume" << setw(15) << "Prenume"
              << setw(15) << "CNP" << setw(20) << "Functie" << setw(12) << "Salariu(RON)"
              << setw(12) << "Data Ang." <<endl;
    cout << string(95, '-') << endl;

    for (const auto& angajat : angajati) {
        cout << std::left
                  << setw(6) << angajat.getIdAngajat()
                  << setw(15) << angajat.getNume()
                  << setw(15) << angajat.getPrenume()
                  << setw(15) << angajat.getCNP()
                  << setw(20) << angajat.getFunctie()
                  << fixed << setprecision(2) << setw(12) << angajat.getSalariu()
                  << setw(12) << angajat.getDataAngajare().toString() << endl;
    }
}

void Administrator::gestioneazaAdaugareCamera() {
    if (hotel) {
        hotel->adaugaCamera();
    } else {
        cerr << "Eroare critica: Referinta la hotel (hotel*) este nula in Administrator!" <<endl;
    }
}

void Administrator::gestioneazaAfisareCamere() const {
    if (hotel) {
        hotel->afiseazaToateCamerele();
    } else {
        cerr << "Eroare critica: Referinta la hotel (hotel*) este nula in Administrator!" << endl;
    }
}

double Administrator::getIncasariPerioada(const Data& start, const Data& end) const {
    if (!hotel) return 0.0;
    double totalIncasari = 0.0;

    for (const auto& rez : hotel->getRezervari()) {
        if (rez.getStare() == StareRezervare::CheckOut) {
            if (!(rez.getCheckOut() < start) && (rez.getCheckOut() < end || rez.getCheckOut().toString() == end.toString()) ) {
                 totalIncasari += rez.getPretTotal();
            }
        }
    }
    return totalIncasari;
}


Data avanseazaZi(Data d) {

    int zileInLunaVal = Data::getZileInLuna(d.luna, d.an);

    d.zi++;
    if (d.luna > 0 && d.luna <= 12 && d.zi > zileInLunaVal && zileInLunaVal != 0) {
        d.zi = 1;
        d.luna++;
        if (d.luna > 12) {
            d.luna = 1;
            d.an++;
        }
    } else if (d.luna <= 0 || d.luna > 12 || zileInLunaVal == 0) {
        return d;
    }
    return d;
}


double Administrator::getGradOcuparePerioada(const Data& start, const Data& end) const {
    if (!hotel || hotel->getCamere().empty()) return 0.0;
    if (!start.esteValida() || !end.esteValida() || end < start) return 0.0;

    long long totalNoptiDisponibile = 0;
    long long noptiOcupate = 0;
    int numarTotalCamere = hotel->getCamere().size();

    Data currentDate = start;

    while (!(end < currentDate)) {
        if (!currentDate.esteValida()) break;
        totalNoptiDisponibile += numarTotalCamere;

        for (const auto& rez : hotel->getRezervari()) {
            if (rez.getStare() != StareRezervare::Anulata && rez.getStare() != StareRezervare::InAsteptare) {
                 if ( (rez.getCheckIn() < currentDate || rez.getCheckIn().toString() == currentDate.toString()) &&
                      (currentDate < rez.getCheckOut()) ) {
                    noptiOcupate++;
                }
            }
        }
        if (currentDate.toString() == end.toString()) break;
        currentDate = avanseazaZi(currentDate);
        if (!currentDate.esteValida() || (currentDate.toString() == start.toString() && !(start.toString() == end.toString()) ) ) {
            cerr << "Eroare in avansarea datei in getGradOcuparePerioada. Intrerupere bucla." << endl;
            break;
        }
    }

    if (totalNoptiDisponibile == 0) return 0.0;
    return (static_cast<double>(noptiOcupate) / totalNoptiDisponibile) * 100.0;
}

void Administrator::schimbaCredentiale() {
    string currentPassInput;
    string newUsernameInput;
    string newPassInput;
    string newPassConfirmInput;

    cout << "\n--- Schimbare Credentiale Administrator ---" << endl;

    cout << "Introduceti parola curenta: ";
    cin >> currentPassInput;

    if (encryptDecrypt(currentPassInput, XOR_KEY) != this->encryptedPassword) {
        cout << "Parola curenta este incorecta. Schimbarea credentialelor a fost anulata." << endl;
        return;
    }

    cout << "Credentiale curente verificate." << endl;
    cout << "Introduceti noul username: ";
    cin >> newUsernameInput;

    if (newUsernameInput.empty()) {
        cout << "Noul username nu poate fi gol. Schimbarea credentialelor a fost anulata." << endl;
        return;
    }

    cout << "Introduceti noua parola: ";
    cin >> newPassInput;

    if (newPassInput.empty()) {
        cout << "Noua parola nu poate fi goala. Schimbarea credentialelor a fost anulata." << endl;
        return;
    }

    if (newPassInput.length() < 6) {
        cout << "Noua parola trebuie sa aiba cel putin 6 caractere. Schimbarea credentialelor a fost anulata." << endl;
        return;
    }

    cout << "Confirmati noua parola: ";
    cin >> newPassConfirmInput;

    if (newPassInput != newPassConfirmInput) {
        std::cout << "Parolele noi nu se potrivesc. Schimbarea credentialelor a fost anulata." << endl;
        return;
    }

    salveazaCredentialeNoi(newUsernameInput, newPassInput);
    cout << "Username-ul si parola au fost schimbate cu succes." << endl;
}

void Administrator::vizualizeazaIncasari() const {
    if (!hotel) {
        cerr << "Eroare critica: Referinta la hotel (hotel*) este nula!" << endl;
        return;
    }
    cout << "\n--- Vizualizare Incasari ---" << endl;
    cout << "1. Incasari lunare " << endl;
    cout << "2. Incasari anuale" << endl;
    cout << "3. Incasari perioada custom" << endl;
    cout << "0. Inapoi la meniul administratorului" << endl;
    cout << "Alege o optiune: ";
    int optiuneIncasari;
    cin >> optiuneIncasari;
    while(cin.fail() || optiuneIncasari < 0 || optiuneIncasari > 3) {
         cout << "Optiune invalida. Introduceti un numar intre 0 si 3: ";
         cin.clear();
         cin >> optiuneIncasari;
    }

    if (optiuneIncasari == 0) {
        return;
    }

    Data dataStart, dataSfarsit;
    Data dataCurenta = Data::getCurrentDate();

    switch (optiuneIncasari) {
        case 1:
        {
            int luna;
            system("cls");
            cout << "1. Ianuarie\n2. Februarie\n3. Martie\n4. Aprilie\n5. Mai\n6. Iunie\n7. Iulie\n8. August\n9. Septembire\n10. Octombire\n11. Noiembrie\n12. Decembrie\n";
            cout << "Introduceti luna (1-12):";
            cin >> luna;
            while(cin.fail() || luna < 1 || luna > 12) {
            cout << "Luna invalida. Introduceti un numar intre 1 si 12: ";
            cin >> luna;
            }
            dataStart = Data(1, luna, dataCurenta.an);
            int zileLuna = Data::getZileInLuna(luna, dataCurenta.an);
            if (zileLuna == 0) { cout << "Eroare: Luna/an invalid pentru calcul zile." << endl; return; }
            dataSfarsit = Data(zileLuna, luna, dataCurenta.an);

            if (!dataStart.esteValida() || !dataSfarsit.esteValida()) { cout << "Date invalide generate pentru luna/an." << endl; return;}
            cout << "\nIncasari pentru " << luna << "/" << dataCurenta.an << ": "
                      << fixed << setprecision(2) << getIncasariPerioada(dataStart, dataSfarsit) << " RON" << endl;
            break;
        }
        case 2:
        {
            dataStart = Data(1, 1, dataCurenta.an);
            dataSfarsit = Data(31, 12, dataCurenta.an);
            if (!dataStart.esteValida() || !dataSfarsit.esteValida()) { cout << "Date invalide generate pentru an." << endl; return;}
            system("cls");
            cout << "\nIncasari pentru anul " << dataCurenta.an << ": "
                      << fixed <<setprecision(2) << getIncasariPerioada(dataStart, dataSfarsit) << " RON" << endl;
            break;
        }
        case 3:
        {
            cout << "Introduceti data de inceput (DD.MM.YYYY): ";
            cin >> dataStart;

            while(!dataStart.esteValida()){
                cout << "Data invalida. Reintroduceti data de inceput (DD.MM.YYYY): ";
                cin.clear();
                cin >> dataStart;
            }
            cout << "Introduceti data de sfarsit (DD.MM.YYYY): ";
            cin >> dataSfarsit;

            while(!dataSfarsit.esteValida() || dataSfarsit < dataStart){
                cout << "Data invalida sau data de sfarsit < data de inceput. Reintroduceti data de sfarsit (DD.MM.YYYY): ";
                cin.clear();
                cin >> dataSfarsit;
            }
            system("cls");
            cout << "\nIncasari pentru perioada " << dataStart.toString() << " - " << dataSfarsit.toString() << ": "
                      << fixed << setprecision(2) << getIncasariPerioada(dataStart, dataSfarsit) << " RON" << endl;
            break;
        }
    }
}

void Administrator::statisticiGradOcupare() const {
    if (!hotel) {
        cerr << "Eroare critica: Referinta la hotel (hotel*) este nula!" << endl;
        return;
    }
    if (hotel->getCamere().empty()) {
        cout << "\nNu exista camere inregistrate pentru a calcula gradul de ocupare." << endl;
        return;
    }
    cout << "\n--- Statistici Grad Ocupare ---" << endl;
    cout << "1. Grad ocupare lunar " << endl;
    cout << "2. Grad ocupare anual " << endl;
    cout << "3. Grad ocupare perioada custom" << endl;
    cout << "0. Inapoi la meniul administratorului" << endl;
    cout << "Alege o optiune: ";
    int optiuneOcupare;
    cin >> optiuneOcupare;
    while(cin.fail() || optiuneOcupare < 0 || optiuneOcupare > 3) {
         cout << "Optiune invalida. Introduceti un numar intre 0 si 3: ";
         cin.clear();
         cin >> optiuneOcupare;
    }

    if (optiuneOcupare == 0) {
        return;
    }

    Data dataStart, dataSfarsit;
    Data dataCurenta = Data::getCurrentDate();

    switch (optiuneOcupare) {
        case 1:
        {
            int luna;
            system("cls");
            cout << "1. Ianuarie\n2. Februarie\n3. Martie\n4. Aprilie\n5. Mai\n6. Iunie\n7. Iulie\n8. August\n9. Septembire\n10. Octombire\n11. Noiembrie\n12. Decembrie\n";
            cout << "Introduceti luna (1-12):";
            cin >> luna;
            while(cin.fail() || luna < 1 || luna > 12) {
                cout << "Luna invalida. Introduceti un numar intre 1 si 12: ";
                cin.clear();
                cin >> luna;
            }
            dataStart = Data(1, luna, dataCurenta.an);
            int zileLuna = Data::getZileInLuna(luna, dataCurenta.an);
            if (zileLuna == 0) { cout << "Eroare: Luna/an invalid pentru calcul zile." << endl; return; }
            dataSfarsit = Data(zileLuna, luna, dataCurenta.an);

            if (!dataStart.esteValida() || !dataSfarsit.esteValida()) { cout << "Date invalide generate pentru luna/an." <<endl; return;}
            system("cls");
            cout << "\nGrad ocupare pentru " << luna << "/" << dataCurenta.an << ": "
                      << fixed << setprecision(2) << getGradOcuparePerioada(dataStart, dataSfarsit) << "%" << endl;
            break;
        }
        case 2: // Anual
        {
            dataStart = Data(1, 1, dataCurenta.an);
            dataSfarsit = Data(31, 12, dataCurenta.an);
            if (!dataStart.esteValida() || !dataSfarsit.esteValida()) { cout << "Date invalide generate pentru an." << endl; return;}
            system("cls");
            cout << "\nGrad ocupare pentru anul " << dataCurenta.an << ": "
                      << fixed << setprecision(2) << getGradOcuparePerioada(dataStart, dataSfarsit) << "%" << endl;
            break;
        }
        case 3:
        {
            cout << "Introduceti data de inceput (DD.MM.YYYY): ";
            cin >> dataStart;
            while(!dataStart.esteValida()){
                cout << "Data invalida. Reintroduceti data de inceput (DD.MM.YYYY): ";
                cin.clear();
                cin >> dataStart;
            }
            cout << "Introduceti data de sfarsit (DD.MM.YYYY): ";
            cin >> dataSfarsit;
            while(!dataSfarsit.esteValida() || dataSfarsit < dataStart){
                cout << "Data invalida sau data de sfarsit < data de inceput. Reintroduceti data de sfarsit (DD.MM.YYYY): ";
                cin.clear();
                cin >> dataSfarsit;
            }
            system("cls");
            cout << "\nGrad ocupare pentru perioada " << dataStart.toString() << " - " << dataSfarsit.toString() << ": "
                      << fixed << setprecision(2) << getGradOcuparePerioada(dataStart, dataSfarsit) << "%" << endl;
            break;
        }
    }
}
