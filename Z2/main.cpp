// TP 2023/2024: Zadaća 1, Zadatak 2
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

typedef std::vector<std::vector<double>> matrica;

double medijan(std::vector<double> &v) {
  double pom = 0;
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (v.at(j) < v.at(i)) {
        pom = v.at(j);
        v.at(j) = v.at(i);
        v.at(i) = pom;
        i = 0;
      }
    }
  }
  if (v.size() % 2 == 1) {
    pom = v.at(v.size() / 2);
  } else {
    pom = v.at(v.size() / 2) + v.at(v.size() / 2 - 1);
    pom /= 2.;
  }
  return pom;
}


matrica MedijanskiFilter(matrica a, int N) {
  if (N < 0)
    throw std::domain_error("Neispravan red filtriranja");
  if (N == 0)
    return a;

  int max = 0;
  for (int i = 0; i < a.size(); i++) {
    if (a.at(i).size() > max) {
      max = a.at(i).size();
    }
  }
  for (int i = 0; i < a.size(); i++) {
    for (int j = a.at(i).size(); j < max; j++) {
      a.at(i).push_back(-333);
    }
  }
  std::vector<double> pom;
  matrica b(a.size());

  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < max; j++) {
      pom = {};

      if (a.at(i).at(j) == -333)
        continue;

      for (int k = i - N; k <= i + N; k++) {
        if (k < 0)
          continue;
        if (k > a.size() - 1)
          continue;

        for (int h = j - N; h <= j + N; h++) {
          if (h < 0)
            continue;
          if (h > max - 1)
            continue;
          if (a.at(k).at(h) == -333)
            continue;
          pom.push_back(a.at(k).at(h));
        }
      }
      b.at(i).push_back(medijan(pom));

    }
  } 
  return b;
}

int main() {
  int a = 0, b = 0;
  std::cout << "Unesite broj redova i kolona matrice: ";
  std::cin >> a >> b;
  std::cout << "Unesite elemente matrice: ";
  matrica slika(a,std::vector<double>(b));
  double pom = 0;
  for (int i = 0; i < a; i++) {
    //slika.resize(slika.size() + 1);
    for (int j = 0; j < b; j++) {
      std::cin >> pom;
      slika.at(i).at(j) = pom;
    }
  }
  int N = 0;
  std::cout << "Unesite red filtriranja: ";
  std::cin >> N;
  if(N < 0){
      std::cout << "GRESKA: Neispravan red filtriranja!";
      return 0;
  }
  matrica filtrirana = MedijanskiFilter(slika, N);
  std::cout << "Matrica nakon filtriranja: " << std::endl;

  for(int i = 0; i < filtrirana.size(); i++){
        for(int j = 0; j < filtrirana.at(i).size(); j++){
            std::cout <<std::setw(7) <<std::fixed <<std::setprecision(2)<<filtrirana.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
  return 0;
}
