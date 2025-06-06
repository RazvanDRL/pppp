#include "Produs.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

string Produs::getCodDeBare() const { return cod_de_bare; }

string Produs::getDenumire() const { return denumire; }

int Produs::getCantitate() const { return cantitate; }

double Produs::getPret() const { return pret; }

void Produs::setCodDeBare(const string &cod_de_bare) {
  this->cod_de_bare = cod_de_bare;
}
void Produs::setDenumire(const string &denumire) { this->denumire = denumire; }
void Produs::setCantitate(int cantitate) { this->cantitate = cantitate; }
void Produs::setPret(double pret) { this->pret = pret; }

ostream &operator<<(ostream &os, const Produs &p) {
  os << "Cod de bare: " << p.cod_de_bare << ", Denumire: " << p.denumire
     << ", Cantitate: " << p.cantitate << ", Pret: " << p.pret;
  return os;
}