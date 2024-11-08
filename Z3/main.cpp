//TP 2023/2024: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <fstream>

class Spremnik{
    protected:
    std::string naziv;
    double tezina;
    public:

    Spremnik(double t, std::string na) : tezina(t), naziv(na){}
    virtual ~Spremnik(){}
    virtual void Ispisi()const  = 0;
    double DajTezinu()const{return tezina;}
    virtual double DajUkupnuTezinu()const = 0; 
    virtual Spremnik* DajKopiju() const = 0;
};

class Sanduk : public Spremnik{
    std::vector<double> tezine;
    public:
    Sanduk(double t, std::string na, std::vector<double> v) : Spremnik(t,na), tezine(v){}
    double DajUkupnuTezinu()const override{
        double x = 0;
        for(auto k : tezine){
            x+=k;
        }
        return x+tezina;
    }
    void Ispisi()const override{
        std::cout << "Vrsta spremnika: Sanduk" <<std::endl;
        std::cout << "Sadrzaj: " << naziv << std::endl;
        std::cout << "Tezine predmeta: ";
        for(auto x : tezine){
            std::cout << x << " ";
        }
        std::cout << "(kg)" <<std::endl;
        std::cout << "Vlastita tezina: " << tezina << " (kg)"<<std::endl;
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" <<std::endl;
    }
    Spremnik* DajKopiju()const override{
        return new Sanduk(*this);
    }
};
class Vreca : public Spremnik{
    double tezina_m;
    public:
    Vreca(double t, std::string na, double te) : Spremnik(t,na), tezina_m(te){}
    double DajUkupnuTezinu()const override{
        return tezina + tezina_m;
    }
    void Ispisi() const override{
        std::cout << "Vrsta spremnika: Vreca" <<std::endl;
        std::cout << "Sadrzaj: " << naziv << std::endl;
        std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
        std::cout << "Tezina pohranjene materije: " << tezina_m << " (kg)" <<std::endl;
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" <<std::endl;
        //std::cout << std::endl <<std::endl;
    }
    Spremnik* DajKopiju()const override{
        return new Vreca(*this);
    }
};

class Bure : public Spremnik{
    double gustina;
    double zapremina;
    public:
    Bure(double t, std::string na, double g, double z) : Spremnik(t, na), gustina(g), zapremina(z){}
    double DajUkupnuTezinu()const override{
        return tezina + (gustina*zapremina)/1000;
    }
    void Ispisi()const  override{
        std::cout << "Vrsta spremnika: Bure" <<std::endl;
        std::cout << "Sadrzaj: " << naziv << std::endl;
        std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
        std::cout << "Specificna tezina tecnosti: " << gustina << " (kg/m^3)" <<std::endl;
        std::cout <<"Zapremina tecnosti: " << zapremina << " (l)" <<std::endl;
        std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" <<std::endl;
    }
    Spremnik* DajKopiju()const override{
        return new Bure(*this);
    }

};

class Skladiste{
    std::vector<std::shared_ptr<Spremnik>>spremnici;
    public:
    Skladiste() = default;
    /*~Skladiste(){
        while (!spremnici.empty()) {
        BrisiSpremnik(spremnici.back().get());
    }
    }*/
    Skladiste(const Skladiste &s){
        for(auto x : s.spremnici){
            spremnici.push_back(std::shared_ptr<Spremnik>(x->DajKopiju()));
        }
    }
    Skladiste &operator =(const Skladiste &s){
        if(&s != this){
            for(auto x : s.spremnici){
                 spremnici.push_back(std::shared_ptr<Spremnik>(x->DajKopiju()));
            }
        }
        return *this;
    }
    Spremnik * DodajSanduk(double t, std::string na, std::vector<double> v){
        auto x = std::make_shared<Sanduk>(t,na,v);
        spremnici.push_back(x);
        return x.get();
    }
    Spremnik * DodajVrecu(double t, std::string na, double te){
        auto x = std::make_shared<Vreca>(t,na,te);
        spremnici.push_back(x);
        return x.get();
    }
    Spremnik *DodajBure(double t, std::string na, double g, double z){
        auto x = std::make_shared<Bure>(t,na,g,z);
        spremnici.push_back(x);
        return x.get();
    }
    Spremnik *DodajSpremnik(Spremnik* s,bool vlasnistvo ){ 
        if(vlasnistvo){
            std::shared_ptr<Spremnik> sprt(s);
            spremnici.push_back(sprt);
        }else{
            auto x = (std::shared_ptr<Spremnik>(s->DajKopiju()));
            spremnici.push_back(x);
        }
        return s;
    }
    void BrisiSpremnik(Spremnik * s){
        int i = 0;
        for(auto x : spremnici){
            if(x.get() == s){
                spremnici.erase(spremnici.begin()+i);
            }
            i++;
        }
    }

    Spremnik & DajNajlaksi(){
        if(spremnici.size() == 0)throw std::range_error("Skladiste je prazno");
        auto min = spremnici.at(0);
        for(auto x : spremnici){
            if(x->DajTezinu()  < min->DajTezinu()){
                min = x;
            }
        }
        return *min;
    }
    Spremnik & DajNajtezi(){
        if(spremnici.size() == 0)throw std::range_error("Skladiste je prazno");
        auto max = spremnici.at(0);
        for(auto x : spremnici){
            if(x->DajTezinu()  > max->DajTezinu()){
               max= x;
            }
        }
        return *max;
    }
    int BrojPreteskih(double x)const{
        return std::count_if(spremnici.begin(), spremnici.end(), [x](std::shared_ptr<Spremnik>s){
            return s->DajUkupnuTezinu() > x;
        });
    }
    void IzlistajSkladiste()const{
        auto pom = spremnici;
        std::sort(pom.begin(), pom.end(), [](std::shared_ptr<Spremnik>s1, std::shared_ptr<Spremnik>s2){
            return s1->DajUkupnuTezinu()  > s2->DajUkupnuTezinu() ;
        });
        for(auto x : pom){
            x->Ispisi();
            //std::cout << std::endl;
        }
    } 
    
    void UcitajIzDatoteke(std::string dat){
        spremnici.clear();
        std::ifstream tok(dat);
        std::string red1;
        std::string naziv;
        std::string red2;
        double tezina, zapremina, gustina;
        int broj;
        char vrsta, znak;
        if(!tok) throw std::logic_error("Trazena datoteka ne postoji");
        while(tok>>vrsta){
            tok >> std::ws;
            std::getline(tok, red1);
            if(red1.size() == 0)throw std::logic_error("Datoteka sadrzi besmislene podatke");
           if(vrsta == 'S' || vrsta == 's'){
               std::vector<double> tezine;
               naziv = red1;
               if(!(tok >> tezina >> broj))throw std::logic_error("Datoteka sadrzi besmislene podatke");
               double pom;
               for(int i = 0; i < broj; i++){
                   if(!(tok >> pom))throw std::logic_error("Datoteka sadrzi besmislene podatke");
                   tezine.push_back(pom);
               }
            DodajSanduk(tezina, naziv, tezine);
           }else if(vrsta == 'V' || vrsta == 'v'){
               naziv = red1;
               double tezina_m;
               if(!(tok >> tezina >> tezina_m))throw std::logic_error("Datoteka sadrzi besmislene podatke");
               DodajVrecu(tezina, naziv, tezina_m);
           }else if(vrsta == 'B' || vrsta == 'b'){
               naziv = red1;
               if(!(tok >> tezina >>gustina >> zapremina))throw std::logic_error("Datoteka sadrzi besmislene podatke");
               DodajBure(tezina, naziv, gustina, zapremina);
           }else{
               throw std::logic_error("Datoteka sadrzi besmislene podatke");
           }
        }
    }
};



int main ()
{
    Skladiste a;
    try {
        a.UcitajIzDatoteke("ROBA.TXT");
        a.IzlistajSkladiste();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    


	return 0;
}
