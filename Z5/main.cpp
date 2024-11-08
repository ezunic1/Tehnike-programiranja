// TP 2023/2024: Zadaća 4, Zadatak 5
#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class Student {
  int indeks;
  std::string godina, ime, adresa, broj;

public:
  Student(int indeksX, std::string godinaX, std::string imeX,
          std::string adresaX, std::string brojX);
  int DajIndeks() const { return indeks; }
  std::string DajGodinuStudija() const { return godina; }
  std::string DajImePrezime() const { return ime; }
  std::string DajTelefon() const { return broj; }
  std::string DajAdresu()const{return adresa;}
  void Ispisi() const;
};

void Student::Ispisi() const {
  std::cout << "Broj indeksa: " << indeks << std::endl;
  std::cout << "Godina studija: " << godina << std::endl;
  std::cout << "Ime i prezime: " << ime << std::endl;
  std::cout << "Adresa: " << adresa << std::endl;
  std::cout << "Telefon: " << broj << std::endl;
}

Student::Student(int indeksX, std::string godinaX, std::string imeX,
                 std::string adresaX, std::string brojX) {
  if (indeksX < 10000 || indeksX > 99999)
    throw std::domain_error("Neispravni parametri");
  indeks = indeksX;
  std::string pomIme{};
  bool pom = true;
  for (int i = 0; i < imeX.size(); i++) {
    if (imeX.at(i) != ' ') {
      pomIme += imeX.at(i);
      pom = false;
    } else if (!pom) {
      pomIme += ' ';
      pom = true;
    }
  }
  if (!pomIme.empty() && pomIme.at(pomIme.size() - 1) == ' ') {
    pomIme.erase(pomIme.size() - 1);
  }
  ime = pomIme;
  pomIme = {};
  pom = true;
  for (int i = 0; i < adresaX.size(); i++) {
    if (adresaX.at(i) != ' ') {
      pomIme += adresaX.at(i);
      pom = false;
    } else if (!pom) {
      pomIme += ' ';
      pom = true;
    }
  }
  if (!pomIme.empty() && pomIme.at(pomIme.size() - 1) == ' ') {
    pomIme.erase(pomIme.size() - 1);
  }
  adresa = pomIme;

  if (godinaX != "1" && godinaX != "2" && godinaX != "3" && godinaX != "1/B" &&
      godinaX != "2/B" && godinaX != "3/B" && godinaX != "1/M" &&
      godinaX != "2/M" && godinaX != "3/M" && godinaX != "1/D" &&
      godinaX != "2/D" && godinaX != "3/D")
    throw std::domain_error("Neispravni parametri");

  if (godinaX == "1")
    godina = std::string("1/B");
  else if (godinaX == "2")
    godina = std::string("2/B");
  else if (godinaX == "3")
    godina = std::string("3/B");
  else
    godina = godinaX;
  pom = true;
  int i = 0;
  char znak1, znak2;

  while (i < brojX.size() && brojX.at(i) >= '0' && brojX.at(i) <= '9') {
    i++;
  }
  if (i == 0 || i == brojX.size())
    throw std::domain_error("Neispravni parametri");
  znak1 = brojX.at(i);
  if (znak1 != '/')
    throw std::domain_error("Neispravni parametri");
  i++;
  if (i == brojX.size())
    throw std::domain_error("Neispravni parametri");
  int pompom = i;
  while (i < brojX.size() && brojX.at(i) >= '0' && brojX.at(i) <= '9') {
    i++;
  }
  if (i == pompom || i == brojX.size())
    throw std::domain_error("Neispravni parametri");
  znak2 = brojX.at(i);
  if (znak2 != '-')
    throw std::domain_error("Neispravni parametri");
  i++;
  if (i == brojX.size())
    throw std::domain_error("Neispravni parametri");
  while (i < brojX.size() && brojX.at(i) >= '0' && brojX.at(i) <= '9') {
    i++;
  }
  if (i != brojX.size())
    throw std::domain_error("Neispravni parametri");
  broj = brojX;
}

class Laptop {
  int ev_broj;
  std::string naziv, karakteristike;
  Student *kod_koga_je;

public:
  Laptop(int br, std::string naziv, std::string k)
      : ev_broj(br), naziv(naziv), karakteristike(k), kod_koga_je(nullptr) {
    if (ev_broj < 0)
      throw std::domain_error("Neispravni parametri");
  }
  int DajEvidencijskiBroj() const { return ev_broj; }
  std::string DajNaziv() const { return naziv; }
  std::string DajKarakteristike() const { return karakteristike; }

  void Zaduzi(Student &s) {
    if (kod_koga_je != nullptr)
      throw std::domain_error("Laptop vec zaduzen");
    kod_koga_je = &s;
  }
  void Razduzi() { kod_koga_je = nullptr; }

  bool DaLiJeZaduzen() const {
    if (kod_koga_je == nullptr)
      return false;
    return true;
  }

  Student &DajKodKogaJe() {
    if (kod_koga_je == nullptr)
      throw std::domain_error("Laptop nije zaduzen");
    return *kod_koga_je;
  }
  Student *DajPokKodKogaJe() { return kod_koga_je; }

  void Ispisi() const;
};

void Laptop::Ispisi() const {
  std::cout << "Evidencijski broj: " << ev_broj << std::endl;
  std::cout << "Naziv: " << naziv << std::endl;
  std::cout << "Karakteristike: " << karakteristike << std::endl;
}

class Administracija {
  std::map<int, Student *> studenti;
  std::map<int, Laptop *> laptopi;

public:
  Administracija(){}
  ~Administracija(){
      for(auto &x : studenti){
          delete x.second;
      }
      for(auto &x : laptopi){
          delete x.second;
      }
  }
  Administracija(const Administracija &a);
  Administracija(Administracija &&a);
  Administracija &operator=(const Administracija &a);
  Administracija &operator=(Administracija &&a);
  void RegistrirajNovogStudenta(int indeksX, std::string godinaX, std::string imeX, std::string adresaX,std::string brojX);
  void RegistrirajNoviLaptop(int br, std::string naziv, std::string k);
  Student &NadjiStudenta(int index);
  Laptop &NadjiLaptop(int br);
  Student NadjiStudenta(int index)const;
  Laptop NadjiLaptop(int br) const;
  void IzlistajStudente()const;
  void IzlistajLaptope()const;
  void ZaduziLaptop(int index, int br);
  int NadjiSlobodniLaptop()const;
  void RazduziLaptop(int br);
  void PrikaziZaduzenja()const;
};
Administracija::Administracija(const Administracija &a){
    for(auto &x : a.studenti){
        studenti[x.first] = new Student(*x.second);
    }
    for(auto &x : a.laptopi){
        laptopi[x.first] = new Laptop(*x.second);
    }
}

Administracija &Administracija::operator=(const Administracija &a){
    if(this == &a)return *this;
    for(auto &x : studenti){
          delete x.second;
      }
    for(auto &x : laptopi){
        delete x.second;
    }
    for(auto &x : a.studenti){
        studenti[x.first] = new Student(*x.second);
    }
    for(auto &x : a.laptopi){
        laptopi[x.first] = new Laptop(*x.second);
    }
    return *this;
}

Administracija::Administracija(Administracija &&a){
    std::swap(studenti,a.studenti);
    std::swap(laptopi, a.laptopi);
}

Administracija &Administracija::operator=(Administracija &&a){
    if(&a == this)return *this;
   /*for(auto &x : studenti){
          delete x.second;
      }
    for(auto &x : laptopi){
        delete x.second;
    }*/
    std::swap(studenti,a.studenti);
    std::swap(laptopi, a.laptopi);
    return *this;
}


Student& Administracija::NadjiStudenta(int index){
    auto it = studenti.find(index);
    if(it == studenti.end())throw std::domain_error("Student nije nadjen");
    return *(it->second);
}

Laptop& Administracija::NadjiLaptop(int br){
    auto it = laptopi.find(br);
    if(it == laptopi.end())throw std::domain_error("Laptop nije nadjen");
    return *(it->second);
}

Student Administracija::NadjiStudenta(int index)const{
    auto it = studenti.find(index);
    if(it == studenti.end())throw std::domain_error("Student nije nadjen");
    return *(it->second);
}

Laptop Administracija::NadjiLaptop(int br)const{
    auto it = laptopi.find(br);
    if(it == laptopi.end())throw std::domain_error("Laptop nije nadjen");
    return *(it->second);
}

void Administracija::IzlistajStudente()const{
    for(auto &x: studenti){
        (x.second)->Ispisi();
        std::cout << std::endl;
    }
}

void Administracija::IzlistajLaptope()const{
    for(auto &x : laptopi){
        (x.second)->Ispisi();
        if(x.second->DaLiJeZaduzen()){
            Student pom = x.second->DajKodKogaJe();
            std::cout << "Zaduzio(la): " << pom.DajImePrezime() << " (" << pom.DajIndeks() << ")" <<std::endl;
        }
        std::cout << std::endl;
    }
}
void Administracija::ZaduziLaptop(int index, int br){
    if(studenti.find(index) == studenti.end())throw std::domain_error("Student nije nadjen");
    if(laptopi.find(br) == laptopi.end())throw std::domain_error("Laptop nije nadjen");
    if(laptopi[br]->DaLiJeZaduzen())throw std::domain_error("Laptop vec zaduzen");
    for(auto &x : laptopi){
        if(x.second->DaLiJeZaduzen() && x.second->DajKodKogaJe().DajIndeks() == index)
            throw std::domain_error("Student je vec zaduzio laptop");
    }
    laptopi[br]->Zaduzi(*studenti[index]);
}

int Administracija::NadjiSlobodniLaptop()const{
    for(auto &x : laptopi){
        if(!x.second->DaLiJeZaduzen()){
            return x.second->DajEvidencijskiBroj();
        }
    }
    throw std::domain_error("Nema slobodnih laptopa");
    return 0;
}

void Administracija::RazduziLaptop(int br){
    if(laptopi.find(br) == laptopi.end())throw std::domain_error("Laptop nije nadjen");
    if(!laptopi.find(br)->second->DaLiJeZaduzen())throw std::domain_error("Laptop nije zaduzen");
    laptopi[br]->Razduzi();
}

void Administracija::PrikaziZaduzenja()const{
    bool pom1 = false;
    for(auto &x : laptopi){
        if(x.second->DaLiJeZaduzen()){
            pom1 = true;
            Student pom = x.second->DajKodKogaJe();
            std::cout << "Student " << pom.DajImePrezime() << " (" << pom.DajIndeks() << ") " 
            << "zaduzio/la laptop broj " << x.first << std::endl;
        }
    }
    if(!pom1) std::cout << "Nema zaduzenja" << std::endl;
}

void Administracija::RegistrirajNovogStudenta(int indeksX, std::string godinaX,
                                              std::string imeX,
                                              std::string adresaX,
                                              std::string brojX) {
  auto it = studenti.find(indeksX);
  if (it != std::end(studenti))
    throw std::domain_error("Student s tim indeksom vec postoji");
  studenti[indeksX] = new Student(indeksX, godinaX, imeX, adresaX, brojX);
}

void Administracija::RegistrirajNoviLaptop(int br, std::string naziv,std::string k) {
  auto it = laptopi.find(br);
  if (it != std::end(laptopi))
    throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
  laptopi[br] = new Laptop(br, naziv, k);
}

int main() {
    char x;
    Administracija A;

    while(true){
        std::cout << "Odaberite jednu od sljedecih opcija: " << std::endl;
        std::cout  << "1 - RegistrirajNovogStudenta" << std::endl;
        std::cout  << "2 - RegistrirajNoviLaptop" << std::endl;
        std::cout  << "3 - IzlistajStudente" << std::endl;
        std::cout  << "4 - IzlistajLaptope" << std::endl;
        std::cout  << "5 - NadjiSlobodniLaptop" << std::endl;
        std::cout  << "6 - ZaduziLaptop" << std::endl;
        std::cout  << "7 - RazduziLaptop" << std::endl;
        std::cout  << "8 - PrikaziZaduzenja" << std::endl;
        std::cout  << "K - Kraj programa" << std::endl;
        std::cin >> x;
        std::cin.ignore(10000, '\n');
        if(x == 'K')break;

        if(x == '1'){
            int index;
            std::string godina, ime, adresa, broj;
            std::cout << "Unesite broj indeksa: " << std::endl;
            std::cin >> index;
            std::cin.ignore(10000, '\n');
            std::cout << "Unesite godinu studija (formata A/X, gdje je A godina studija, a X prima vrijednosti B,M,D, zavisno od studija): " << std::endl;
            std::getline(std::cin, godina);
            std::cout << "Unesite ime i prezime studenta: " << std::endl;
            std::getline(std::cin, ime);
            std::cout << "Unesite adresu studenta: " << std::endl;
            std::getline(std::cin, adresa);
            std::cout << "Unesite broj telefona (formata x/x-x): " << std::endl;
            std::getline(std::cin, broj);
            try{
                A.RegistrirajNovogStudenta(index,godina,ime,adresa,broj);
            }catch(std::domain_error &w){
                std::cout << "Izuzetak: " <<w.what() << "!" << std::endl;
            }
        }else if(x == '2'){
            int br;
            std::string naziv, k;
            std::cout << "Unesite evidencijski broj laptopa "<< std::endl;
            std::cin >> br;
            std::cin.ignore(10000, '\n');
            std::cout << "Unesite naziv laptopa "<< std::endl;
            std::getline(std::cin, naziv);
            std::cout << "Unesite karakteristike laptopa: "<< std::endl;
            std::getline(std::cin, k);
            try{
                A.RegistrirajNoviLaptop(br,naziv,k);
                std::cout << "Laptop uspjesno registrovan!" << std::endl;
            }catch(std::domain_error &w){
                std::cout << "Izuzetak: "<<w.what() << "!" << std::endl;
            }
        }else if(x == '3'){
            A.IzlistajStudente();
        }else if(x == '4'){
            A.IzlistajLaptope();
        }else if(x == '5'){
            std::cout << "Slobodan laptop: " << A.NadjiSlobodniLaptop();
        }else if(x == '6'){
            int index, br;
            std::cout << "Unesite broj indeksa: ";
            std::cin >> index;
            std::cin.ignore(10000, '\n');
            std::cout << "Unesite evidencijski broj: ";
            std::cin >> br;
            std::cin.ignore(10000, '\n');
            try{
                A.ZaduziLaptop(index, br);
            }catch(std::domain_error &w){
                std::cout << "Izuzetak: "<<w.what() << "!" << std::endl;
            }
        }else if(x == '7'){
            int br;
            std::cout << "Unesite evidencijski broj: ";
            std::cin >> br;
            std::cin.ignore(10000, '\n');
            try{
                A.RazduziLaptop(br);
            }catch(std::domain_error &w){
                std::cout << "Izuzetak: "<<w.what() << "!" << std::endl;
            }
        }else if(x == '8'){
            A.PrikaziZaduzenja();
        }
    }




  return 0;
}
