//TP 2023/2024: Zadaća 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <array>
#include <stdexcept>
#include <vector>
#include <exception>
enum class TretmanNegativnih {IgnorirajZnak, Odbaci, TretirajKao0, PrijaviGresku};

int BrojKvadrata (int x){
    if(x < 0) throw std::domain_error("Broj mora biti nenegativan");
    if(x == 0)return 0;
    int y = x;
    int brojac = 0;
    //int min = 4;
    if(x <=3)return x;
    while(y!=0){
        y = y - int(sqrt(y)) * int(sqrt(y));
        brojac++;
    }
    
    if(brojac <= 2)return brojac;
    y = x;
    int ip = 0, jp = 0;
    int korijen = int(sqrt(y));
    for(int i = 1; i <= korijen; i++){
        ip = i*i;
        for(int j = 1; j <= korijen; j++){
            jp = j*j;
            for(int k = 1; k <= korijen; k++){
                if(ip + jp + k*k == x){
                    return 3;
                }
            }
        }
    }
    return 4;
}

std::array<std::vector<int>, 5> RazvrstajPoBrojuKvadrata(std::vector<int> v ,TretmanNegativnih en){
    std::array<std::vector<int>, 5> niz;
    int a = -1;
    for(int i = 0; i < v.size(); i++){
        a = -1;
        if(en  == TretmanNegativnih::IgnorirajZnak  && v.at(i) < 0){
            a = BrojKvadrata(abs(v.at(i)));
            niz.at(a).push_back(v.at(i));
            continue;
            //v.at(i) = abs(v.at(i));
        }else if (en == TretmanNegativnih::Odbaci && v.at(i) < 0){
            continue;
        }else if (en == TretmanNegativnih::TretirajKao0  && v.at(i) < 0){
            niz.at(0).push_back(v.at(i));
            continue;
        }else if (en == TretmanNegativnih::PrijaviGresku  && v.at(i) < 0){
            throw std::domain_error("Nije predvidjeno razvrstavanje negativnih brojeva");
        }
       // niz.at(a).push_back(v.at(i));

        if(a == 0 || BrojKvadrata(v.at(i)) == 0 ){
            niz.at(0).push_back(v.at(i));
        }else if(a == 1 || BrojKvadrata(v.at(i)) == 1){
            niz.at(1).push_back(v.at(i));
        }else if(a == 2 || BrojKvadrata(v.at(i)) == 2){
            niz.at(2).push_back(v.at(i));
        }else if(a == 3 || BrojKvadrata(v.at(i)) == 3){
            niz.at(3).push_back(v.at(i));
        }else if(a == 4 || BrojKvadrata(v.at(i)) == 4){
            niz.at(4).push_back(v.at(i));
        }
    }

    return niz;

}

int main ()
{
    std:: vector<int> v;
    int x = 0;
    std:: cout<< "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
    while(1){
        //std:: cin >> x;
        if(!(std::cin>> x) || (std::cin.peek()!=' ' && std::cin.peek()!='\n'))break;
        if(x < 0){
            std:: cout << "Nije podrzano razvrstavanje negativnih brojeva!";
            return 0;
        }
        v.push_back(x);
    }
    std:: cout<< "Rezultati razvrstavanja po broju kvadrata: " <<std::endl;
    std::array<std::vector<int>, 5> rezultat = RazvrstajPoBrojuKvadrata(v, TretmanNegativnih::PrijaviGresku);
    for(int i = 0; i < 5; i++){
        if(rezultat.at(i).size() == 0)continue;
        std:: cout << i <<": ";
        for(int j = 0; j < rezultat.at(i).size();j++){
            std:: cout << rezultat.at(i).at(j) << " ";
        }
        std:: cout <<std::endl;
    }
	return 0;
}