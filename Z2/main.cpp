//TP 2023/2024: LV 11, Zadatak 8
// zadaca 4 zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <iomanip>

enum Pol {Musko = 1, Zensko = 2};

class GradjaninBiH{
    std::string imePrezime{};
    long long int JMBG{};
    Pol pol;
    int dan{};
    int mjesec{};
    int godina{};
    int sifraRegije{};
    int kod{};
    GradjaninBiH * prethodni{};
    static GradjaninBiH * pomocni;
    static int brojac;
    void datum(int d, int m, int g){
        int broj_dana[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if((g % 4 == 0 && g % 100 != 0) || g % 400 == 0) broj_dana[1]++;
        if(g < 1 || d < 1 || m < 1 || m > 12 || d > broj_dana[m - 1] || g > 2021)
        throw std::logic_error("error");
        dan = d; mjesec = m; godina = g;
    }

    void provjeriJmbg(long long int JMBG){
        GradjaninBiH::JMBG = JMBG;
        auto p = pomocni;
        while(p!=nullptr){
            if(JMBG == p->JMBG)throw std::logic_error("Vec postoji gradjanin sa istim JMBG");
            p = p->prethodni;
        }
        int niz[13]{};
        int pom = 0;
        int i = 0;
        while(JMBG!=0){
            pom = JMBG%10;
            JMBG/=10;
            niz[12-i] = pom;
            i++;
        }
        int c13 = 11 - (7* ( niz[0] + niz[6]) + 6 * (niz[1] + niz[7]) + 5 * (niz[2] + niz[8]) + 4 * (niz[3] + niz[9]) + 3 * (niz[4] + niz[10]) + 2 * (niz[5] + niz[11])) % 11;
        if(c13 == 11)c13 = 0;
        if(c13 !=niz[12])throw std::logic_error("JMBG nije validan");
        int d{},m{},g{};
        d = niz[0]*10 + niz[1];
        m = niz[2]*10 + niz[3];
        g = niz[4]*100 + niz[5]*10 + niz[6];
        if(g < 100)g+=2000;
        else g+=1000;
        try{
            datum(d,m,g);
        }catch(...){
            throw std::logic_error("JMBG nije validan");
        }
        sifraRegije = niz[7] * 10 + niz[8];
        kod = niz[9]*100 + niz[10]*10 + niz[11];
        if(kod < 500) pol = Pol::Musko;
        else pol = Pol::Zensko; 
    }
    void napraviJMBG(int d, int m, int g, int sifra, Pol p){
        try{
            datum(d,m,g);
        }catch(...){
            throw std::logic_error("Neispravni podaci");
        }
        sifraRegije = sifra;
        long long int pom = 0;
        int niz[13]{};
       // int pom2 = 0;
        niz[0] = d/10;
        niz[1] = d%10;
        niz[2] = m/10;
        niz[3] = m%10;
        g = g % 1000;
        niz[4] = g / 100;
        niz[5] = (g % 100)/10;
        niz[6] = g % 10;
        auto pok = pomocni;
        //pok = pok->prethodni;
        pol = p;
        //std::cout << p << std::endl;
        int pomkod = 0;
        if(pol == Pol::Musko){
            pomkod = 0;
        }else if(pol == Pol::Zensko){
            pomkod = 500;
        }
        while(pok !=nullptr){
            if(pok->dan == dan && pok->mjesec == mjesec && pok->godina == godina && pok->pol == pol){
                pomkod = pok->kod + 1;
               // std::cout << pok->kod << "*******" << std::endl;
                break;
            } 
            pok = pok->prethodni;
        }
        //std::cout << pomkod << "  brojac:" << brojac << std::endl;
        niz[7] = sifra / 10;
        niz[8] = sifra % 10;
        while(true){
            niz[9] = pomkod / 100;
            niz[10] = (pomkod % 100) / 10;
            niz[11] = pomkod % 10;
            niz[12] = 11 - (7* ( niz[0] + niz[6]) + 6 * (niz[1] + niz[7]) + 5 * (niz[2] + niz[8]) + 4 * (niz[3] + niz[9]) + 3 * (niz[4] + niz[10]) + 2 * (niz[5] + niz[11])) % 11;       
            if(niz[12] == 10){
                pomkod++;
                continue;
            }else if(niz[12] == 11){
                niz[12] = 0;
                break;
            }else{
                break;
            }
        }

        for(int i = 0; i < 13; i++){
            JMBG = JMBG * 10 + niz[i];
        }
        kod = pomkod;
    }
    public:
    GradjaninBiH(std::string ime,long long int jmbg_br): JMBG(jmbg_br), imePrezime(ime){
        if(ime.size() == 0)throw std::logic_error("Ime ne moze biti prazno!");
        provjeriJmbg(jmbg_br);
        prethodni = pomocni;
        pomocni = this;
        brojac++;
    }
    GradjaninBiH(std::string ime, int d, int m, int g, int sifra, Pol p): imePrezime(ime), dan(d), mjesec(m), godina(g), sifraRegije(sifra){
        napraviJMBG(d,  m,  g,  sifra, p);
        prethodni = pomocni;
        pomocni = this;
        brojac++;
    }
    ~GradjaninBiH(){
        if(this == pomocni){
            //auto x = pomocni;
            pomocni = prethodni;
            //delete x;
        }else{
            auto p = pomocni;
            while(p->prethodni !=this){
                p = p->prethodni;
            }
            p->prethodni = this->prethodni;
        }
    }

    GradjaninBiH * DajPrethodnog(){
        return prethodni;
    }
    void PostaviPrethodnog(GradjaninBiH * pom){
        prethodni = pom;
    }


    GradjaninBiH(const GradjaninBiH &a) = delete;
    GradjaninBiH operator =(const GradjaninBiH &a) = delete;
    std::string DajImeIPrezime()const{return imePrezime;}
    long long int DajJMBG() const{return JMBG;}
    int DajDanRodjenja() const{return dan;}
    int DajMjesecRodjenja() const{return mjesec;}
    int DajGodinuRodjenja() const{return godina;}
    int DajSifruRegije() const {return sifraRegije;}
    Pol DajPol() const{return pol;}
    void ispisi(){
        std::cout <<imePrezime << " " <<  dan <<  "." << mjesec << "." << godina << " JMBG: ";
        if(dan < 10)std::cout << "0";
        std::cout<< JMBG<< std::endl;
    }
    void PromijeniImeIPrezime(std::string ime){
        if(ime.size() == 0)throw std::logic_error("Ime ne moze biti prazno!");
        imePrezime = ime;
    }
};

GradjaninBiH* GradjaninBiH::pomocni{};
int GradjaninBiH::brojac = 0;

int main ()
{
    std::cout << "Unesite broj gradjana: " << std::endl;
    int n = 0;
    std::cin >> n;
    //std::cin.ignore();
    GradjaninBiH *niz[100];
    std::string ime{};
    int d{}, m{}, g{}, sifra{}, p{};
    Pol pol;
    for(int i = 0; i < n; i++){
        bool pom = false;

        while(true){
            try{
                std::cout << "Unesite podatke za " << i+1 << ". gradjanina: " << std::endl;
                std::cout << "Ime i prezime: ";
                std::cin.ignore();
                std::getline(std::cin, ime);
                std::cout << "Datum rodjenja: ";
                std::cin >> d >> m >> g;
                std::cout << "Sifra regije: ";
                std::cin >> sifra;
                std::cout << "Pol ( 1-Musko, 2-Zensko ): " << std::endl;
                std::cin >> p;
                if(p == 1) pol = Pol::Musko;
                else if(p == 2) pol = Pol::Zensko; 
                else throw std::logic_error("error");
                if(sifra > 99 || sifra < 0)throw std::logic_error("error");
                niz[i] = new GradjaninBiH(ime, d, m, g, sifra, pol);
                pom = true;
            }catch(...){
                std::cout << "Neispravni podaci. Molimo ponovite unos." << std::endl << std::endl;
                //i--;
            }
            if(pom == true)break;
        }     
    }
    std::cout << "Gradjani sortirani po starosti: " << std::endl;
    for (int i = 0; i < n; i++) {
        niz[i]->ispisi();
    }

	return 0;
}
