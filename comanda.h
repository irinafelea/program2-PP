#ifndef PROIECT_COMANDA_H
#define PROIECT_COMANDA_H

#include "produs.h"
#include "data.h"
#include <vector>
class Comanda{
    Data *d;
    vector<Produs>produse;

public:
    Comanda(Data *d,vector<Produs>);
    Comanda(const Comanda&);

    friend ostream& operator <<(ostream &out,  Comanda &c);

    Comanda & operator= (const Comanda&);
};

#endif //PROIECT_COMANDA_H
