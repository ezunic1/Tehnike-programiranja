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
    virtual ~Spremnik() {}
    Spremnik(double t, std::string na) : tezina(t), naziv(na){}
    virtual void Ispisi()const = 0;
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
    void Ispisi() const override{
        std::cout << "Vrsta spremnika: Sanduk" <<std::endl;
        std::cout << "Sadrzaj: " << naziv << std::endl;
        std::cout << "Tezine predmeta: ";
        for(auto x : tezine){
            std::cout << x << " ";
        }
        std::cout << "(kg)" <<std::endl;
        std::cout << "Vlastita tezina: " << tezina << " (kg)" <<std::endl;
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
    void Ispisi()const override{
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
    void Ispisi() const override{
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
    Spremnik *DodajSpremnik(std::shared_ptr<Spremnik>s,bool vlasnistvo ){
        if(vlasnistvo){
            spremnici.push_back(s);
        }else{
            auto x = (std::shared_ptr<Spremnik>(s->DajKopiju()));
            spremnici.push_back(x);
        }
        return s.get();
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

class PolimorfniSpremnik{
    Spremnik *p;
    public:
    PolimorfniSpremnik() : p(nullptr){}
    ~PolimorfniSpremnik(){delete p;}
    PolimorfniSpremnik(const Spremnik &s) : p(s.DajKopiju()){}
    PolimorfniSpremnik(const PolimorfniSpremnik &s){
        if(!s.p) p = nullptr;
        else p = s.p->DajKopiju();
    }
    PolimorfniSpremnik(PolimorfniSpremnik &&s){
        p = s.p;
        s.p = nullptr;
    }
    PolimorfniSpremnik &operator = (const PolimorfniSpremnik &s){
        if(this != &s){
            delete p;
            if(s.p != nullptr) p = s.p->DajKopiju();
            else {
                p = nullptr;
            }
        }
        return *this;
    }
    PolimorfniSpremnik &operator = (PolimorfniSpremnik &&s){
        if(this!=&s){
            delete p;
            p = s.p;
            s.p = nullptr;
        }
        return *this;
    }

    void Ispisi(){
        if(!p) throw std::logic_error("Nespecificiran spremnik");
        p->Ispisi();
    }
    double DajTezinu()const{
        if(!p) throw std::logic_error("Nespecificiran spremnik");
        return p->DajTezinu();
    }
    double DajUkupnuTezinu(){
        if(!p) throw std::logic_error("Nespecificiran spremnik");
        return p->DajUkupnuTezinu();
    }; 
};

/*class PolimorfniSpremnik{
    std::shared_ptr<Spremnik>p;
    public:
    PolimorfniSpremnik() : p(nullptr){}
    ~PolimorfniSpremnik(){}
    PolimorfniSpremnik(const Spremnik &s) : p(s.DajKopiju()){}
    PolimorfniSpremnik(const PolimorfniSpremnik &s){
        if(!s.p) p = nullptr;
        else p = std::shared_ptr<Spremnik>(s.p->DajKopiju());
    }
    PolimorfniSpremnik(PolimorfniSpremnik &&s){
        p = s.p;
        s.p = nullptr;
    }
    PolimorfniSpremnik &operator = (const PolimorfniSpremnik &s){
        if(this != &s){
            std::shared_ptr<Spremnik> pp = nullptr;
            if(s.p != nullptr) pp = std::shared_ptr<Spremnik>(s.p->DajKopiju());
             p = pp;
        }
        return *this;
    }
    PolimorfniSpremnik &operator = (PolimorfniSpremnik &&s){
        if(this!=&s)std::swap(p, s.p);
        return *this;
    }

    void Ispisi(){
        if(!p) throw std::logic_error("Nespecificiran spremnik");
        p->Ispisi();
    }
    double DajTezinu()const{
        if(!p) throw std::logic_error("Nespecificiran spremnik");
        return p->DajTezinu();
    }
    double DajUkupnuTezinu(){
        if(!p) throw std::logic_error("Nespecificiran spremnik");
        return p->DajUkupnuTezinu();
    }; 
};*/
int main ()
{

    /*Skladiste a;
    std::vector<double> pom{1,2,34,5,63};
    a.DodajBure(10, "Burence", 2000, 100);
    a.DodajSanduk(10, "Sanduce", pom);
    auto x = a.DodajVrecu(1000, "Vrecica",2);
   // a.DodajVrecu(12, "Vreca2", 14);
    //a.IzlistajSkladiste();
    //a.BrisiSpremnik(x);
    //a.IzlistajSkladiste();
    //a.DajNajlaksi().Ispisi();
    //a.DajNajtezi().Ispisi();
    //std::cout << a.BrojPreteskih(4);
   // a.UcitajIzDatoteke("dat.txt");
    a.IzlistajSkladiste();
    Bure pom1(100, "Burce", 1500, 100);
    //Spremnik pom2(pom1);
    PolimorfniSpremnik b(pom1);
    std::cout << std::endl;
    b.Ispisi();*/
    PolimorfniSpremnik s1 = Bure(5,"Benzin", 930, 70); // s1 je bure
    PolimorfniSpremnik s2, s3; // s2 i s3 su nespecificirani
    s2 = Sanduk(3, "Tepsije", {0.5, 0.8, 0.6, 0.5}); // s2 je sada sanduk
    s3 = Vreca(0.4, "Brasno", 30); // a s3 vreca
    std::cout << s1.DajTezinu() << std::endl;
    std::cout << s2.DajUkupnuTezinu() << std::endl;
    s3.Ispisi();
    s1 = s2; // sad je i s1 sanduk...
    s1.Ispisi();
	return 0;
    
    
}
