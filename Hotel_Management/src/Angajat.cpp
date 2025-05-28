#include "Angajat.h"

using namespace std;

Angajat::Angajat() : Persoana(), idAngajat(0), functie(""), salariu(0.0), dataAngajare() {}

Angajat::Angajat(int _idAngajat, const string& _nume, const string& _prenume, const string& _cnp,
                 const string& _functie, double _salariu, const Data& _dataAngajare)
    : Persoana(_nume, _prenume, _cnp), idAngajat(_idAngajat), functie(_functie),
      salariu(_salariu), dataAngajare(_dataAngajare) {}

int Angajat::getIdAngajat() const { return idAngajat; }
string Angajat::getFunctie() const { return functie; }
double Angajat::getSalariu() const { return salariu; }
Data Angajat::getDataAngajare() const { return dataAngajare; }

void Angajat::setIdAngajat(int id) { idAngajat = id; }
void Angajat::setFunctie(const string& _functie) { functie = _functie; }
void Angajat::setSalariu(double _salariu) { if (_salariu >= 0) salariu = _salariu; }
void Angajat::setDataAngajare(const Data& _dataAngajare) { if (_dataAngajare.esteValida()) dataAngajare = _dataAngajare; }

string Angajat::toString() const {
    return "ID Angajat: " + to_string(idAngajat) + "\n" +
           Persoana::toString() +
           "Functie: " + functie + "\n" +
           "Salariu: " + to_string(salariu) + " RON\n" +
           "Data angajare: " + dataAngajare.toString() + "\n";
}

ostream& operator<<(ostream& out, const Angajat& angajat) {
    out << angajat.toString();
    return out;
}

istream& operator>>(istream& in, Angajat& angajat) {
    in >> (Persoana&)angajat;
    cout << "Functie: ";
    in >> angajat.functie;
    cout << "Salariu (RON): ";
    in >> angajat.salariu;
    if (angajat.salariu < 0) angajat.salariu = 0;
    cout << "Data angajare (DD.MM.YYYY): ";
    in >> angajat.dataAngajare;
    if (!angajat.dataAngajare.esteValida()) angajat.dataAngajare = Data();
    return in;
}
