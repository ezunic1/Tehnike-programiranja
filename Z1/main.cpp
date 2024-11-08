// TP 2023/2024: Zadaća 2, Zadatak 1
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace Robot {
enum class Pravci {
  Sjever = 0,
  Sjeveroistok = 1,
  Istok = 2,
  Jugoistok = 3,
  Jug = 4,
  Jugozapad = 5,
  Zapad = 6,
  Sjeverozapad = 7
};
enum class KodoviGresaka {
  PogresnaKomanda = 0,
  NedostajeParametar = 1,
  SuvisanParametar = 3,
  NeispravanParametar = 2
};
enum class Komande { Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj };
// varijable
bool vidljivost = true;
bool pomocni = true;
bool vidljiv_temp = true;
std::vector<std::vector<char>> Teren;
int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
std::vector<std::string> poruke = {
    {"Nerazumljiva komanda!"},
    {"Komanda trazi parametar koji nije naveden!"},
    {"Parametar komande nije ispravan!"},
    {"Zadan je suvisan parametar nakon komande!"}};

std::vector<std::string> pravciN = {
    {"sjever."}, {"sjeveroistok."}, {"istok."}, {"jugoistok."},
    {"jug."},    {"jugozapad."},    {"zapad."}, {"sjeverozapad."},
};
void KreirajTeren(int xmin, int xmax, int ymin, int ymax, int &x, int &y,
                  Pravci &orijentacija);                  //
bool Idi(int &x, int &y, Pravci orijentacija, int korak); //
void Rotiraj(Pravci &orijentacija, int ugao);             //
void Sakrij();                                            //
void Otkrij();                                            //
void IspisiPoziciju(int x, int y, Pravci orijentacija);   //
void PrikaziTeren();                                      //
void PrijaviGresku(KodoviGresaka kod_greske);             //
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                   Pravci &orijentacija);
bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske);
} // namespace Robot
bool Robot::UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske){
    return true;
}
void Robot::KreirajTeren(int xmin, int xmax, int ymin, int ymax, int &x, int &y,
                         Pravci &orijentacija) {
  Robot::xmin = xmin;
  Robot::xmax = xmax;
  Robot::ymin = ymin;
  Robot::ymax = ymax;
  if (xmin >= xmax || ymin >= ymax) {
    throw std::range_error("Nelegalan opseg");
  }
  int sirina = 0;
  int visina = 0;
  for (int i = xmin; i <= xmax; i++)
    sirina++;
  for (int i = ymin; i <= ymax; i++)
    visina++;
  Robot::Teren.resize(visina);
  for (int i = 0; i < Robot::Teren.size(); i++) {
    Robot::Teren.at(i).resize(sirina, true);
  }
  x = (xmin + xmax) / 2;
  y = (ymin + ymax) / 2;
  orijentacija = Robot::Pravci::Sjever;
  for (int i = 0; i < visina; i++) {
    for (int j = 0; j < sirina; j++) {
      Robot::Teren.at(i).at(j) = ' ';
    }
  }
  Robot::Teren.at(y - ymin).at(x - xmin) = '*';
}
void Robot::PrikaziTeren() {
  int sirina = 0;
  int visina = 0;
  for (int i = xmin; i <= xmax; i++)
    sirina++;
  for (int i = ymin; i <= ymax; i++)
    visina++;
  for (int i = 0; i <= sirina + 1; i++)
    std::cout << "#";
  std::cout << std::endl;
  for (int i = visina - 1; i >= 0; i--) {
    std::cout << "#";
    for (int j = 0; j < sirina; j++) {
      std::cout << Robot::Teren.at(i).at(j);
    }
    std::cout << "#";
    std::cout << std::endl;
  }
  for (int i = 0; i <= sirina + 1; i++)
    std::cout << "#";
  std::cout << std::endl;
}
void Robot::IspisiPoziciju(int x, int y, Pravci orijentacija) {
  std::cout << "Robot je ";
  if (Robot::vidljivost)
    std::cout << "vidljiv, ";
  else
    std::cout << "nevidljiv, ";
  std::cout << "nalazi se na poziciji (" << x << "," << y << ") i gleda na ";
  std::cout << pravciN.at(static_cast<size_t>(orijentacija)) << std::endl;
}
void Robot::Otkrij() { Robot::vidljivost = true; }
void Robot::Sakrij() { Robot::vidljivost = false; }
void Robot::PrijaviGresku(KodoviGresaka kod_greske) {
  std::cout << poruke.at(static_cast<size_t>(kod_greske)) << std::endl;
}

void Robot::Rotiraj(Pravci &orijentacija, int ugao) {
  /*int pomak = (ugao * 45) % 360;
  orijentacija = Pravci((int(orijentacija) + pomak) % 360);
  if ((int(orijentacija) < 0))
    orijentacija = Pravci(int(orijentacija) + 360);*/
  int pom = static_cast<size_t>(orijentacija);
  orijentacija = Pravci( (8 + pom - ugao)%8);
  // std::cout << int(orijentacija);
}

bool Robot::Idi(int &x, int &y, Pravci orijentacija, int korak) {
  if (korak < 0) {
    Robot::Rotiraj(orijentacija, 4);
    korak *= -1;
  } else if (korak == 0)
    return true;

  int pozicijax = x - Robot::xmin, pozicijay = y - Robot::ymin;

  bool pom = true;

  if (Robot::vidljivost || Robot::vidljiv_temp) {
    Robot::Teren.at(y - ymin).at(x - xmin) = '*';
  } else {
    Robot::Teren.at(y - ymin).at(x - xmin) = ' ';
  }

  Robot::pomocni = true;
  int xpom = x, ypom = y;
  if (int(orijentacija) % 2 == 0) {
    for (int i = 0; i < korak; i++) {
      if (int(orijentacija) == 0) {
        y++;
      } else if (int(orijentacija) == 2) {
        x++;
      } else if (int(orijentacija) == 4) {
        y--;
      } else if (int(orijentacija) == 6) {
        x--;
      }
      if (x > Robot::xmax || x < Robot::xmin || y > Robot::ymax ||
          y < Robot::ymin) {

        x = xpom;
        y = ypom;
        Robot::Teren.at(pozicijay).at(pozicijax) = 'O';
        std::cout << "Robot je pokusao napustiti teren!" << std::endl;
        Robot::pomocni = false;
        pom = false;
        break;
      }
      xpom = x;
      ypom = y;
      pozicijax = x - Robot::xmin;
      pozicijay = y - Robot::ymin;
      if (i == korak - 1)
        Robot::Teren.at(pozicijay).at(pozicijax) = 'O';
      else if (Robot::vidljivost) {
        Robot::Teren.at(pozicijay).at(pozicijax) = '*';
      }
    }
  } else if (int(orijentacija) % 2 == 1) {
    for (int i = 0; i < korak; i++) {
      if (int(orijentacija) == 1) {
        x++;
        y++;
      } else if (int(orijentacija) == 7) {
        x--;
        y++;
      } else if (int(orijentacija) == 5) {
        x--;
        y--;
      } else if (int(orijentacija) == 3) {
        x++;
        y--;
      }
      if (x > Robot::xmax || x < Robot::xmin || y > Robot::ymax ||
          y < Robot::ymin) {
        x = xpom;
        y = ypom;
        Robot::Teren.at(pozicijay).at(pozicijax) = 'O';
        pom = false;
        std::cout << "Robot je pokusao napustiti teren!" << std::endl;
        Robot::pomocni = false;
        break;
      }
      xpom = x;
      ypom = y;
      pozicijax = x - Robot::xmin;
      pozicijay = y - Robot::ymin;
      if (i == korak - 1)
        Robot::Teren.at(pozicijay).at(pozicijax) = 'O';
      else if (Robot::vidljivost) {

        Robot::Teren.at(pozicijay).at(pozicijax) = '*';
      }
    }
  }
  if (Robot::vidljivost)
    Robot::vidljiv_temp = true;
  else {
    Robot::vidljiv_temp = false;
  }

  return pom;
}

void Robot::IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                          Pravci &orijentacija) {
  switch (komanda) {
  case Robot::Komande::Idi: {
    Robot::Idi(x, y, orijentacija, parametar);
    break;
  }
  case Robot::Komande::Rotiraj: {
    Robot::Rotiraj(orijentacija, parametar);
    break;
  }
  case Robot::Komande::Sakrij: {
    Robot::Sakrij();
    break;
  }
  case Robot::Komande::Otkrij: {
    Robot::Otkrij();
    break;
  }
  case Robot::Komande::PrikaziTeren: {
    Robot::PrikaziTeren();
    break;
  }
  case Robot::Komande::Kraj: {
    break;
  }
  }
}

int main() { 

    // AT 15: Test funkcije IspisiPoziciju u kombinaciji sa funkcijom PostaviVidljivost
    {
        int x = 5, y = -5, ugao = 0;
        Robot::Pravci pravci = Robot::Pravci::Sjever;
        Robot::KreirajTeren(-1000,1000,-1000,1000,x,y,pravci);

        for (int i{}; i<8; i++)
        {
            IspisiPoziciju(x,y,pravci);

            Idi(x,y,pravci,12*i+3);
            ugao++;
            Rotiraj(pravci,ugao);

            if (i % 2 == 0)
                Robot::vidljivost = true;
            else
                Robot::vidljivost = false;
        }
    }
    
    return 0; }
