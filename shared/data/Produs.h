#ifndef __PRODUS_H__
#define __PRODUS_H__

#include "DataCalendaristica.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Produs {
  string cod_de_bare;
  string denumire;
  int cantitate;
  double pret;
  DataCalendaristica data_creare;

public:
  // Constructor implicit care initializeaza un produs gol
  Produs();
  // Constructor cu parametri care creeaza un produs cu date specifice
  Produs(const string &cod, const string &nume, int cant, double pr);
  // Functie care returneaza codul de bare al produsului
  string getCodDeBare() const;
  // Functie care returneaza denumirea produsului
  string getDenumire() const;
  // Functie care returneaza cantitatea produsului
  int getCantitate() const;
  // Functie care returneaza pretul produsului
  double getPret() const;
  // Functie care returneaza data de creare a produsului
  DataCalendaristica getDataCreare() const;
  // Metoda care seteaza codul de bare al produsului
  void setCodDeBare(const string &);
  // Metoda care seteaza denumirea produsului
  void setDenumire(const string &);
  // Metoda care seteaza cantitatea produsului
  void setCantitate(int);
  // Metoda care seteaza pretul produsului
  void setPret(double);
  // Operator de afisare pentru produse
  friend ostream &operator<<(ostream &, const Produs &);
};

#endif