// TP 2023/2024: Zadaća 1, Zadatak 3
#include <cmath>
#include <exception>
#include <iostream>
#include <limits>
#include <climits>
#include <stdexcept>
#include <string>
#include <vector>


long long int fun(std::string a) {

  long long int pom = 0;
  long long int cifra = 0;
  bool negativan = false;

  if (a.at(0) == '-')
    negativan = true;

  for (int i = a.size()-1; i >= 0; i--) {
    if (a.at(i) == '-')
      continue;
    //std::cout << a.at(i) << " ....." << std::endl;
    cifra = a.at(i) - '0';
     //std::cout <<   cifra  << " +++++" << std::endl;
    if(pom > std::numeric_limits<long long int>::max() - static_cast<long long int>(cifra * pow(10,a.size()-1 -i)))throw std::range_error("Prevelik broj");
    pom += cifra * (long long int)pow(10, a.size()-1 -i);
    //std::cout << pom<< std::endl;
  }
 // std::cout << std::endl;
  if(negativan)pom*=-1;
  return pom;
}

std::vector<long long int> BrojeviUStringu(std::string brojevi) {
  std::vector<long long int> v;
  std::vector<std::string> matrica;
  int brojac = 0;
  std::string pom;

  for (int i = 0; i < brojevi.length(); i++) {
    // std::cout << brojevi.at(i) <<" ";
    if (brojevi.at(i) >= '0' && brojevi.at(i) <= '9') {
      pom = "";
      while (1) {
        // if(i == brojevi.size())break;
        if (brojevi.at(i) >= '0' && brojevi.at(i) <= '9') {
          // std::cout << brojevi.at(i) << " " << i << std::endl;
          pom += brojevi.at(i);
        } else if ((brojevi.at(i) >= 'A' && brojevi.at(i) <= 'Z') ||
                   (brojevi.at(i) >= 'a' && brojevi.at(i) <= 'z')) {
          break;
        } else if (!((brojevi.at(i) >= 'A' && brojevi.at(i) <= 'Z') ||
                     (brojevi.at(i) >= 'a' && brojevi.at(i) <= 'z') ||
                     (brojevi.at(i) >= '0' && brojevi.at(i) <= '9'))) {
          matrica.push_back(pom);
          brojac++;
          i--;
          break;
        }

        if (i == brojevi.size() && pom.size() == 0)
          break;
        if (i == brojevi.size() - 1 && pom.size() > 0) {
          matrica.push_back(pom);
          brojac++;
          break;
        }
        i++;
      }
    } else if (brojevi.at(i) == '-') {
      pom = "-";
      i++;
      if (brojevi.at(i) >= '0' && brojevi.at(i) <= '9') {
        // pom = "";
        while (1) {
          // if(i == brojevi.size())break;
          if (brojevi.at(i) >= '0' && brojevi.at(i) <= '9') {
            // std::cout << brojevi.at(i) << " " << i << std::endl;
            pom += brojevi.at(i);
          } else if ((brojevi.at(i) >= 'A' && brojevi.at(i) <= 'Z') ||
                     (brojevi.at(i) >= 'a' && brojevi.at(i) <= 'z')) {
            i++;
            break;
          } else if (!((brojevi.at(i) >= 'A' && brojevi.at(i) <= 'Z') ||
                       (brojevi.at(i) >= 'a' && brojevi.at(i) <= 'z') ||
                       (brojevi.at(i) >= '0' && brojevi.at(i) <= '9'))) {
            matrica.push_back(pom);
            brojac++;
            break;
          }
          if (i == brojevi.size() && pom.size() == 0)
            break;
          if (i == brojevi.size() - 1 && pom.size() > 0) {
            matrica.resize(matrica.size() + 1);
            matrica.at(brojac) = pom;
            brojac++;
            break;
          }
          i++;
        }
      }
    }
  }

  long long int k = 0;
  for (int i = 0; i < matrica.size(); i++) {
    //std::cout << matrica.at(i) << std::endl;
    v.push_back(fun(matrica.at(i)));
  }
  return v;
}

int main() {
    //std::cout << std::numeric_limits<long long int>::min() << std::endl;

    /*auto v = BrojeviUStringu("Najveci broj je 9223372036854775807, a najmanji -9223372036854775808");
    for(int i = 0; i < v.size(); i++){
        std::cout << v.at(i) << " ";
    }*/


    //std::cout << std::numeric_limits<long long int>::max();
  try{
  std::string Brojevi;
  std::cout << "Unesite string: ";
  std::getline(std::cin, Brojevi);
  std::vector<long long int> v = BrojeviUStringu(Brojevi);
  if(v.size() == 0){
      std::cout << "Uneseni string ne sadrzi nijedan broj!";
      return 0;
  } 
  std::cout <<"Brojevi unutar stringa: ";
  for (int i = 0; i < v.size(); i++) {
    std::cout << v.at(i) << " ";
  }
  }catch(std::range_error){
      std::cout << "PROBLEM: Uneseni string sadrzi prevelik broj!!!";
  }
  
  return 0;
}
