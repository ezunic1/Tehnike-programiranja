// TP 2023/2024: Zadaća 4, Zadatak 1

#include <cmath>
#include <iostream>
#include <new>
#include <algorithm>

typedef std::pair<double, double> Tacka;
enum Pozicija { GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno };
enum Smjer { Nalijevo, Nadesno };

class Pravougaonik {
  Tacka GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno;
public:
  Pravougaonik();
  Pravougaonik(const Tacka &t1, const Tacka &t2) { Postavi(t1, t2); }
  void Postavi(const Tacka &t1, const Tacka &t2);
  void Postavi(Pozicija p, const Tacka &t);
  void Centriraj(const Tacka &t);
  Tacka DajTjeme(Pozicija p) const;
  Tacka DajCentar() const;
  double DajHorizontalnu() const {
    return fabs(GoreDesno.first - GoreLijevo.first);
  }
  double DajVertikalnu() const {
    return fabs(GoreDesno.second - DoljeDesno.second);
  }
  double DajObim() const { return (DajHorizontalnu() + DajVertikalnu()) * 2; }
  double DajPovrsinu() const { return DajHorizontalnu() * DajVertikalnu(); }
  static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
  void Transliraj(double delta_x, double delta_y);
  void Rotiraj(const Tacka &t, Smjer s);
  void Ispisi() const {
    std::cout << "{{" << GoreLijevo.first << "," << GoreLijevo.second << "},{"
              << DoljeDesno.first << "," << DoljeDesno.second << "}}";
  }
  friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
  friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
  friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};

void Pravougaonik::Postavi(const Tacka &t1, const Tacka &t2) {
  GoreLijevo.first = std::min(t1.first, t2.first);
  GoreLijevo.second = std::max(t1.second, t2.second);
  DoljeDesno.first = std::max(t1.first, t2.first);
  DoljeDesno.second = std::min(t1.second, t2.second);
  GoreDesno = {DoljeDesno.first, GoreLijevo.second};
  DoljeLijevo = {GoreLijevo.first, DoljeDesno.second};
}

void Pravougaonik::Postavi(Pozicija p, const Tacka &t) {
  if (p == Pozicija::GoreLijevo) {
    this->Postavi(t, DoljeDesno);
  } else if (p == Pozicija::GoreDesno) {
    this->Postavi(t, DoljeLijevo);
  } else if (p == Pozicija::DoljeLijevo) {
    this->Postavi(t, GoreDesno);
  } else if (p == Pozicija::DoljeDesno) {
    this->Postavi(t, GoreLijevo);
  }
}

void Pravougaonik::Centriraj(const Tacka &t) {
    Transliraj(t.first - DajCentar().first, t.second - DajCentar().second);
}

Tacka Pravougaonik::DajTjeme(Pozicija p) const {
  if (p == Pozicija::GoreLijevo) {
    return GoreLijevo;
  } else if (p == Pozicija::GoreDesno) {
    return GoreDesno;
  } else if (p == Pozicija::DoljeLijevo) {
    return DoljeLijevo;
  } else if (p == Pozicija::DoljeDesno) {
    return DoljeDesno;
  }
  return GoreLijevo;
}

Tacka Pravougaonik::DajCentar() const {
  return {(GoreLijevo.first + GoreDesno.first) / 2,
          (GoreLijevo.second + DoljeLijevo.second) / 2};
}

void Pravougaonik::Transliraj(double delta_x, double delta_y) {
  GoreLijevo.first += delta_x;
  GoreLijevo.second += delta_y;
  DoljeLijevo.first += delta_x;
  DoljeLijevo.second += delta_y;
  GoreDesno.first += delta_x;
  GoreDesno.second += delta_y;
  DoljeDesno.first += delta_x;
  DoljeDesno.second += delta_y;
}

void Pravougaonik::Rotiraj(const Tacka &t, Smjer s) {
    if(s == Nalijevo) {
        double nova_goreLijevo_x = -(GoreLijevo.second - t.second) + t.first;
        double nova_goreLijevo_y = (GoreLijevo.first - t.first) + t.second;
        double nova_doljeDesno_x = -(DoljeDesno.second - t.second) + t.first;
        double nova_doljeDesno_y = (DoljeDesno.first - t.first) + t.second;
        this->Postavi({nova_goreLijevo_x, nova_goreLijevo_y}, {nova_doljeDesno_x, nova_doljeDesno_y});
    } else if(s == Nadesno) {
        double nova_goreLijevo_x = (GoreLijevo.second - t.second) + t.first;
        double nova_goreLijevo_y = -(GoreLijevo.first - t.first) + t.second;
        double nova_doljeDesno_x = (DoljeDesno.second - t.second) + t.first;
        double nova_doljeDesno_y = -(DoljeDesno.first - t.first) + t.second;
        this->Postavi({nova_goreLijevo_x, nova_goreLijevo_y}, {nova_doljeDesno_x, nova_doljeDesno_y});
    }
}


bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2) {
  return (p1.DajHorizontalnu() == p2.DajHorizontalnu() &&
          p1.DajVertikalnu() == p2.DajVertikalnu()) ||
         (p1.DajHorizontalnu() == p2.DajVertikalnu() &&
          p1.DajVertikalnu() == p2.DajHorizontalnu());
}
bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2){

    auto h1 = p1.DajHorizontalnu();
    auto h2 = p2.DajHorizontalnu();
    auto v1 = p1.DajVertikalnu();
    auto v2 = p2.DajVertikalnu();
    if((h1 == 0 && v1 == 0) || h2 == 0 && v2 == 0)return true;
    if((h1 == 0 && v1!=0) || (h1 != 0 && v1 == 0)){
        if((h2 == 0 && v2!=0) || (h2 != 0 && v2 == 0))return true;
        else return false;
    }

    double pom1 = h1 / v1;
    double pom2 = h2 / v2;
    //std::cout << std::endl << "---   " <<fabs(pom2-pom1) << "   ----" << std::endl;
    return fabs(pom1 - pom2) < 1e-9 || fabs(pom1 - 1 / pom2) < 1e-9;
}

bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2) {
    return (p1.GoreLijevo == p2.GoreLijevo && p1.DoljeDesno == p2.DoljeDesno);
  }

Pravougaonik Pravougaonik::Presjek(const Pravougaonik &p1, const Pravougaonik &p2){
    Tacka gl, dd;
    gl.first = std::max(p1.GoreLijevo.first, p2.GoreLijevo.first);
    gl.second = std::min(p1.GoreLijevo.second, p2.GoreLijevo.second);
    dd.first = std::min(p1.DoljeDesno.first, p2.DoljeDesno.first);
    dd.second = std::max(p1.DoljeDesno.second, p2.DoljeDesno.second);
        if (gl.first > dd.first || gl.second < dd.second) {
        throw std::domain_error("Pravougaonici se ne presjecaju");
    }
    return {gl,dd};
}

int main() {
        /*Pravougaonik p1 {{1, 5}, {5, 1}}, p2 ({1, 1}, {7, 5}), p3 ({7, 1}, {1, 5});
        std::cout << "DaLiSePoklapaju (p2, p3): " << DaLiSePoklapaju(p2, p3) << std::endl;
        std::cout << "DaLiSePoklapaju (p1, p1): " << DaLiSePoklapaju(p1, p1) << std::endl;
        std::cout << "P2:  ";
        p2.Ispisi();
        std::cout << "P3:   ";
        p3.Ispisi();*/

        std::cout << "Unesite n: ";
        int n = 0;
        std::cin >> n;
     
        Pravougaonik **niz = new Pravougaonik*[n]{};
        double x, y;
        for(int i = 0; i < n; i++){
            std::cout <<"Unesite 1. tjeme pravougaonika " << i+1 << ": ";
            std:: cin >> x  >> y;
            Tacka t1 = {x,y};
            std::cout <<"Unesite 2. tjeme pravougaonika " << i+1 << ": ";  
            std::cin >> x >> y;
            Tacka t2 = {x,y};
            niz[i] = new Pravougaonik(t1,t2);
        }
        double dx, dy;
        std::cout <<"Unesite podatke za transliranje (dx dy): ";
        std::cin >> dx >> dy;

        std::transform(niz, niz + n,niz, [dx,dy](Pravougaonik *p){
            p->Transliraj(dx, dy);
            return p;
        });
        std::transform(niz, niz + n, niz, [](Pravougaonik * p){
            p->Rotiraj(p->DajCentar(), Smjer::Nadesno);
            return p;
        });
        std::cout << "Pravougaonici, nakon transformacija:" <<std::endl;
        std::for_each(niz,niz+n, [](Pravougaonik * p){
            p->Ispisi();
            std::cout << std::endl;
        });

        auto p = std::max_element(niz, niz + n, [](Pravougaonik *p1, Pravougaonik * p2){
            return p1->DajPovrsinu() < p2->DajPovrsinu();
        });
        std::cout << "Pravougaonik s najvecom povrsinom: ";
        (*p)->Ispisi();

        for(int i = 0; i < n; i++){
            delete niz[i];
        }
        delete []niz;


return 0; }
