//TP 2023/2024: Zadaća 3, Zadatak 2
#include <cctype>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>
#include <tuple>
#include <map>
#include <set>


typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string, int, int>>> Mapa;
bool je_slovo(char x){
    if((x >='a' && x <='z') || ( x >='A' && x<='Z') || (x>='0' && x <= '9')) return true;
    return false; 
}
Mapa KreirajIndeksPojmova(Knjiga k){
    Mapa izlazna;
    std::vector<std::string> v;
    bool pom = true;
    for(auto par : k){
        for(auto stranica : par.second){ 
            //std::cout << stranica << " ";
            //std::cout << stranica.size() << "------ ";
            for(int i = 0; i < stranica.size(); i++){
                std::string rijec{};
                while(stranica.at(i) == ' ' && i < stranica.size()-1)i++;
                pom = true;
                while(i < stranica.size() && je_slovo(stranica.at(i))){
                    rijec+=std::toupper(stranica.at(i));
                    i++;
                }
                for(int j = 0; j < v.size(); j++){
                    if(rijec == v.at(j)){
                        pom = false;
                        break;
                    }
                }
                if(pom && rijec.size() > 0){
                    v.push_back(rijec);
                }
            }
        }
    }
    //std::cout << v.size() << " duzina" << std::endl;
    for(int i = 0; i < v.size(); i++){
        std::set<std::tuple<std::string, int, int>> m;
        std::string kljuc = v.at(i);
        for(auto par : k){
            auto poglavlje = par.first;// naziv poglavlja
            auto niz = par.second;
            for(int j = 0; j < niz.size(); j++){ //broj stranice j+1
                for(int k = 0; k < niz.at(j).size(); k++){ // broj mjesta u stranici
                    std::string rijec{};
                    int pozicija = -1;
                    while(niz.at(j).at(k) == ' ' && k < niz.at(j).size()-1)k++;
                    while(k < niz.at(j).size() && je_slovo(niz.at(j).at(k))){
                        if(rijec.size() == 0)pozicija = k; 
                        rijec+=std::toupper(niz.at(j).at(k));
                        k++;
                    }
                    if(rijec == kljuc && pozicija!=-1){
                        m.insert(std::make_tuple(poglavlje, j+1, pozicija+1));
                    }
                }
             }
        }
        izlazna[kljuc] = m;
    }
    return izlazna;
}

std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(const std::string& rijec, const Mapa& m){
    std::set<std::tuple<std::string, int, int>> izlazni{};
    auto pom = rijec;
    auto it = pom.begin();
    while(it !=pom.end()){  
        if(!je_slovo(*it))throw std::domain_error("Neispravna rijec");
        *it = std::toupper(*it);
        it++;
    }
    //std::cout << pom;
    auto i = m.find(pom);
    if(i != m.end()){
        izlazni = i->second;
    }
    return izlazni;
}

void IspisiIndeksPojmova(Mapa ma){
    for(auto it = ma.begin(); it != ma.end(); it++){
        std::cout << it->first << ": ";
        auto v = it->second;
        int i = 0;
        for(auto x : v){
            std::cout << std::get<0>(x)<< "/" << std::get<1>(x) << "/" << std::get<2>(x);
            if(i < v.size()-1)std::cout << ", ";
            i++;
        }
        std::cout << std::endl;
    }
}

int main ()
{
    /*Knjiga k;
    k["A"] = {"ABC QWE STSDA ABC ABC DHI QWE HRKW DHI"}; 
    k["DRUGO"] = {"123 213 ", "   aSD    aaa sa   ", " s ", " ABC", "zzz"}; 
    Mapa ma = KreirajIndeksPojmova(k);
    IspisiIndeksPojmova(ma);
    auto v = PretraziIndeksPojmova( "abc", ma);
    std::cout << std::endl;
    for(int i = 0; i < v.size(); i++){
            std::cout << std::get<0>(v.at(i))<< "/" << std::get<1>(v.at(i)) << "/" << std::get<2>(v.at(i));
            if(i < v.size()-1)std::cout << ", ";
    }*/
    Knjiga k;
    std::string pom1,pom2;
    while(true){
        std::cout<< "Unesite naziv poglavlja: " << std::endl;
        getline(std::cin, pom1);
        if(pom1.size() == 0)break;
        std::vector<std::string> sadrzaj;
        int i = 1;
        while(true){
            std::cout << "Unesite sadrzaj stranice " << i << ": " << std::endl;
            getline(std::cin, pom2);
            if(pom2.size() == 0)break;
            sadrzaj.push_back(pom2);
            i++;
        }
        if(sadrzaj.size()>0) k[pom1] = sadrzaj;
    }
    Mapa ma = KreirajIndeksPojmova(k);
    std::cout << std::endl;
    std::cout << "Kreirani indeks pojmova: "<<std::endl;
    IspisiIndeksPojmova(ma);
    std::cout << std::endl;
    while(true){
        std::cout << "Unesite rijec: " << std::endl;
        getline(std::cin, pom1);
        if(pom1.size() == 0){
            std::cout << "Dovidjenja!";
            break;
        }
        try{
            auto vektor = PretraziIndeksPojmova(pom1, ma);
            if(vektor.size() == 0){
                std::cout << "Rijec nije nadjena!"<<std::endl;
                continue;
            }
            std::cout << "Rijec nadjena na pozicijama: ";
            int i = 0;
            for(auto x : vektor){
            std::cout << std::get<0>(x)<< "/" << std::get<1>(x) << "/" << std::get<2>(x);
            if(i < vektor.size()-1)std::cout << " ";
            i++;
        }
            std::cout << std::endl;
        }catch(std::domain_error &w){
            std::cout << "Neispravna rijec!" << std::endl;
            continue;
        }
    }
	return 0;
}
