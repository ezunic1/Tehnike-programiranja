//TP 2023/2024: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <type_traits>
#include <deque>
template <typename tip1, typename tip2, typename tip3>
tip3 UnijaBlokova(tip1 p1, tip1 p2, tip2 p3, tip2 p4, tip3 p5){
    auto pom = p5;
    while(p1!=p2){
        auto pom2 = pom;
        while(pom2!=p5){
            if(*p1 == *pom2)break;
            pom2++;
        }
        if(pom2 == p5){
            *p5 = *p1;
            p5++;
        }
        p1++;
    }
    while(p3!=p4){
        auto pom2 = pom;
        while(pom2!=p5){
            if(*p3 == *pom2)break;
            pom2++;
        }
        if(pom2 == p5){
            *p5 = *p3;
            p5++;
        }
        p3++;
    }
    return p5;
}

int main ()
{
    std::cout << "Unesite broj elemenata niza (max. 100): ";
    int x = 0;
    std::cin >> x;
    int k = 0;
    std::vector<double> a;
    std::deque<int> b;
    std::cout << "Unesite elemente niza: ";
    for(int i = 0; i < x; i++){
        std::cin >> k;
        a.push_back(k);
    }
    std::cout << "Unesite broj elemenata deka: ";
    std::cin >> x;
    std::cout << "Unesite elemente deka: ";
    for(int i = 0; i < x; i++){
        std::cin >> k;
        b.push_back(k);
    }
    std::vector<double> c(a.size() + b.size());
    auto p = UnijaBlokova(std::begin(a), std::end(a), std::begin(b), std::end(b), std::begin(c));
    c.resize(p - std::begin(c));

    std::cout << "Njihova unija glasi: ";
    for(int i = 0; i < c.size(); i++){
        std::cout << c.at(i) << " ";
    }
	return 0;
}
