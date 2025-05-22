#ifndef DATA_H
#define DATA_H

#include <string>

using namespace std;

class Data {
public:
    int zi, luna, an;

    Data() : zi(1), luna(1), an(2000) {}
    Data(int _zi, int _luna, int _an);
    bool esteValida() const;
    bool operator<(const Data& other) const;
    string toString() const;
    friend istream& operator>>(istream& in, Data& data);
    friend ostream& operator<<(ostream& out, const Data& data);
};

#endif
