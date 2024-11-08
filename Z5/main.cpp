// TP 2023/2024: Zadaća 3, Zadatak 5
#include <cmath>
#include <iostream>
#include <new>
#include <vector>


struct Distrikt {
  int broj_distrikta;
  Distrikt *sljedeci;
};

std::vector<int> Razbrajanje(int n, int m) {
  std::vector<int> izlazni;
  Distrikt *pocetak{}, *prethodni{};
  std::vector<Distrikt *> dinamicki(n,nullptr);///
  try{ ///
  for (int i = 0; i < n; i++) {
    Distrikt *novi = new Distrikt{i + 1, nullptr};
    dinamicki.at(i) = novi; ///
    if (!pocetak)
      pocetak = novi;
    else
      prethodni->sljedeci = novi;
    prethodni = novi;
  }
   //// 

  prethodni->sljedeci = pocetak;
  Distrikt *p = pocetak;
  while (p->sljedeci != p) {
    izlazni.push_back(p->broj_distrikta);
    prethodni->sljedeci = p->sljedeci;
    delete p;
    p = prethodni->sljedeci;
    for (int i = 1; i < m; i++) {
      prethodni = p;
      p = p->sljedeci;
    }
    
  }
  izlazni.push_back(p->broj_distrikta);
  delete p;
  }catch(std::bad_alloc){ //// 
    for(auto p : dinamicki){
        delete p;
    }
  }///
  return izlazni;
}

int OdabirKoraka(int n, int k) {
  for (int i = 1; i <= n; i++) {
    auto vektor = Razbrajanje(n, i);
    if (vektor.at(vektor.size() - 1) == k) {
      return i;
    }
  }
  if(k > n || k < 1 || n < 1)
  throw std::domain_error(
      "Broj blokova i redni broj bloka su pozitivni cijeli brojevi i redni "
      "broj bloka ne moze biti veci od broja blokova");
  return 0;
}

int main() {
  int n, k;
  std::cout << "Unesite broj distrikta u gradu: ";
  std::cin >> n;
  std::cout << "Unesite redni broj distrikta u kojem se nalazi restoran: ";
  std::cin >> k;
  std::cout << "Trazeni korak: ";
  try {
    std::cout << OdabirKoraka(n, k);
  } catch (std::domain_error &w) {
    std::cout << w.what();
  }
  return 0;
}
