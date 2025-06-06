#include "DataCalendaristica.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


DataCalendaristica::DataCalendaristica(int zi, int luna, int an) {
    if (!dataValida(zi, luna, an)) {
      throw invalid_argument("Data invalida");
    }
    this->zi = zi;
    this->luna = luna;
    this->an = an;
  }

int DataCalendaristica::getZi() const { return zi; }

int DataCalendaristica::getLuna() const { return luna; }

int DataCalendaristica::getAn() const { return an; }

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

bool DataCalendaristica::esteAnBisect(int an) const {
  return (an % 4 == 0 && an % 100 != 0) || (an % 400 == 0);
}

bool DataCalendaristica::dataValida(int zi, int luna, int an) const {
  if (an < 1 || luna < 1 || luna > 12)
    return false;
  if (zi < 1 || zi > zileInLuna(luna, an))
    return false;
  return true;
}

string DataCalendaristica::toString() const {
  return to_string(zi) + "/" + to_string(luna) + "/" + to_string(an);
}