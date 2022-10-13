#include "data.h"

Data::Data(int zi, int luna, int an)
{
    this->zi = zi;
    this->luna = luna;
    this->an = an;
}

Data& Data::operator=(const Data &d){
    this->zi = d.zi;
    this->luna = d.luna;
    this->an = d.an;
    return *this;
}

Data::Data(const Data &d) {
    this->zi = d.zi;
    this->luna = d.luna;
    this->an = d.an;
}

int Data::getZi() const
{
    return this->zi;
}
void Data::setZi(int zi)
{
    this->zi = zi;
}

int Data::getLuna() const
{
    return this->luna;
}
void Data::setLuna(int luna)
{
    this->luna = luna;
}

int Data::getAn() const
{
    return this->an;
}
void Data::setAn(int zi)
{
    this->an = an;
}

ostream & operator << (ostream &out, const Data &d)
{
    out << d.zi << "." << d.luna << "."<< d.an;
    return out;
}

istream & operator >> (istream &in, Data &d)
{
    in >> d.zi >> d.luna >> d.an;
    return in;
}
