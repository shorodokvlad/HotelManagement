#include "Hotel.h"
#include "Camera.h"
#include <iostream>

using namespace std;

int main() {
    Hotel hotel;
    cout << "Test adaugaCamera:" << endl;
    hotel.adaugaCamera(101, "Single", 100.0, true, true, true, false);
    hotel.adaugaCamera(102, "Double", 150.0, true, true, true, true);
    cout << endl;

    cout << "Test obtineCameraDupaNumar:" << endl;
    Camera* camera1 = hotel.obtineCameraDupaNumar(101);
    if (camera1) {
        cout << "Camera gasita: " << camera1->toString() << endl;
    } else {
        cout << "Camera cu numarul 101 nu a fost gasita." << endl;
    }
    cout << endl;

    cout << "Test salveazaCamere si incarcaCamere:" << endl;
    hotel.salveazaCamere();
    hotel.incarcaCamere();
    Camera* camera2 = hotel.obtineCameraDupaNumar(102);
    if (camera2) {
        cout << "Camera incarcata: " << camera2->toString() << endl;
    } else {
        cout << "Camera cu numarul 102 nu a fost incarcata." << endl;
    }

    return 0;
}
