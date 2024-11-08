//TP 2023/2024: Zadaća 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>


template<typename tip>
bool Kriterij(std::vector<tip> v1, std::vector<tip>v2){
    auto prvi = std::max_element(std::begin(v1), std::end(v1));
    auto drugi = std::max_element(std::begin(v2), std::end(v2));
    if(*prvi == *drugi)
        return v1 > v2;
    return *prvi > *drugi;
}
template <typename tip>
void SortirajPoDobrotiRedova(std::vector<std::vector<tip>> &v){
    std::sort(std::begin(v), std::end(v), Kriterij<tip>);
}

bool broj(char x){
    if(x>='0' && x<='9')return true;
    return false;
}
int main ()
{
    //std::vector<std::vector<int>> a ={{2, 5, 1, 6, 7}, {9, 8, 9}, {3, 3, 2, 3}, {4, 5, 1, 1, 7, 3, 2}} ;
    //std::vector<std::vector<std::string>> a = {{"Ovo je recenica.", "Ali i ovo je.", "E i ovo isto."}, {"Avo je recenica.", "Ali i ovo je.", " A i ovo isto"}};
    //std::vector<int> b = {5,3,1};
    /*SortirajPoDobrotiRedova(a);
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a.at(i).size(); j++){
            std::cout << a.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> pom = {2,5,1,6,7};
    auto pok = lower_bound(std::begin(a), std::end(a), pom, Kriterij<int>);
    if(pok!=std::end(a) && *pok == pom)
        std::cout <<"Ova sekvenca se nalazi na " << pok - std::begin(a) +1 << ". poziciji.";
    else {
        std::cout <<"Trazena sekvenca se ne nalazi u matrici";
    }*/
    
    std::vector<std::vector<int>> a;
    std::string pomocniString; 
    std::cout << "Unesite elemente (* za kraj reda, * na pocetku reda za kraj unosa): " << std::endl;
    while(true){
        std::getline(std::cin, pomocniString);
        std::string pom={};
        std::vector<int> red;
        for(char x : pomocniString){
            if(x == ' ' || !broj(x)){
                if(pom.size() != 0){
                    red.push_back(std::stoi(pom));
                    pom = {};
                }
            }else{
                pom.push_back(x);
            }
        }
        if(pom.size()!=0){
            red.push_back(std::stoi(pom));
        }
        if(red.size() == 0)break;
        a.push_back(red);
        if(!broj(pomocniString.at(0)) && pomocniString.at(0)!=' ')break;
    }
    SortirajPoDobrotiRedova(a);
    std::cout << "Matrica nakon sortiranja: " << std::endl;
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < a.at(i).size(); j++){
            std::cout << a.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Unesite elemente sekvence koja se trazi (* za kraj reda): ";
    std::vector<int> sekvenca;
    std::getline(std::cin, pomocniString);
    std::string pom;
    for(char x : pomocniString){
            if(x == ' ' || !broj(x)){
                if(pom.size() != 0){
                    sekvenca.push_back(std::stoi(pom));
                    pom = {};
                }
            }else{
                pom.push_back(x);
            }
        }
        if(pom.size()!=0){
            sekvenca.push_back(std::stoi(pom));
        }
    /*for(int x : sekvenca)
        std::cout << x << " ";*/
    auto pok = lower_bound(std::begin(a), std::end(a), sekvenca, Kriterij<int>);
    if(pok!=std::end(a) && *pok == sekvenca)
        std::cout <<"Trazena sekvenca se nalazi u " << pok - std::begin(a) +1 << ". redu (nakon sortiranja)";
    else {
        std::cout <<"Trazena sekvenca se ne nalazi u matrici";
    }

	return 0;
}
