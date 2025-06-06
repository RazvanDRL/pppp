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
  DataCalendaristica(int, int, int);
  bool esteAnBisect(int) const;
  bool dataValida(int, int, int) const;
  int zileInLuna(int, int) const;
  int getZi() const;
  int getLuna() const;
  int getAn() const;
  string toString() const;
};

#endif // __DATACALENDARISTICA_H__