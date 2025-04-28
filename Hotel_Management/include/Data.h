#ifndef DATA_H
#define DATA_H

#include <string>

class Data {
public:
    int zi, luna, an;

    Data(int z, int l, int a);
    bool esteValida() const;
    bool esteMaiMicaDecat(const Data& other) const;
    std::string toString() const;
};

#endif
