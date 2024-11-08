//TP 2023/2024: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>

bool kriterij(std::pair<double,double> a, std::pair<double,double> b){
    return a.first < b.first;

}

std::function<double(double)> KubnaInterpolacija(std::vector<std::pair<double,double>> v){
    //provjeriti ima li ih vise od 4
    //moraju x-ovi biti razliciti
    if(v.size() < 4)throw std::domain_error("Nedovoljan broj cvorova");
    std::sort(std::begin(v), std::end(v), kriterij);
    for(int i = 0; i < v.size(); i++){
        for(int j = i+1; j < v.size(); j++){
            if(v.at(i).first == v.at(j).first)throw std::domain_error("Neispravni cvorovi");
        }
    }
    return [=](double x){
        if( x < v.at(0).first || x > v.at(v.size()-1).first){
            //std::cout << x << "   " << v.at(0).first << "    " << v.at(v.size()-1).first<< std::endl;
            throw std::range_error("Argument izvan opsega"); /////////////
        }
        if(x == v.at(v.size()-1).first)return v.at(v.size()-1).second;
        int i  = 0;
        while(x > v.at(i).first){
            i++;
        };
        //i--;
        if(i!=0)i--;
        if(i == 0)i = 1;
        if(i == v.size()-2) i = v.size()-3;
        double pom1 = 0, pom2 = 1;
        for(int k = i-1; k <= i+2; k++){
            pom2 = 1;
            for(int j = i-1; j <= i+2; j++){
                //std::cout << v.at(j).first << " " << std::endl;
                if(k == j)continue;
                pom2*=(x - v.at(j).first ) / ( v.at(k).first -v.at(j).first);
            }   
            pom2*=v.at(k).second;
            pom1+=pom2;
        }
        return pom1;
  };
}
std::function<double(double)> KubnaInterpolacija(std::function<double(double)>f, double x_min, double x_max, double x_d){
    std::vector<std::pair<double,double>> v;
    if(x_min > x_max || x_d <=0) throw std::domain_error("Nekorektni parametri");
    double pomx = x_min;
    while(pomx < x_max || std::fabs(pomx - x_max) < 0.00001){
        //std::cout << "a";
        auto pom = std::make_pair(pomx, f(pomx));
        v.push_back(pom);
        pomx+= x_d; 
        //if(fabs(x_max - pomx) < 0.00001){
           // v.push_back(std::make_pair(pomx, f(pomx)));
           // break;
        //}
    }
    return KubnaInterpolacija(v);
}


int main ()
{
    
    /*std::vector<std::pair<double,double>> v = {{1, 3}, {2, 5}, {4, 4}, {5, 2}, {7, 1}};
    //auto a = KubnaInterpolacija(v);
    //std::cout << a(2.5);
    auto a = KubnaInterpolacija([](double x){return x*x + sin(x) + log(x+1);},0, 1, 0.2 );
    std::cout << a(0.3);*/
    try{

    
    std::cout << "Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): " << std::endl;
    int n = 0;
    std::cin >> n;
    std::vector<std::pair<double,double>> v;
    if(n == 1){
        std::cout << "Unesite broj cvorova: " << std::endl;
        int k = 0;
        std::cin >> k;
        std::cout << "Unesite cvorove kao parove x y: " << std::endl;
        int x, y;
        for(int i = 0; i < k; i++){
            std:: cin >> x >> y;
            v.push_back(std::make_pair(x,y));
        }
        std::sort(std::begin(v), std::end(v), kriterij);
        auto fun = KubnaInterpolacija(v);
        while(true){
            std::cout << "Unesite argument (ili \"kraj\" za kraj): " << std::endl;
            double z = 0;
            std::cin >> z;
            if(!std::cin)break;
            if(z < v.at(0).first || z > v.at(v.size()-1).first){
                std::cout << "Argument izvan opsega!" << std::endl;
                continue;
            }
            std::cout << "f(" << z << ") = " << fun(z) << std::endl;
        }  
    }
    else if(n == 2){
        std::cout << "Unesite krajeve intervala i korak: " << std::endl;
        double x_min, x_max, x_d;
        std::cin >> x_min >> x_max >> x_d;
        auto fun = KubnaInterpolacija([](double x){return x*x + sin(x) + log(x+1);},x_min, x_max, x_d );

        while(true){
            std::cout << "Unesite argument (ili \"kraj\" za kraj): " << std::endl;
            double z = 0;
            std::cin >> z;
            if(!std::cin)break;
            if(z < x_min || z > x_max){
                std::cout << "Argument izvan opsega!" << std::endl;
                continue;
            }
            std::cout << "f(" << z << ") = " << z*z + sin(z) + log(z+1) << " fapprox(" << z << ") = " << fun(z) << std::endl;

        }
    }
    }catch(const std::domain_error &c){
        std::cout << c.what();
    }

	return 0;
}
