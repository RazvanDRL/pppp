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
  Produs();
  Produs(const string &cod, const string &nume, int cant, double pr);
  string getCodDeBare() const;
  string getDenumire() const;
  int getCantitate() const;
  double getPret() const;
  DataCalendaristica getDataCreare() const;
  void setCodDeBare(const string &);
  void setDenumire(const string &);
  void setCantitate(int);
  void setPret(double);
  friend ostream &operator<<(ostream &, const Produs &);
};

#endif