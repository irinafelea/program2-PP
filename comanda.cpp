#include "comanda.h"

Comanda::Comanda(Data *d, vector<Produs>produse) {
    this->d = d;
    this->produse = produse;
}
ostream& operator << (ostream &out,  Comanda &c){
    cout << "Data: " << *c.d <<endl;
    cout<<"Lista produse: "<<endl;
    for(auto it= c.produse.begin(); it != c.produse.end(); it++)
        cout << *it <<endl;
    return out;
}
Comanda::Comanda(const Comanda&c){
    this->d = c.d;
    this->produse = c.produse;
}

Comanda &Comanda::operator =(const Comanda&c){
    this->d = c.d;
    this->produse = c.produse;
    return *this;
}
