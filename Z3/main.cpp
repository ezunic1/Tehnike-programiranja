// TP 2023/2024: Zadaća 3, Zadatak 3
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <new>
#include <stdexcept>
#include <vector>


enum Smjer { Desno, Dolje, Dijagonalno };

template <typename TipElemenata> struct Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipElemenata **elementi = nullptr; 
};
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.br_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.br_redova = br_redova;
  mat.br_kolona = br_kolona;
  mat.ime_matrice = ime;
  mat.elementi = new TipElemenata *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      mat.elementi[i] = new TipElemenata[br_kolona];
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      //std::cout << mat.ime_matrice << "M(" << i + 1 << "," << j + 1 << ") = " << std::endl;
    mat.elementi[i][j] = 0;
    }
  
  return mat;
}

template <typename TipElemenata> void UnesiMatricu(Matrica<TipElemenata> &mat) {
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << mat.ime_matrice << "M(" << i + 1 << "," << j + 1 << ") = " << std::endl;
      std::cin >> mat.elementi[i][j];
    }
}
template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> mat, int sirina_ispisa=4, int sirina = 4, bool treba_brisati = false) {
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++)
      std::cout << std::setw(sirina_ispisa)<< std::setprecision(sirina) << mat.elementi[i][j];
    std::cout << std::endl;
  }
  if(treba_brisati){
    UnistiMatricu(mat);
  }
}

template <typename TipElemenata>
 Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
 const Matrica<TipElemenata> &m2) {
 if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
 throw std::domain_error("Matrice nemaju jednake dimenzije!");
 auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
 for(int i = 0; i < m1.br_redova; i++)
 for(int j = 0; j < m1.br_kolona; j++)
 m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
 return m3;
 }

Matrica<int> ProsiriPremaFunkcijama (Matrica<int> m, std::map<Smjer, std::function<int(int)>>mapa, int n){
    //auto p = m;
    if(n == 1 || mapa.size() == 0){
        auto p = StvoriMatricu<int>(m.br_redova, m.br_kolona);
        for(int i = 0; i < m.br_redova; i++){
            for(int j = 0; j < m.br_kolona; j++){
                p.elementi[i][j] = m.elementi[i][j];
            }
        }
        return p;
    }
    
    //UnistiMatricu(p);
    if(n < 1)throw std::domain_error("Besmislen parametar");
    bool a = false,b = false,c = false;
    if(mapa.find(Desno) != mapa.end()) a = true;
    if(mapa.find(Dolje) != mapa.end()) b = true;
    if(mapa.find(Dijagonalno) != mapa.end()) c = true;
    std::vector<Matrica<int>>vektor(n);
    vektor.at(0) = m;
    for(int i = 1; i < n; i++){
        if((a && b && c) || (a && b) || (a && c) || (b && c)  || c){
            vektor.at(i) = StvoriMatricu<int>(vektor.at(i-1).br_redova * 2, vektor.at(i-1).br_kolona * 2);
            for(int j = 0; j < vektor.at(i).br_redova; j++){
                for(int k  = 0; k < vektor.at(i).br_kolona; k++){
                    if(j >=vektor.at(i-1).br_redova && k >= vektor.at(i-1).br_kolona){
                        if(c){
                            vektor.at(i).elementi[j][k] = mapa[Smjer::Dijagonalno](vektor.at(i-1).elementi[j - vektor.at(i-1).br_redova][k - vektor.at(i-1).br_kolona]);
                        }else{
                            vektor.at(i).elementi[j][k] = vektor.at(i-1).elementi[j - vektor.at(i-1).br_redova][k - vektor.at(i-1).br_kolona];
                        }
                    }else if(j < vektor.at(i-1).br_redova && k >= vektor.at(i-1).br_kolona){
                        if(a){
                            vektor.at(i).elementi[j][k] = mapa[Smjer::Desno](vektor.at(i-1).elementi[j][k - vektor.at(i-1).br_kolona]);
                        }else{
                            vektor.at(i).elementi[j][k] = vektor.at(i-1).elementi[j][k - vektor.at(i-1).br_kolona];
                        }
                    }else if(j >= vektor.at(i-1).br_redova && k < vektor.at(i-1).br_kolona){
                        if(b){
                            vektor.at(i).elementi[j][k] = mapa[Smjer::Dolje](vektor.at(i-1).elementi[j - vektor.at(i-1).br_redova][k]);
                        }else {
                            vektor.at(i).elementi[j][k] = vektor.at(i-1).elementi[j - vektor.at(i-1).br_redova][k];
                        }
                    }else{
                            vektor.at(i).elementi[j][k] = vektor.at(i-1).elementi[j][k];
                        }
                }
            }
        }else if((a && !b && !c) || (b && !a && !c)){
            if(a){
                vektor.at(i) = StvoriMatricu<int>(vektor.at(i-1).br_redova, vektor.at(i-1).br_kolona * 2);
                for(int j = 0; j < vektor.at(i).br_redova; j++){
                    for(int k = 0; k < vektor.at(i).br_kolona; k++){
                        if(k >=vektor.at(i-1).br_kolona){
                            vektor.at(i).elementi[j][k] = mapa[Smjer::Desno](vektor.at(i-1).elementi[j][k-vektor.at(i-1).br_kolona]);
                        }else{
                            vektor.at(i).elementi[j][k] = vektor.at(i-1).elementi[j][k];
                        }
                    }
                }
            }else if(b){
                vektor.at(i) = StvoriMatricu<int>(vektor.at(i-1).br_redova * 2, vektor.at(i-1).br_kolona);
                for(int j = 0; j < vektor.at(i).br_redova; j++){
                    for(int k = 0; k < vektor.at(i).br_kolona; k++){
                        if(j >=vektor.at(i-1).br_redova){
                            vektor.at(i).elementi[j][k] = mapa[Smjer::Dolje](vektor.at(i-1).elementi[j - vektor.at(i-1).br_redova][k]);
                        }else{
                            vektor.at(i).elementi[j][k] = vektor.at(i-1).elementi[j][k];
                        }
                    }
                }
            }
        }
        if(i > 1) UnistiMatricu(vektor.at(i-1));
    }
    /*for(int i = 0; i < n-1; i++){
        UnistiMatricu(vektor.at(i));
    }*/
   /* auto mat = vektor.at(n-1);
    for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++)
      std::cout << std::setw(4) << mat.elementi[i][j];
    std::cout << std::endl;
  }*/
    return vektor.at(n-1);
}

int main() { 
  /*std::map<Smjer, std::function<int(int)>> m{
      {Smjer::Desno, [](int x) { return x + 1; }},
      {Smjer::Dolje, [](int x) { return x + 2; }},
     {Smjer::Dijagonalno, [](int x) { return x + 3; }}
     };

    Matrica<int> A  = StvoriMatricu<int>(2, 1);
    A.elementi[0][0] = 1;
    A.elementi[1][0] = 3;
    auto mat = ProsiriPremaFunkcijama(A, m, 3);
    IspisiMatricu(mat, 4);*/
    /*std::cout << "Unesite dimenzije kvadratne matrice: ";
    int n;
    std::cin >> n;
    Matrica<int> A = StvoriMatricu<int>(n, n);*/
    std::map<Smjer, std::function<int(int)>> mapa{
      {Smjer::Desno, [](int x) { return x + 1; }},
      {Smjer::Dolje, [](int x) { return x + 2; }},
     {Smjer::Dijagonalno, [](int x) { return x + 3; }}
     };
    std::cout << "Unesi broj redova i kolona matrice: ";
    Matrica<int> a;
    int m, n;
    std::cin >> m >> n;
    a = StvoriMatricu<int>(m, n);
    UnesiMatricu(a);
    std::cout << "Unesite n: ";
    std::cin >> n;
    auto b = ProsiriPremaFunkcijama(a, mapa, n);
    IspisiMatricu(b);
    UnistiMatricu(b);
    UnistiMatricu(a);


  return 0;
}
