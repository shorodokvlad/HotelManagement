#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

class Data {
public:
    int zi, luna, an;

    Data(int z, int l, int a);
    bool esteValida() const;
    bool esteMaiMicaDecat(const Data& other) const;
    string toString() const;
};

#endif
