#include "shared/data/DataCalendaristica.h"
#include "shared/data/Produs.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct ProdusInCos {
  string cod_de_bare;
  int cantitate;
};

vector<Produs> citireStoc(const string &numeFile) {
  vector<Produs> stoc;
  ifstream fin(numeFile);
  if (!fin) {
    cout << "Eroare: nu s-a putut deschide fisierul " << numeFile << endl;
    return stoc;
  }
  int nrProduse;
  fin >> nrProduse;
  for (int i = 0; i < nrProduse; i++) {
    Produs p;
    string cod_de_bare, denumire;
    int cantitate;
    double pret;
    fin >> cod_de_bare >> denumire >> cantitate >> pret;
    p.setCodDeBare(cod_de_bare);
    p.setDenumire(denumire);
    p.setCantitate(cantitate);
    p.setPret(pret);
    stoc.push_back(p);
  }
  fin.close();
  return stoc;
}

vector<ProdusInCos> citireCos(const string &numeFile) {
  vector<ProdusInCos> cos;
  ifstream fin(numeFile);
  if (!fin) {
    // Fisierul nu exista inca, returnam cos gol
    return cos;
  }
  string cod_de_bare;
  int cantitate;
  while (fin >> cod_de_bare >> cantitate) {
    ProdusInCos p;
    p.cod_de_bare = cod_de_bare;
    p.cantitate = cantitate;
    cos.push_back(p);
  }
  fin.close();
  return cos;
}

void scrieCos(const vector<ProdusInCos> &cos, const string &numeFile) {
  ofstream fout(numeFile);
  if (!fout) {
    cout << "Eroare: nu s-a putut deschide fisierul pentru scriere." << endl;
    return;
  }
  for (const auto &produs : cos) {
    fout << produs.cod_de_bare << " " << produs.cantitate << endl;
  }
  fout.close();
}

template <typename T, typename Predicate>
T gasesteElement(const vector<T> &container, Predicate pred) {
  for (const auto &element : container) {
    if (pred(element)) {
      return element;
    }
  }
  T elementGol;
  return elementGol;
}

Produs gasesteProdusInStoc(const string &cod_de_bare,
                           const vector<Produs> &stoc) {
  return gasesteElement<Produs>(stoc, [&cod_de_bare](const Produs &p) {
    return p.getCodDeBare() == cod_de_bare;
  });
}

void vizualizareCos() {
  vector<ProdusInCos> cos = citireCos("shared/files/cos_cumparaturi.txt");
  vector<Produs> stoc = citireStoc("shared/files/stoc.txt");

  if (cos.empty()) {
    cout << "Cosul de cumparaturi este gol." << endl;
    return;
  }

  cout << "Produse in cosul de cumparaturi:" << endl;
  cout << "=================================" << endl;

  double totalPret = 0.0;

  for (const auto &produsInCos : cos) {
    Produs produsStoc = gasesteProdusInStoc(produsInCos.cod_de_bare, stoc);

    if (produsStoc.getCodDeBare().empty()) {
      cout << "- Cod necunoscut: " << produsInCos.cod_de_bare
           << " (cantitate: " << produsInCos.cantitate << ")" << endl;
    } else {
      double pretTotal = produsStoc.getPret() * produsInCos.cantitate;
      totalPret += pretTotal;

      cout << "- " << produsStoc.getDenumire()
           << " (cod: " << produsStoc.getCodDeBare()
           << ", cantitate: " << produsInCos.cantitate
           << ", pret unitar: " << produsStoc.getPret()
           << ", pret total: " << fixed << setprecision(2) << pretTotal << ")"
           << endl;
    }
  }

  cout << "=================================" << endl;
  cout << "Total de plata: " << fixed << setprecision(2) << totalPret << " RON"
       << endl;
}

void adaugareProdusInCos(const string &cod_de_bare, int cantitate) {
  vector<Produs> stoc = citireStoc("shared/files/stoc.txt");

  // Verificam daca produsul exista in stoc
  Produs produsStoc = gasesteProdusInStoc(cod_de_bare, stoc);
  if (produsStoc.getCodDeBare().empty()) {
    cout << "Eroare: Produsul cu codul " << cod_de_bare << " nu exista in stoc."
         << endl;
    return;
  }

  // Verificam daca avem suficienta cantitate in stoc
  if (cantitate > produsStoc.getCantitate()) {
    cout << "Eroare: Nu avem suficienta cantitate in stoc. Disponibil: "
         << produsStoc.getCantitate() << endl;
    return;
  }

  vector<ProdusInCos> cos = citireCos("shared/files/cos_cumparaturi.txt");

  // Verificam daca produsul exista deja in cos
  bool gasit = false;
  for (auto &produsInCos : cos) {
    if (produsInCos.cod_de_bare == cod_de_bare) {
      // Verificam daca cantitatea totala nu depaseste stocul
      if (produsInCos.cantitate + cantitate > produsStoc.getCantitate()) {
        cout << "Eroare: Cantitatea totala ("
             << produsInCos.cantitate + cantitate
             << ") ar depasi stocul disponibil (" << produsStoc.getCantitate()
             << ")." << endl;
        return;
      }
      produsInCos.cantitate += cantitate;
      gasit = true;
      break;
    }
  }

  if (!gasit) {
    ProdusInCos nouProdus;
    nouProdus.cod_de_bare = cod_de_bare;
    nouProdus.cantitate = cantitate;
    cos.push_back(nouProdus);
  }

  scrieCos(cos, "shared/files/cos_cumparaturi.txt");
  cout << "Produsul " << produsStoc.getDenumire()
       << " a fost adaugat in cos cu cantitatea " << cantitate << "." << endl;
}

void modificareProdusInCos(const string &cod_de_bare, int cantitateNoua) {
  vector<ProdusInCos> cos = citireCos("shared/files/cos_cumparaturi.txt");
  vector<Produs> stoc = citireStoc("shared/files/stoc.txt");

  // Verificam daca produsul exista in stoc
  Produs produsStoc = gasesteProdusInStoc(cod_de_bare, stoc);
  if (produsStoc.getCodDeBare().empty()) {
    cout << "Eroare: Produsul cu codul " << cod_de_bare << " nu exista in stoc."
         << endl;
    return;
  }

  // Verificam cantitatea disponibila
  if (cantitateNoua > produsStoc.getCantitate()) {
    cout << "Eroare: Nu avem suficienta cantitate in stoc. Disponibil: "
         << produsStoc.getCantitate() << endl;
    return;
  }

  bool gasit = false;
  for (auto &produsInCos : cos) {
    if (produsInCos.cod_de_bare == cod_de_bare) {
      produsInCos.cantitate = cantitateNoua;
      gasit = true;
      break;
    }
  }

  if (!gasit) {
    cout << "Eroare: Produsul cu codul " << cod_de_bare << " nu exista in cos."
         << endl;
    return;
  }

  scrieCos(cos, "shared/files/cos_cumparaturi.txt");
  cout << "Cantitatea pentru produsul " << produsStoc.getDenumire()
       << " a fost modificata la " << cantitateNoua << "." << endl;
}

void stergereProdusInCos(const string &cod_de_bare) {
  vector<ProdusInCos> cos = citireCos("shared/files/cos_cumparaturi.txt");
  vector<Produs> stoc = citireStoc("shared/files/stoc.txt");

  vector<ProdusInCos> cosNou;
  bool gasit = false;
  string numeProdus = "";

  for (const auto &produsInCos : cos) {
    if (produsInCos.cod_de_bare != cod_de_bare) {
      cosNou.push_back(produsInCos);
    } else {
      gasit = true;
      Produs produsStoc = gasesteProdusInStoc(cod_de_bare, stoc);
      if (!produsStoc.getCodDeBare().empty()) {
        numeProdus = produsStoc.getDenumire();
      }
    }
  }

  if (!gasit) {
    cout << "Eroare: Produsul cu codul " << cod_de_bare << " nu exista in cos."
         << endl;
    return;
  }

  scrieCos(cosNou, "shared/files/cos_cumparaturi.txt");

  if (!numeProdus.empty()) {
    cout << "Produsul " << numeProdus << " a fost sters din cos." << endl;
  } else {
    cout << "Produsul cu codul " << cod_de_bare << " a fost sters din cos."
         << endl;
  }
}

DataCalendaristica getDataCurenta() {
  time_t now = time(0);
  tm *ltm = localtime(&now);

  int zi = ltm->tm_mday;
  int luna = 1 + ltm->tm_mon;
  int an = 1900 + ltm->tm_year;

  return DataCalendaristica(zi, luna, an);
}

void cumparare() {
  vector<ProdusInCos> cos = citireCos("shared/files/cos_cumparaturi.txt");

  if (cos.empty()) {
    cout << "Eroare: Cosul de cumparaturi este gol. Nu se poate plasa comanda."
         << endl;
    return;
  }

  vector<Produs> stoc = citireStoc("shared/files/stoc.txt");

  // Verificam din nou disponibilitatea tuturor produselor
  for (const auto &produsInCos : cos) {
    Produs produsStoc = gasesteProdusInStoc(produsInCos.cod_de_bare, stoc);
    if (produsStoc.getCodDeBare().empty()) {
      cout << "Eroare: Produsul cu codul " << produsInCos.cod_de_bare
           << " nu mai exista in stoc." << endl;
      return;
    }
    if (produsInCos.cantitate > produsStoc.getCantitate()) {
      cout << "Eroare: Nu avem suficienta cantitate pentru produsul "
           << produsStoc.getDenumire()
           << ". Disponibil: " << produsStoc.getCantitate()
           << ", necesar: " << produsInCos.cantitate << endl;
      return;
    }
  }

  // Actualizez stocul
  for (const auto &produsInCos : cos) {
    for (auto &produsStoc : stoc) {
      if (produsStoc.getCodDeBare() == produsInCos.cod_de_bare) {
        produsStoc.setCantitate(produsStoc.getCantitate() -
                                produsInCos.cantitate);
        break;
      }
    }
  }

  // Scriu stocul actualizat
  ofstream foutStoc("shared/files/stoc.txt");
  if (!foutStoc) {
    cout << "Eroare: nu s-a putut actualiza stocul." << endl;
    return;
  }
  foutStoc << stoc.size() << endl;
  for (const auto &produs : stoc) {
    foutStoc << produs.getCodDeBare() << " " << produs.getDenumire() << " "
             << produs.getCantitate() << " " << produs.getPret() << endl;
  }
  foutStoc.close();

  // Adaug comanda in fisierul comenzi.txt
  ofstream foutComenzi("shared/files/comenzi.txt", ios::app);
  if (!foutComenzi) {
    cout << "Eroare: nu s-a putut deschide fisierul comenzi.txt." << endl;
    return;
  }

  DataCalendaristica dataCurenta = getDataCurenta();
  foutComenzi << dataCurenta.getZi() << " " << dataCurenta.getLuna() << " "
              << dataCurenta.getAn() << endl;

  for (size_t i = 0; i < cos.size(); i++) {
    foutComenzi << cos[i].cod_de_bare;
    if (i < cos.size() - 1) {
      foutComenzi << " ";
    }
  }
  foutComenzi << endl;
  foutComenzi.close();

  // Golesc cosul
  ofstream foutCos("shared/files/cos_cumparaturi.txt");
  foutCos.close();

  cout << "Comanda a fost plasata cu succes!" << endl;
  cout << "Data comenzii: " << dataCurenta.toString() << endl;
  cout << "Stocul a fost actualizat si cosul a fost golit." << endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Nu s-a specificat nicio comanda." << endl;
    cout << "Comenzi disponibile:" << endl;
    cout << "  vizualizare_cos" << endl;
    cout << "  adaugare_produs <cod_de_bare> <cantitate>" << endl;
    cout << "  modificare_produs <cod_de_bare> <cantitate_noua>" << endl;
    cout << "  stergere_produs <cod_de_bare>" << endl;
    cout << "  cumparare" << endl;
    return 1;
  }

  string comanda = argv[1];

  if (comanda == "vizualizare_cos") {
    if (argc != 2) {
      cout << "Eroare: Comanda 'vizualizare_cos' nu necesita parametri "
              "suplimentari."
           << endl;
      return 1;
    }
    vizualizareCos();
  } else if (comanda == "adaugare_produs") {
    if (argc != 4) {
      cout << "Eroare: Trebuie sa specifici codul de bare si cantitatea."
           << endl;
      cout << "Utilizare: ./app_2.exe adaugare_produs <cod_de_bare> <cantitate>"
           << endl;
      return 1;
    }
    string cod_de_bare = argv[2];
    int cantitate;
    try {
      cantitate = stoi(argv[3]);
      if (cantitate <= 0) {
        cout << "Eroare: Cantitatea trebuie sa fie un numar pozitiv." << endl;
        return 1;
      }
    } catch (const exception &e) {
      cout << "Eroare: Cantitatea trebuie sa fie un numar valid." << endl;
      return 1;
    }
    adaugareProdusInCos(cod_de_bare, cantitate);
  } else if (comanda == "modificare_produs") {
    if (argc != 4) {
      cout << "Eroare: Trebuie sa specifici codul de bare si cantitatea noua."
           << endl;
      cout << "Utilizare: ./app_2.exe modificare_produs <cod_de_bare> "
              "<cantitate_noua>"
           << endl;
      return 1;
    }
    string cod_de_bare = argv[2];
    int cantitateNoua;
    try {
      cantitateNoua = stoi(argv[3]);
      if (cantitateNoua <= 0) {
        cout << "Eroare: Cantitatea trebuie sa fie un numar pozitiv." << endl;
        return 1;
      }
    } catch (const exception &e) {
      cout << "Eroare: Cantitatea trebuie sa fie un numar valid." << endl;
      return 1;
    }
    modificareProdusInCos(cod_de_bare, cantitateNoua);
  } else if (comanda == "stergere_produs") {
    if (argc != 3) {
      cout << "Eroare: Trebuie sa specifici codul de bare al produsului de "
              "sters."
           << endl;
      cout << "Utilizare: ./app_2.exe stergere_produs <cod_de_bare>" << endl;
      return 1;
    }
    string cod_de_bare = argv[2];
    stergereProdusInCos(cod_de_bare);
  } else if (comanda == "cumparare") {
    if (argc != 2) {
      cout << "Eroare: Comanda 'cumparare' nu necesita parametri suplimentari."
           << endl;
      return 1;
    }
    cumparare();
  } else {
    cout << "Comanda necunoscuta: " << comanda << endl;
    cout << "Comenzi disponibile:" << endl;
    cout << "  vizualizare_cos" << endl;
    cout << "  adaugare_produs <cod_de_bare> <cantitate>" << endl;
    cout << "  modificare_produs <cod_de_bare> <cantitate_noua>" << endl;
    cout << "  stergere_produs <cod_de_bare>" << endl;
    cout << "  cumparare" << endl;
    return 1;
  }

  return 0;
}