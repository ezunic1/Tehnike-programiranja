//TP 2023/2024: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <exception>

std::string ViginereSifriranje(std::string poruka1, std::string kljuc){
    if(kljuc.size() == 0){
        throw std::domain_error("Neispravan kljuc");
    }
    std::string poruka = poruka1;
    int i = 0;
    while(true){
        if(i == kljuc.length())break;
        if(kljuc.at(i) < 'A' || kljuc.at(i) > 'Z'){
            throw std::domain_error("Neispravan kljuc");
        }
        i++;
    }
    int brojac = 0;
    for(int i = 0; i < poruka.length(); i++){
        //std::cout << kljuc.at(i) << " ";
        if(poruka.at(i) >= 'A' && poruka.at(i) <= 'Z'){
            poruka.at(i) = poruka.at(i) + kljuc.at(brojac) - 'A';
            if(poruka.at(i) > 'Z'){
                poruka.at(i)-=26;
            }
            brojac++;
        }else if(poruka.at(i) >= 'a' && poruka.at(i) <= 'z'){
            poruka.at(i) = poruka.at(i) + kljuc.at(brojac) - 'A';
            if(!(poruka.at(i) >= 'a' && poruka.at(i) <= 'z')){
                poruka.at(i)-=26;
            }
            brojac++;
        }
        if(brojac == kljuc.length())brojac = 0;
    }
    return poruka;
}

std::string ViginereDesifriranje(std::string poruka1, std::string kljuc){
    if(kljuc.size() == 0){
        throw std::domain_error ("Neispravan kljuc");
    }
    std::string poruka = poruka1;
    int i = 0;
    while(true){
        if(i == kljuc.length())break;
        if(kljuc.at(i) < 'A' || kljuc.at(i) > 'Z'){
            throw std::domain_error("Neispravan kljuc");
        }
        i++;
    }
    int brojac = 0;

    for(int i = 0; i < poruka.length(); i++){

        if(poruka.at(i) >= 'A' && poruka.at(i) <= 'Z'){
            poruka.at(i) = poruka.at(i) - kljuc.at(brojac) + 'A';
            if(poruka.at(i) < 'A'){
                poruka.at(i)+=26;
            }
            brojac++;
        }else if(poruka.at(i) >= 'a' && poruka.at(i) <= 'z'){
            poruka.at(i) = poruka.at(i) - kljuc.at(brojac) + 'A';
            if(!(poruka.at(i) >= 'a' && poruka.at(i) <= 'z')){
                poruka.at(i)+=26;
            }
            brojac++;
        }
        if(brojac == kljuc.length())brojac = 0;
    }
    return poruka;
}

int main ()
{
   std::string poruka;
    std::string kljuc;
    std::string pom;
    std::string pom2;
    std::string kljuc2;
    int i = 0;
    while(1){
        std::cout <<"Unesite kljuc: ";
        std::getline(std::cin, kljuc);
        i = 0;
        while(true){       
        if(kljuc.size() == 0 || kljuc.at(i) < 'A' || kljuc.at(i) > 'Z' ){
            std::cout << "Neispravan kljuc, ponovite unos: " << std::endl;
            //i  = 5;
            break;
        }
        
        i++;
        if(i == kljuc.length())break; 
        }
        if(i == kljuc.length() && i != 0){
            std::cout <<"Kljuc prihvacen. Unesite poruku: ";
            std::getline(std::cin, poruka);
            std::cout << "Sifrirana poruka: " << ViginereSifriranje(poruka,kljuc)<< std::endl;
            pom = ViginereSifriranje(poruka,kljuc);
            pom2 = poruka;
            while(1){
                std::cout <<"Pokusajte pogoditi kljuc: ";
                std::getline(std::cin, kljuc2);
                i = 0;
            while(true){
                
                if(kljuc2.size() == 0 || kljuc2.at(i) < 'A' || kljuc2.at(i) > 'Z'){
                    std::cout << "Niste pogodili kljuc, probajte ponovo!" << std::endl;
                    break;
                }
                i++;
                if(i == kljuc2.length())break;
            }
            if(i == kljuc2.length() && i!=0){
                poruka = ViginereDesifriranje(pom, kljuc2);
                std::cout << "Pokusaj desifriranja: " << poruka<<std::endl;
                if(kljuc == kljuc2){
                    std::cout << "Bravo, pogodili ste kljuc!";
                    return 0;
                }else{
                    std::cout << "Niste pogodili kljuc, probajte ponovo!" << std::endl;
                }
            }
            }
        }
    }
	return 0;
}