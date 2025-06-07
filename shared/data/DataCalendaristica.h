#ifndef __DATACALENDARISTICA_H__
#define __DATACALENDARISTICA_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class DataCalendaristica {
  int zi, luna, an;

public:
  // Constructor care creeaza o data calendaristica cu zi, luna si an
  DataCalendaristica(int, int, int);
  // Functie care verifica daca un an este bisect
  bool esteAnBisect(int) const;
  // Functie care verifica daca o data este valida
  bool dataValida(int, int, int) const;
  // Functie care returneaza numarul de zile dintr-o luna
  int zileInLuna(int, int) const;
  // Functie care returneaza ziua datei
  int getZi() const;
  // Functie care returneaza luna datei
  int getLuna() const;
  // Functie care returneaza anul datei
  int getAn() const;
  // Functie care converteste data la string
  string toString() const;
};

#endif // __DATACALENDARISTICA_H__