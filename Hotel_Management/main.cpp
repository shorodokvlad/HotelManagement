#include <iostream>
#include "Client.h"

using namespace std;

int main() {
    // Creăm un client folosind constructorul parametrizat
    Client client1("Ion", "Popescu", "1234567890123", "M", 1, "2025-04-01", "2025-04-05", 4, "Card bancar", 400, true, "Fara fum");

    // Afișează informațiile clientului folosind operatorul <<
    cout << client1 << endl;

    // Citirea unui obiect Client folosind operatorul >>
    Client client2;
    cin >> client2;

    // Afișează informațiile clientului citit
    cout << "\n" << client2 << endl;

    return 0;
}


