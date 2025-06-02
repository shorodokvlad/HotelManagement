#include "Angajat.h"
#include <windows.h>

using namespace std;

void setColorAngajat(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Angajat::Angajat() : Persoana(), idAngajat(0), functie(""), salariu(0.0), dataAngajare() {}

Angajat::Angajat(int _idAngajat, const string& _nume, const string& _prenume, const string& _cnp,
                 const string& _functie, double _salariu, const Data& _dataAngajare)
    : Persoana(_nume, _prenume, _cnp), idAngajat(_idAngajat), functie(_functie),
      salariu(_salariu), dataAngajare(_dataAngajare) {}

int Angajat::getIdAngajat() const
{
    return idAngajat;
}
string Angajat::getFunctie() const
{
    return functie;
}
double Angajat::getSalariu() const
{
    return salariu;
}
Data Angajat::getDataAngajare() const
{
    return dataAngajare;
}

void Angajat::setIdAngajat(int id)
{
    idAngajat = id;
}
void Angajat::setFunctie(const string& _functie)
{
    functie = _functie;
}
void Angajat::setSalariu(double _salariu)
{
    if (_salariu >= 0) salariu = _salariu;
}
void Angajat::setDataAngajare(const Data& _dataAngajare)
{
    if (_dataAngajare.esteValida()) dataAngajare = _dataAngajare;
}

string Angajat::toString() const
{
    return "ID Angajat: " + to_string(idAngajat) + "\n" +
           Persoana::toString() +
           "Functie: " + functie + "\n" +
           "Salariu: " + to_string(salariu) + " RON\n" +
           "Data angajare: " + dataAngajare.toString() + "\n";
}

bool Angajat::validareSalariu(const string& input, double& salariuOut)
{
    for (char c : input)
    {
        if (isalpha(c))
        {
            setColorAngajat(12);
            cout << "\nSalariul nu trebuie sa contina litere!\n";
            return false;
        }
    }

    try
    {
        salariuOut = stod(input);
    }
    catch (...)
    {
        setColorAngajat(12);
        cout << "\nSalariul introdus nu este valid!\n";
        return false;
    }

    if (salariuOut <= 0)
    {
        setColorAngajat(12);
        cout << "\nSalariul trebuie sa fie pozitiv!\n";
        return false;
    }

    return true;
}


ostream& operator<<(ostream& out, const Angajat& angajat)
{
    out << angajat.toString();
    return out;
}

istream& operator>>(istream& in, Angajat& angajat)
{
    in >> (Persoana&)angajat;

    setColorAngajat(8);
    cout << "Functie: ";
    setColorAngajat(14);
    in >> angajat.functie;

    string inputSalariu;
    do
    {
        setColorAngajat(8);
        cout << "Salariu (RON): ";
        setColorAngajat(14);
        in >> inputSalariu;
    }
    while (!Angajat::validareSalariu(inputSalariu, angajat.salariu));


    do
    {
        setColorAngajat(8);
        cout << "Data angajare (DD.MM.YYYY): ";
        setColorAngajat(14);
        cin.clear();
        cin >> angajat.dataAngajare;

        if (!angajat.dataAngajare.esteValida())
        {
            setColorAngajat(12);
            cout << "\nData introdusa nu este valida. Reincercati.\n";
        }

    }
    while (!angajat.dataAngajare.esteValida());


    return in;
}
