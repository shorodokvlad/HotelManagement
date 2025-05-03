#include <iostream>
#include "Hotel.h"

using namespace std;

int main() {
    Hotel hotel;
    hotel.incarcaDate();
    int optiune, optiuneReceptioner, optiuneAdministrator;

    do {
        cout << "=============================" << endl;
        cout << "      HOTEL Management       " << endl;
        cout << "=============================" << endl;
        cout << "1. Intra ca Receptioner" << endl;
        cout << "2. Intra ca Administrator" << endl;
        cout << "0. Iesire" << endl;
        cout << "Alege o optiune: ";
        cin >> optiune;

        switch (optiune) {
            case 1: {
                system("cls");
                do {
                    cout << "\nMeniu Receptioner:" << endl;
                    cout << "1. Adauga client" << endl;
                    cout << "2. Afiseaza clienti" << endl;
                    cout << "3. Afiseaza camere libere" << endl;
                    cout << "4. Afiseaza camere ocupate" << endl;
                    cout << "5. Gestionare rezervari" << endl;
                    cout << "0. Iesire" << endl;
                    cout << "Alege o optiune: ";
                    cin >> optiuneReceptioner;

                    switch (optiuneReceptioner) {
                        case 1: {
                            system("cls");
                            hotel.adaugaClient();
                            break;
                        }
                        case 2: {
                            system("cls");
                            hotel.afiseazaClienti();
                            break;
                        }
                        case 3: {
                            system("cls");
                            hotel.afiseazaCamereLibere();
                            break;
                        }
                        case 4: {
                            system("cls");
                            hotel.afiseazaCamereOcupate();
                            break;
                        }
                        case 5: {
                            system("cls");
                            int optiuneRezervare;
                            do {
                                cout << "\nGestionare rezervari:" << endl;
                                cout << "1. Adaugare rezervare" << endl;
                                cout << "2. Vizualizare rezervari" << endl;
                                cout << "3. Confirmare rezervare" << endl;
                                cout << "4. Check-in" << endl;
                                cout << "5. Check-out" << endl;
                                cout << "6. Anulare rezervare" << endl;
                                cout << "7. Modificare rezervare" << endl;
                                cout << "0. Inapoi" << endl;
                                cout << "Alege o optiune: ";
                                cin >> optiuneRezervare;

                                switch (optiuneRezervare) {
                                    case 1: {
                                        system("cls");
                                        hotel.adaugaRezervare();
                                        break;
                                    }
                                    case 2: {
                                        system("cls");
                                        hotel.afiseazaRezervari();
                                        break;
                                    }
                                    case 3: {
                                        system("cls");
                                        hotel.modificaStareRezervare(StareRezervare::Confirmata);
                                        break;
                                    }
                                    case 4: {
                                        system("cls");
                                        hotel.modificaStareRezervare(StareRezervare::CheckIn);
                                        break;
                                    }
                                    case 5: {
                                        system("cls");
                                        hotel.modificaStareRezervare(StareRezervare::CheckOut);
                                        break;
                                    }
                                    case 6: {
                                        system("cls");
                                        hotel.modificaStareRezervare(StareRezervare::Anulata);
                                        break;
                                    }
                                    case 7: {
                                        system("cls");
                                        hotel.modificaRezervare();
                                        break;
                                    }
                                    case 0: {
                                        system("cls");
                                        break;
                                    }
                                    default: {
                                        cout << "\nOptiune invalida! Incearca din nou." << endl;
                                    }
                                }
                            } while (optiuneRezervare != 0);
                            break;
                        }
                        case 0: {
                            system("cls");
                            break;
                        }
                        default: {
                            cout << "\nOptiune invalida! Incearca din nou." << endl;
                        }
                    }
                } while (optiuneReceptioner != 0);
                break;
            }
            case 2: {
                system("cls");
                do {
                    cout << "\nMeniu Administrator:" << endl;
                    cout << "1. Adauga camera" << endl;
                    cout << "2. Afiseaza toate camerele" << endl;
                    cout << "0. Iesire" << endl;
                    cout << "Alege o optiune: ";
                    cin >> optiuneAdministrator;

                    switch (optiuneAdministrator) {
                        case 1:
                            system("cls");
                            hotel.adaugaCamera();
                            break;
                        case 2:
                            system("cls");
                            hotel.afiseazaToateCamerele();
                            break;
                        case 0:
                            system("cls");
                            break;
                        default: {
                            cout << "\nOptiune invalida! Incearca din nou." << endl;
                        }
                    }
                } while (optiuneAdministrator != 0);
                break;
            }
            case 0: {
                system("cls");
                hotel.salveazaDate();
                cout << "\nIesire din program. La revedere!" << endl;
                break;
            }
            default: {
                cout << "\nOptiune invalida! Incearca din nou." << endl;
            }
        }
        cout << "\n";
    } while (optiune != 0);

    return 0;
}
