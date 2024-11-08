//TP 2023/2024: LV 11, Zadatak 7
#include <initializer_list>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <memory>
class Datum {
    int dan, mjesec, godina;
public:
    Datum(){
        dan = 1;
        mjesec = 1;
        godina = 1;
    }
    Datum(int d, int m, int g) { Postavi(d, m, g); }
    void Postavi(int d, int m, int g);
    void Ispisi() const { std::cout << dan << "/" << mjesec << "/" << godina; }
    std::tuple<int, int, int> Ocitaj() const{
       return std::make_tuple(dan,mjesec,godina);
    }
    int dajDan()const {return dan;}
    int dajMjesec()const{return mjesec;}
    int dajGodinu()const {return godina;}

    bool operator ==(const Datum &d){
        if(dan == d.dajDan() && mjesec == d.dajMjesec() && godina == d.dajGodinu())return true;
        return false;
    }
};
class Vrijeme {
    int sati;
    int minute;
public:
    Vrijeme(int sati = 0, int minute = 0) {
        Postavi(sati, minute);
    }
    void Postavi(int sati , int minute);

    std::pair<int, int> Ocitaj() const {
        return {sati, minute};
    }
    void Ispisi() const {
        if(sati<10) std::cout << "0";
        std::cout << sati << ":";
        if(minute < 10)std::cout << "0";
        std::cout<< minute; 
    }
    int dajSate(){return sati;}
    int dajMinute(){return minute;}  
};

class Pregled{
    std::string ime{};
    Datum datum;
    Vrijeme vrijeme;

    public:
    Pregled(const std::string &ime, const Datum &dat, const Vrijeme &v) : ime(ime), datum(dat), vrijeme(v){}
    Pregled(const std::string &ime, int d, int m, int g, int h, int min) : ime(ime){
        datum = {d,m,g};
        vrijeme = {h,min};
    }
    Pregled &PromijeniPacijenta(std::string ime){
        this->ime = ime;
        return *this;
    }
    Pregled &PromijeniDatum(Datum dat){
        this->datum = dat;
        return *this;
    }
    Pregled &PromijeniVrijeme(Vrijeme v){
        this->vrijeme = v;
        return *this;
    }
    void PomjeriDanUnaprijed();
    void PomjeriDanUnazad();
    std::string DajImePacijenta() const{return ime;}
    Datum DajDatumPregleda() const{return datum;}
    Vrijeme DajVrijemePregleda() const{return vrijeme;}
    static bool DolaziPrije(const Pregled &p1, const Pregled &p2);
    void Ispisi();
};

class Pregledi{
    Pregled ** pregledi;
    const int kapacitet{};
    int broj{};
    public:
    Pregledi() : pregledi(new Pregled*[0]{}){}
    explicit Pregledi(int x) : pregledi(new Pregled*[x]{}), kapacitet(x){}
    Pregledi(std::initializer_list<Pregled> p);
    Pregledi(const Pregledi &p);
    Pregledi &operator =(const Pregledi &p); /// kopirajuci operator dodjele uraditi
    Pregledi(Pregledi &&p);
    Pregledi &operator =(Pregledi &&p){
        std::swap(broj, p.broj);
        std::swap(pregledi, p.pregledi);
        return *this;
    }
    void Dealociraj() {
    for(int i = 0; i < broj; i++) delete pregledi[i];
        delete[] pregledi;
        broj = 0;
    }

    void RegistrirajPregled(const std::string &ime, const Datum &dat, const Vrijeme &v){
        if(broj >= kapacitet)throw std::range_error("Dostignut maksimalni broj pregleda");
        pregledi[broj++] = new Pregled(ime,dat,v);
    }
    void RegistrirajPregled(const std::string &ime, int d, int m, int g, int h, int min){
        if(broj >= kapacitet)throw std::range_error("Dostignut maksimalni broj pregleda");
        pregledi[broj++] = new Pregled(ime,{d,m,g},{h,min});        
    }
    void RegistrirajPregled(Pregled *p){
        if(broj >= kapacitet)throw std::range_error("Dostignut maksimalni broj pregleda");
        pregledi[broj++] = p;   
    }
    ~Pregledi(){
        Dealociraj();
    }
    int DajBrojPregleda() const{return broj;}
    int DajBrojPregledaNaDatum(Datum dat) const{
        return std::count_if(pregledi, pregledi+broj, [&dat](Pregled *p){
           if(dat == p->DajDatumPregleda())return true;
           return false;
        });
    }

    Pregled &DajNajranijiPregled(){
        if(broj == 0)throw std::domain_error("Nema registriranih pregleda");
        auto pom = std::min_element(pregledi, pregledi + broj, [](Pregled *p1, Pregled * p2){
            return Pregled::DolaziPrije(*p1,*p2);
        });
        return **pom;
    }
    Pregled& DajNajranijiPregled()const {
        if(broj == 0)throw std::domain_error("Nema registriranih pregleda");
        auto pom = std::min_element(pregledi, pregledi + broj, [](Pregled *p1, Pregled * p2){
            return Pregled::DolaziPrije(*p1,*p2);
        });
        return **pom;
    }
    void IsprazniKolekciju(){
        Dealociraj();
        pregledi = new Pregled*[kapacitet];
        broj = 0;
    }
    void ObrisiNajranijiPregled();
    void ObrisiPregledePacijenta(std::string ime);
    void IspisiPregledeNaDatum(Datum dat)const{
        for(int i = 0; i < broj; i++){
            if(pregledi[i]->DajDatumPregleda() == dat){
                pregledi[i]->Ispisi();
            }
        }
    }
    void IspisiSvePreglede()const{
        //std::cout << "Svi pregledi:" <<std::endl;
        std::sort(pregledi, pregledi + broj, [](Pregled *p1, Pregled *p2){
            return Pregled::DolaziPrije(*p1, *p2);
        });
        for(int i = 0; i < broj; i++){
            pregledi[i]->Ispisi();
        }
    }
};

Pregledi &Pregledi::operator =(const Pregledi &p){
  /* std::swap(broj, p.broj);
   std::swap(pregledi,p.pregledi);
    return *this;*/
    if(&p !=this){
        Pregled **np = new Pregled*[p.kapacitet]{};
        try{
            for(int i = 0; i < broj; i++)np[i] = new Pregled(*p.pregledi[i]);
        }catch(...){
            for(int i = 0; i < broj; i++) delete np[i];
            delete [] np;
            throw;
        }
        Dealociraj();
        broj = p.broj;
        pregledi = np;
    }
    return *this;

}
/*

Liga &Liga::operator =(Liga l) {
 if(l.max_br_timova != max_br_timova)
 throw std::logic_error("Nesaglasni kapaciteti liga");
 std::swap(broj_timova, l.broj_timova); std::swap(timovi, l.timovi);
 return *this;
}

Liga &Liga::operator =(const Liga &l) {
 if(l.max_br_timova != max_br_timova)
 throw std::logic_error("Nesaglasni kapaciteti liga");
 if(&l != this) {
 Tim *novi_timovi = new Tim*[l.max_br_timova]{};
 try {
 for(int i = 0; i < broj_timova; i++) novi_timovi[i] = new Tim(*l.timovi[i]);
 }
 catch(...) {
 for(int i = 0; i < broj_timova; i++) delete novi_timovi[i];
 delete[] novi_timovi;
 throw;
 }
 Dealociraj();
 broj_timova = l.broj_timova; timovi = novi_timovi;
 }
 return *this;
}



*/

Pregledi::Pregledi(const Pregledi &p): broj(p.broj), kapacitet(p.kapacitet),pregledi(new Pregled*[p.kapacitet]{}) {
        try{
            for(int i = 0; i < broj; i++){
                pregledi[i] = new Pregled(*p.pregledi[i]);
            }
        }
        catch(...){
            Dealociraj();
            throw;
        }
}
Pregledi::Pregledi(std::initializer_list<Pregled> p) : pregledi(new Pregled*[p.size()]{}), kapacitet(p.size()), broj(p.size()){
        try{
            int i = 0;
            for(const auto &x : p){
            auto pom = new Pregled(x);
            pregledi[i] = pom;
            i++;
            if(broj > kapacitet) throw std::range_error("Dostignut maksimalni broj pregleda");
        }
        }catch(...){
            Dealociraj();
            throw;
        }
        
}
Pregledi::Pregledi(Pregledi &&p) : broj(p.broj), kapacitet(p.kapacitet), pregledi(p.pregledi){
    p.pregledi = nullptr;
    p.broj = 0;
}
void Pregledi::ObrisiNajranijiPregled(){
    if(broj == 0) throw std::range_error("Prazna kolekcija");
    auto &pom = DajNajranijiPregled();
    for(int i = 0; i < broj; i++){
        if(&pom == pregledi[i]){
            //std::cout << "OKOKOK";
            delete pregledi[i];
            for(int j = i; j < broj-1; j++){
                pregledi[j] = pregledi[j+1];
            }
            broj--;
            break;
        }
    }
}

void Pregledi::ObrisiPregledePacijenta(std::string ime){
    if(broj == 0) throw std::range_error("Prazna kolekcija");
    for(int i = 0; i < broj; i++){
        if( ime == pregledi[i]->DajImePacijenta()){
            //std::cout << "OK";
            delete pregledi[i];
            for(int j = i; j < broj-1; j++){
                pregledi[j] = pregledi[j+1];
            }
            i--;
            broj--;
        }
    }

}
void Pregled::Ispisi(){
    std::cout << std::left << std::setw(30) << ime;
    datum.Ispisi();
    std::cout << " ";
    vrijeme.Ispisi();
    std::cout << std::endl;
}

bool Pregled::DolaziPrije(const Pregled &p1, const Pregled &p2){
    if(p1.DajDatumPregleda().dajGodinu() < p2.DajDatumPregleda().dajGodinu())return true;
    if(p1.DajDatumPregleda().dajGodinu() > p2.DajDatumPregleda().dajGodinu())return false;
    if(p1.DajDatumPregleda().dajMjesec() < p2.DajDatumPregleda().dajMjesec())return true;
    if(p1.DajDatumPregleda().dajMjesec() > p2.DajDatumPregleda().dajMjesec())return false;
    if(p1.DajDatumPregleda().dajDan() < p2.DajDatumPregleda().dajDan())return true;
    if(p1.DajDatumPregleda().dajDan() > p2.DajDatumPregleda().dajDan())return false;

    if(p1.DajVrijemePregleda().dajSate() < p2.DajVrijemePregleda().dajSate()) return true;
    if(p1.DajVrijemePregleda().dajSate() < p2.DajVrijemePregleda().dajSate()) return false;
    if(p1.DajVrijemePregleda().dajMinute() < p2.DajVrijemePregleda().dajMinute())return true;
    if(p1.DajVrijemePregleda().dajMinute() < p2.DajVrijemePregleda().dajMinute())return false;
    return false;
}

void Pregled::PomjeriDanUnaprijed(){
    int dan = datum.dajDan(), mjesec = datum.dajMjesec(),godina = datum.dajGodinu();
    int broj_dana[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((godina % 4 == 0 && godina % 100 != 0) || godina % 400 == 0) broj_dana[1]++;
    dan++;
    if(dan > broj_dana[mjesec - 1]) dan = 1, mjesec++;
    if(mjesec > 12) mjesec = 1, godina++;
    datum = Datum{dan,mjesec,godina};
}

void Pregled::PomjeriDanUnazad(){
    int dan = datum.dajDan(), mjesec = datum.dajMjesec(),godina = datum.dajGodinu();
    int broj_dana[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((godina % 4 == 0 && godina % 100 != 0)|| godina % 400 == 0) broj_dana[1]++;
    dan--;
    if(dan == 0){
        mjesec--;
        if(mjesec == 0)
        {
            mjesec = 12;
            godina--;
            }
            dan = broj_dana[mjesec-1];
    }
    datum = Datum{dan,mjesec,godina};
}

void Datum::Postavi(int d, int m, int g) {
 int broj_dana[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 if((g % 4 == 0 && g % 100 != 0) || g % 400 == 0) broj_dana[1]++;
 if(g < 1 || d < 1 || m < 1 || m > 12 || d > broj_dana[m - 1])
 throw std::domain_error("Neispravan datum");
 dan = d; mjesec = m; godina = g;
}

void Vrijeme::Postavi(int sati, int minute){
    if (sati < 0 || sati > 23 || minute < 0 || minute > 59)
        throw std::domain_error("Neispravno vrijeme");
    this->sati = sati;
    this->minute = minute; 
}


int main ()
{
   /* Pregledi prvi(5);
    prvi.RegistrirajPregled("Ime", {31,12,2000}, {20,20});
    prvi.RegistrirajPregled("Ime2", {31,12,2000}, {20,20});
    prvi.RegistrirajPregled("Ime", {1,12,2000}, {20,20});
    prvi.RegistrirajPregled("Ime", {2,12,2000}, {20,20});
    prvi.RegistrirajPregled("Ime5", {31,12,2000}, {20,20});
    prvi.ObrisiNajranijiPregled();
    prvi.ObrisiPregledePacijenta("Ime");
    auto pom = prvi.DajNajranijiPregled();

    prvi.IspisiSvePreglede();
    std::cout <<prvi.DajBrojPregledaNaDatum({31,12,2000});
    std::cout << " " << prvi.DajBrojPregleda();*/

std::cout << "Unesite maksimalni broj pregleda: ";
int pom = 0;
std::cin >> pom;
Pregledi pregledi(pom);
  int d = 0,m = 0,g = 0,s = 0,min = 0;
  int k = 0;
  std::string ime{};
  while(true){
      std::cout << "1. Registriraj Pregled\n"
                     "2. Daj Broj Pregleda\n"
                     "3. Daj Broj Pregleda Na Datum\n"
                     "4. Daj Najraniji Pregled\n"
                     "5. Obrisi Najraniji Pregled\n"
                     "6. Obrisi Preglede Pacijenta\n"
                     "7. Ispisi Preglede Na Datum\n"
                     "8. Ispisi Sve Preglede\n"
                     "9. Isprazni Kolekciju\n"
                    "10. Izlaz" <<std::endl;
      std::cout << "Unesite izbor: ";
     // std::cin.ignore(1000, '\n');
      std::cin >> k;
      //std::cin.ignore(1000,'\n');
      //std::cin.clear();
      //if(k == 10)break;
      if(k == 1){
          std::cout << "Unesite ime pacijenta: ";
          //std::cin >> ime;
          //std::cin.ignore();
         std::cin.ignore(1000, '\n');
          std::cin.clear();
          std::getline(std::cin, ime);

          std::cout << "Unesite datum i vrijeme pregleda (dan mjesec godina sati minute): ";
          std::cin >> d >> m >> g >> s >> min;
          //std::cin.ignore(1000, '\n');
          //std::cin.clear();
          try{
              pregledi.RegistrirajPregled(ime, d, m, g, s, min);
          }catch(std::range_error &c){
              std::cout << c.what() << std::endl;
          }
          
      }else if(k == 2){
          std::cout << "Ukupan broj pregleda: " << pregledi.DajBrojPregleda() <<std::endl;
      }else if(k == 3){
          std::cout << "Unesite datum (dan mjesec godina): ";
          std::cin >> d >> m >> g;
          //std::cin.ignore(1000, '\n');
          //std::cin.clear();
          Datum dat(d,m,g);
          std::cout << "Broj pregleda na datum: " << pregledi.DajBrojPregledaNaDatum(dat) << std::endl;
      }else if(k == 4){
          Pregled pom = pregledi.DajNajranijiPregled();
          pom.Ispisi();
      }else if(k == 5){
          pregledi.ObrisiNajranijiPregled();
          std::cout << "Najraniji pregled je obrisan." << std::endl;
      }else if(k == 6){
          std::cout << "Unesite ime pacijenta: ";
          std::cin.ignore(1000, '\n');
          std::cin.clear();
          //std::cin.ignore();
          std::getline(std::cin, ime);
          pregledi.ObrisiPregledePacijenta(ime);
          std::cout << "Pregledi za pacijenta " << ime << " su obrisani." << std::endl;
      }else if(k == 7){
          std::cout <<"Unesite datum: ";
          //std::cin.ignore(1000, '\n');
          //std::cin.clear();
          std::cin >> d >> m >> g;
          Datum dat(d,m,g);
          pregledi.IspisiPregledeNaDatum(dat);
      }else if(k == 8){
          std::cout << "Svi pregledi: " << std::endl;
          pregledi.IspisiSvePreglede();
      }else if(k == 9){
          pregledi.IsprazniKolekciju();
          std::cout << "Kolekcija ispraznjena." << std::endl;
      }else if(k == 10){
          std::cout << "Kraj programa.";
          break;
      }else break;
  }


	return 0;
}
