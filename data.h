#ifndef PROIECT_DATA_H
#define PROIECT_DATA_H

#include <iostream>
#include <string>
using namespace std;

class Data
{
    int zi;
    int luna;
    int an;

public:
    Data(int zi, int luna, int an);
    Data(){}
    Data(const Data&);

    friend ostream& operator <<(ostream&, const Data&);
    friend istream& operator >>(istream&, Data&);
    Data& operator = (const Data&);

    int getZi() const;
    void setZi(int);

    int getLuna() const;
    void setLuna(int);

    int getAn() const;
    void setAn(int);
};

#endif //PROIECT_DATA_H
