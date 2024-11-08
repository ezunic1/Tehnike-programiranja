// TP 2023/2024: Zadaća 3, Zadatak 4
#include <cmath>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

std::vector<int> Razbrajanje(int n, int m) {
  std::vector<int> izlazni;
  int brojac = m;
  std::list<int> lista;
  for (int i = 0; i < n; i++) {
    lista.push_back(i + 1);
  }
  brojac = 1;
  auto it = std::begin(lista);
  izlazni.push_back(*it);
  it = lista.erase(it);
  while (true) {
    it = std::begin(lista);
    while (it != std::end(lista)) {
      if (brojac == m) {
        izlazni.push_back(*it);
        brojac = 0;
        it = lista.erase(it);
        it--;
      }
      it++;
      brojac++;
    }
    if (izlazni.size() == n)
      break;
  }
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

  /*auto vektor = Razbrajanje(10,2);
  for(int i = 0; i < vektor.size(); i++){
      std::cout << vektor.at(i) << " ";
  }
  std::cout << std::endl;*/

  // std::cout << OdabirKoraka(10,3);
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
