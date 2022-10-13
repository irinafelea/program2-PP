#include "produs.h"

Produs::Produs(string cod, string denumire, int cantitate, double pret)
{
    this->cod = cod;
    this->denumire = denumire;
    this->cantitate = cantitate;
    this->pret = pret;
}

Produs& Produs::operator=(const Produs &p){
    this->cod = p.cod;
    this->denumire = p.denumire;
    this->cantitate = p.cantitate;
    this->pret = p.pret;
    return *this;
}

string Produs::getCod() const
{
    return this->cod;
}

void Produs::setCod(string cod)
{
    this->cod = cod;
}

string Produs::getDenumire() const
{
    return this->denumire;
}
void Produs::setDenumire(string denumire)
{
    this->denumire = denumire;
}

int Produs::getCantitate() const
{
    return this->cantitate;
}
void Produs::setCantitate(int cantitate)
{
    this->cantitate = cantitate;
}

double Produs::getPret() const
{
    return this->pret;
}
void Produs::setPret(double pret)
{
    this->pret = pret;
}

ostream & operator << (ostream &out, const Produs &p)
{
    out << p.cod << " " << p.denumire << " "<< p.cantitate << " " << p.pret;
    return out;
}

istream & operator >> (istream &in, Produs &p) {
    in >> p.cod >> p.denumire >> p.cantitate >> p.pret;
    return in;
}
