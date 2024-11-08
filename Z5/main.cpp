 //TP 2023/2024: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <deque>
#include <exception>
#include <type_traits>

auto pomnozi(std::string a, std::string b){
    //std::cout << "greska";
    throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti"); 
}
template <typename tip1, typename tip2>
auto pomnozi(tip1 a, tip2 b){
    return a *b;
}

template <typename Tip>
using Matrica = std::vector<std::vector<Tip>>;
template <typename tip1, typename tip2>
auto KreirajTablicuMnozenja(tip1 &v1, tip2 &v2){
    auto p1 = std::begin(v1);
    auto p2 = std::end(v1);
    auto p3 = std::begin(v2);
    auto p4 = std::end(v2);
    int l1 = 0, l2 = 0;
    while(p1!=p2){
        p1++;
        l1++;
    }
    while(p3!=p4){
        p3++;
        l2++;
    }
    if(l1!=l2) throw std::range_error("Kontejneri nisu iste duzine");
    auto pok = std::begin(v1);
    auto pok2 = std::begin(v2);


    decltype (pomnozi(*pok,*pok2)) **a = {};
    decltype (pomnozi(*pok,*pok2)) *memorija = {};
    try{
        memorija = new decltype (pomnozi(*pok,*pok2))[(l1*(l1+1))/2];
        a = new decltype(pomnozi(*pok,*pok2)) *[l1];
        int pom = 0;
        for(int i = 0; i < l1; i++){
            a[i] = memorija + pom;
            pom +=(i+1);
        }
        auto p = std::begin(v1);
        for(int i = 0; i < l1; i++){
            auto pp = std::begin(v2);
            for(int j = 0; j < i+1; j++){
                if(*p **pp != *pp * *p){
                    delete [] memorija;
                    delete [] a;
                    throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");   
                }
                a[i][j]  = *p ** pp;
                pp++;
            }
        p++;
        }
    return a;

    }catch(const std::bad_alloc &){
        /*for(int i = 0; i < l1; i++){
            delete[] a[i];
        }*/
        delete [] memorija;
        delete[] a;
        throw std::range_error("Nema dovoljno memorije");
    }
}

int main ()
{
    std::cout << "Duzina sekvenci: "<<std::endl;
    int k = 0;
    std::cin >> k;
    std::vector<double>a;
    double pom;
    std::cout <<"Elementi prve sekvence: "<<std::endl;
    for(int i = 0; i < k; i++){
        std::cin >> pom;
        a.push_back(pom);
    } 
    std::deque<double>b;
    std::cout <<"Elementi druge sekvence: "<<std::endl;
    for(int i = 0; i < k; i++){
        std::cin >> pom;
        b.push_back(pom);
    }
    std::cout <<"Tablica mnozenja: " <<std::endl;

    try{
    auto matrica = KreirajTablicuMnozenja(a, b);
    for(int i = 0; i < k; i++){
        for(int j = 0; j <=i; j++){
            std::cout << *(*(matrica + i) + j) << " ";
        }
        std::cout << std::endl;
    }
    for(int i = 0; i < k; i++){
        delete[] matrica[i];
    }
    delete [] matrica;
    }catch(std::exception &poruka){
        std::cout << poruka.what();
    }

	return 0;
}
