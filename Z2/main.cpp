//TP 2023/2024: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>
class Berza{
    
    std::vector<int>cijene;
    int min = 0, max;

    public:
    Berza(int a, int b){
        if(a < 0 || b < 0 || a > b) throw std::range_error("Ilegalne granicne cijene");
        min  = a;
        max = b;
    }
    explicit Berza(int a){
        if(a < 0) throw std::range_error("Ilegalne granicne cijene");
        min = 0;
        max = a;
    }
    void RegistrirajCijenu(int cijena);
    void BrisiSve(){cijene.clear();}
    int DajMinimalnuCijenu() const{
        if (cijene.empty()) throw std::range_error("Nema registriranih cijena");
        return *std::min_element(cijene.begin(), cijene.end());
    }
    int DajMaksimalnuCijenu() const{
        if (cijene.empty())throw std::range_error("Nema registriranih cijena");
        return *std::max_element(cijene.begin(), cijene.end());
    }
    bool operator !()const {
        return cijene.size() == 0;
    }
    int DajBrojCijenaVecihOd(int x)const{
        if(cijene.empty())throw std::range_error("Nema registriranih cijena");
        return std::count_if(cijene.begin(), cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, x));
    }
    int DajBrojRegistriranihCijena()const{
        return cijene.size();
    }
    int operator[](int i)const{
        if( i <= 0 || i > cijene.size())throw std::range_error("Neispravan indeks");
        return cijene.at(i-1);
    }
    Berza &operator++(){
        std::transform(cijene.begin(), cijene.end(), cijene.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 100));
        int x = std::count_if(cijene.begin(), cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, max));
        if ( x != 0){
            std::transform(cijene.begin(), cijene.end(), cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, 100));
            throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        }
        return *this;
    }
    Berza operator++(int){
        auto pom = *this;
        ++(*this);
        return pom;
    }
    Berza &operator--(){
        std::transform(cijene.begin(), cijene.end(), cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, 100));
        int x = std::count_if(cijene.begin(), cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, min));
        if ( x != 0){
            std::transform(cijene.begin(), cijene.end(), cijene.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 100));
            throw std::range_error("Prekoracen dozvoljeni opseg cijena");
        }
        return *this;
    }
    Berza operator--(int){
        auto pom = *this;
        --(*this);
        return pom;
    }    

    Berza operator -()const{
        Berza pom = *this;
        std::transform(cijene.begin(), cijene.end(), pom.cijene.begin(), std::bind(std::minus<int>(), max+min, std::placeholders::_1));
        return pom;
    }
    Berza operator +(int y){
        Berza pom = *this;
        std::transform(cijene.begin(), cijene.end(), pom.cijene.begin(), std::bind(std::plus<int>(), std::placeholders::_1, y));
        int x = std::count_if(pom.cijene.begin(), pom.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, max));
        if ( x != 0)throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
        return pom;
    }
    Berza operator -(int y){
        Berza pom = *this;
        std::transform(cijene.begin(), cijene.end(), pom.cijene.begin(), std::bind(std::minus<int>(), std::placeholders::_1, y));
        int x = std::count_if(pom.cijene.begin(), pom.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, min));
        if ( x != 0)throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
        return pom;
    }
    friend Berza operator -(int y, Berza a){
        Berza pom = a;
        std::transform(a.cijene.begin(), a.cijene.end(), pom.cijene.begin(), std::bind(std::minus<int>(), y, std::placeholders::_1));
        int x = std::count_if(pom.cijene.begin(), pom.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, a.min));
        if (x != 0) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
        return pom;
    }
    friend Berza operator + (int y, Berza a){
        return a + y;
    }

    friend Berza operator + (const Berza &a, const Berza &b){
        if(a.cijene.size() != b.cijene.size() || a.min != b.min || a.max != b.max){
            throw std::domain_error("Nesaglasni operandi");
        }
        Berza pom(a.min, a.max);
        std::transform(a.cijene.begin(), a.cijene.end(), b.cijene.begin(), std::back_inserter(pom.cijene), std::plus<int>());
        int x = std::count_if(pom.cijene.begin(), pom.cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, pom.max));
        if ( x != 0){

            throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
        }
        return pom;
    }

    friend Berza operator - (const Berza &a, const Berza &b){
        if(a.cijene.size() != b.cijene.size() || a.min != b.min || a.max != b.max){
            throw std::domain_error("Nesaglasni operandi");
        }
        Berza pom(a.min, a.max);
        std::transform(a.cijene.begin(), a.cijene.end(), b.cijene.begin(), std::back_inserter(pom.cijene), std::minus<int>());
        int x = std::count_if(pom.cijene.begin(), pom.cijene.end(), std::bind(std::less<int>(), std::placeholders::_1, pom.min));
        if (x != 0){

            throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
        } 
        return pom;
    }

    Berza &operator +=(const Berza &a){
        *this = *this + a;
        return *this;
    }
    Berza &operator -=(const Berza &a){
        *this = *this - a;
        return *this;
    }


    Berza & operator +=(int x){
        *this = *this + x;
        return *this;
    }
    Berza & operator -=(int x){
        *this = *this - x;
        return *this;
    }
    bool operator ==(const Berza &b)const{
        return std::equal(this->cijene.begin(), this->cijene.end(), b.cijene.begin()) && cijene.size() == b.cijene.size();
    }

    bool operator !=(const Berza &b)const{
        return !(*this == b);
    }

    void Ispisi();
};

void Berza::RegistrirajCijenu(int cijena){
    if(cijena < min ||cijena > max)throw std::range_error("Ilegalna cijena");
    cijene.push_back(cijena);
}

void Berza::Ispisi(){
    auto pom = cijene;
    std::sort(pom.begin(), pom.end(), std::greater<int>());
    std::for_each(pom.begin(), pom.end(), [](auto x){
        std::cout << std::fixed<<std::setprecision(2) << double(x) / 100<< std::endl;
    });
}

int main ()
{
    Berza a(20000);
    a.RegistrirajCijenu(500);
    a.RegistrirajCijenu(250);
    a.RegistrirajCijenu(750);
    //++a;
    a.Ispisi();
    //a--;
    Berza pom = a + 1;
    //std::cout << a.DajBrojCijenaVecihOd(100);
    //a.Ispisi();
    pom.Ispisi();
    //a = 1 + a;
    //if( a == pom)std::cout << "ok";
    std::cout << a[3];
	return 0;
}
