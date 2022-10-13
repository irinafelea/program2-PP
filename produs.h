#ifndef PROIECT_PRODUS_H
#define PROIECT_PRODUS_H

#include <iostream>
#include <string>
using namespace std;

class Produs
{
    string cod;
    string denumire;
    int cantitate;
    double pret;

public:
    Produs(string, string, int, double);
    Produs();

    friend ostream& operator <<(ostream&, const Produs&);
    friend istream& operator >>(istream&, Produs&);

    Produs& operator = (const Produs&);

    string getCod() const;
    void setCod(string);

    string getDenumire() const;
    void setDenumire(string);

    int getCantitate() const;
    void setCantitate(int);

    double getPret() const;
    void setPret(double);
};

#endif // PROIECT_PRODUS_H
