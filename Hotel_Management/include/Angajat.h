#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include <string>

class Angajat : public Persoana {
private:
    int angajatID;
    std::string departament;
    std::string pozitie;
    double salariu;
    std::string dataAngajare;
    std::string programMunca;

public:
    // Constructori
    Angajat();
    Angajat(const std::string& nume, const std::string& prenume, const std::string& CNP,
            const std::string& gen, int id, const std::string& departament,
            const std::string& pozitie, double salariu, const std::string& dataAngajare,
            const std::string& programMunca);
    ~Angajat();

    // Getteri și setteri
    int getAngajatID() const;
    void setAngajatID(int id);

    std::string getDepartament() const;
    void setDepartament(const std::string& departament);

    std::string getPozitie() const;
    void setPozitie(const std::string& pozitie);

    double getSalariu() const;
    void setSalariu(double salariu);

    std::string getDataAngajare() const;
    void setDataAngajare(const std::string& data);

    std::string getProgramMunca() const;
    void setProgramMunca(const std::string& program);

    // Metoda toString
    std::string toString() const;

    // Operatori de I/O
    friend std::ostream& operator<<(std::ostream& out, const Angajat& angajat);
    friend std::istream& operator>>(std::istream& in, Angajat& angajat);
};

#endif // ANGAJAT_H
