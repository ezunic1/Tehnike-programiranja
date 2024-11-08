//TP 2023/2024: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <deque>
#include <iomanip>

template <typename tip>
using matrica = std::vector<std::vector<tip>>;

int funk(int x, int y){
    //if(y == 0)throw std::runtime_error("Greska");
    return x*x+y;
}


template <typename tip1, typename tip2, typename funkcija>
auto GeneraliziraniKroneckerovProizvod(const tip1 &a, const tip2 &b, funkcija fun) ->matrica<decltype(fun(a[0][0], b[0][0]))>{
    if(std::begin(a) == std::end(a) || std::begin(b) == std::end(b)){
        throw std::domain_error ("Parametri nemaju formu matrice");
    }
    int m = 0, p = 0, n = 0, q = 0;
    auto p1 = std::begin(a[0]);
    auto p2 = std::end(a[0]);
    
    //int brojac = 0;
    while(p1!=p2){
        n++;
        p1++;
    }
    auto p3 = std::begin(a);
    auto p4 = std::end(a);
    while(p3!=p4){
        m++;
        p3++;
    }
    auto p5 = std::begin(b[0]);
    auto p6 = std::end(b[0]);
    while(p5!=p6){
        q++;
        p5++;
    }
    auto p7 = std::begin(b);
    auto p8 = std::end(b);
    while(p7!=p8){
        p++;
        p7++;
    }
    //std::cout << m << " " << n << " ";
    bool prvi = true;
    int brojac = 0;
    for(int i = 0; i < m; i++){
        brojac = 0;
        auto u = std::begin(a[i]);
        auto g = std::end(a[i]);
        while(u!=g){
            brojac++;
            u++;
        }
        if(brojac!=n)prvi = false;
    }
    bool drugi = true;
    for(int i = 0; i < p; i++){
        brojac = 0;
        auto u = std::begin(b[i]);
        auto g = std::end(b[i]);
        while(u!=g){
            brojac++;
            u++;
        }
        if(brojac!=q)drugi = false;
    }

    if(!prvi && !drugi){
        throw std::domain_error ("Parametri nemaju formu matrice");
    }else if(!prvi){
        throw std::domain_error("Prvi parametar nema formu matrice");
    }else if(!drugi){
        throw std::domain_error("Drugi parametar nema formu matrice");
    }
    try{
        auto pom = fun(a[0][0], b[0][0]);
        //std::cout << pom;
        matrica<decltype(pom)> v3(m*p, std::vector<decltype(pom)>(n*q));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                for(int k = 0; k < p; k++){
                    for(int l = 0; l < q; l++){
                        v3.at(k + i*p).at(l + q*j) = fun(a[i][j], b[k][l]);
                    }
                }
            }
        }
        //matrica<decltype(m)> v3(m*p, std::vector<decltype(m)>(n*q));
        return v3;
    } 
     catch (...) {
         throw std::runtime_error("Neocekivani problemi pri racunanju");
    }
}
int BrojCifara(int a){
    int x = 0;
    if(a < 0){
        x++;
        a*=-1;
    }
    while(a!=0){
        a/=10;
        x++;
    }
    return x;
}

int najsiri(matrica<double> v3){
    int najsiri = 0;
    for(int i = 0; i < v3.size(); i++){
        for(int j = 0; j < v3.at(i).size(); j++){
            if(BrojCifara(v3.at(i).at(j)) > najsiri){
                najsiri = BrojCifara(v3.at(i).at(j));
            }
        }
    }
    return najsiri + 1;
}


int main ()
{
    /*std::vector<std::vector<int>> v1 = {{3, 5, 2},{4, 0, -1}};
    std::vector<std::vector<int>> v2 = {{1, 4, -2, 3},{0, 5, 4, 1}, {2, 0, 0, 3}};
    auto v3 = GeneraliziraniKroneckerovProizvod(v1,v2,funk);

    for(int i = 0; i < v3.size(); i++){
        for(int j = 0; j < v3.at(i).size(); j++){
            std::cout << v3.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }*/
    std::vector<std::deque<double>> v1;
    std::deque<std::vector<double>> v2;
    std::cout << "Unesite dimenzije prve matrice: ";
    int m, n;
    std::cin >> m >> n;
    std::cout << "Unesite elemente prve matrice: ";
    int k = 0;
    v1.resize(m, std::deque<double>(n));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            std:: cin >> k;
            v1.at(i).at(j) = k;
        }
    }
    std::cout << "Unesite dimenzije druge matrice: ";
    std::cin >> m >> n;
    std::cout << "Unesite elemente druge matrice: ";
    v2.resize(m, std::vector<double>(n));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            std:: cin >> k;
            v2.at(i).at(j) = k;
        }
    }
    std::cout <<"Njihov Kroneckerov proizvod glasi: " << std::endl;
    auto v3 = GeneraliziraniKroneckerovProizvod(v1, v2, [](double x, double y){
        return x*y;
    });
    int pom = najsiri(v3);
    for(int i = 0; i < v1.size()*v2.size(); i++){
        for(int j = 0; j < v1.at(0).size()* v2.at(0).size(); j++){
            std::cout <<std::setw(pom) <<std::right <<v3.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
	return 0;
}
