#include "DataCalendaristica.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Constructor care initializeaza data cu zi, luna si an, verificand validitatea
DataCalendaristica::DataCalendaristica(int zi, int luna, int an) {
  if (!dataValida(zi, luna, an)) {
    throw invalid_argument("Data invalida");
  }
  this->zi = zi;
  this->luna = luna;
  this->an = an;
}

// Functie care returneaza ziua datei
int DataCalendaristica::getZi() const { return zi; }

// Functie care returneaza luna datei
int DataCalendaristica::getLuna() const { return luna; }

// Functie care returneaza anul datei
int DataCalendaristica::getAn() const { return an; }

// Functie care calculeaza numarul de zile dintr-o luna data
int DataCalendaristica::zileInLuna(int luna, int an) const {
  switch (luna) {
  case 2:
    return esteAnBisect(an) ? 29 : 28;
  case 4:
  case 6:
  case 9:
  case 11:
    return 30;
  default:
    return 31;
  }
}

// Functie care verifica daca un an este bisect
bool DataCalendaristica::esteAnBisect(int an) const {
  return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
}

// Functie care verifica daca o data cu zi, luna si an este valida
bool DataCalendaristica::dataValida(int zi, int luna, int an) const {
  if (an < 1 || luna < 1 || luna > 12)
    return false;
  if (zi < 1 || zi > zileInLuna(luna, an))
    return false;
  return true;
}

// Functie care converteste data la format string zi/luna/an
string DataCalendaristica::toString() const {
  return to_string(zi) + "/" + to_string(luna) + "/" + to_string(an);
}