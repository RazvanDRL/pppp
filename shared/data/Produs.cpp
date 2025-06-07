#include "Produs.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Constructor implicit care initializeaza un produs gol cu data implicita
Produs::Produs() : data_creare(1, 1, 2025) {
  cod_de_bare = "";
  denumire = "";
  cantitate = 0;
  pret = 0.0;
}

// Constructor cu parametri care creeaza un produs cu datele specificate si data
// curenta
Produs::Produs(const string &cod, const string &nume, int cant, double pr)
    : cod_de_bare(cod), denumire(nume), cantitate(cant), pret(pr),
      data_creare(1, 1, 2025) {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int zi = ltm->tm_mday;
  int luna = 1 + ltm->tm_mon;
  int an = 1900 + ltm->tm_year;
  try {
    data_creare = DataCalendaristica(zi, luna, an);
  } catch (const exception &e) {
    // If current date is invalid, keep default date
  }
}

// Functie care returneaza codul de bare al produsului
string Produs::getCodDeBare() const { return cod_de_bare; }

// Functie care returneaza denumirea produsului
string Produs::getDenumire() const { return denumire; }

// Functie care returneaza cantitatea produsului
int Produs::getCantitate() const { return cantitate; }

// Functie care returneaza pretul produsului
double Produs::getPret() const { return pret; }

// Functie care returneaza data de creare a produsului
DataCalendaristica Produs::getDataCreare() const { return data_creare; }

// Metoda care seteaza codul de bare al produsului
void Produs::setCodDeBare(const string &cod_de_bare) {
  this->cod_de_bare = cod_de_bare;
}
// Metoda care seteaza denumirea produsului
void Produs::setDenumire(const string &denumire) { this->denumire = denumire; }
// Metoda care seteaza cantitatea produsului
void Produs::setCantitate(int cantitate) { this->cantitate = cantitate; }
// Metoda care seteaza pretul produsului
void Produs::setPret(double pret) { this->pret = pret; }

// Operator de afisare care afiseaza toate datele produsului
ostream &operator<<(ostream &os, const Produs &p) {
  os << "Cod de bare: " << p.cod_de_bare << ", Denumire: " << p.denumire
     << ", Cantitate: " << p.cantitate << ", Pret: " << p.pret;
  return os;
}