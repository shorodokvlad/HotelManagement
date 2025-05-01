#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

class Data {
public:
    int zi, luna, an;

    Data(int _zi, int _luna, int _an);
    bool esteValida() const;
    bool operator<(const Data& other) const;
    int getZileInLuna() const;
    string toString() const;
};

#endif
