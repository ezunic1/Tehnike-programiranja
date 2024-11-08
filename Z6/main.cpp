//TP 2023/2024: Zadaća 5, Zadatak 6
#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>
#include <stdexcept>

template <typename TipElemenata>
 void SortirajBinarnuDatoteku(const char ime_datoteke[],
 std::function<bool(TipElemenata, TipElemenata)> kriterij
 = std::less<TipElemenata>()){
    std::fstream otvori(ime_datoteke, std::ios::binary | std::ios::in |std::ios::out);
    if(!otvori)throw std::logic_error("Datoteka ne postoji");

    otvori.seekg(0, std::ios::end);
    int size = otvori.tellg() / sizeof(TipElemenata);
    for(int i = 0; i < size - 1; i++){
        for(int j = i + 1; j < size; j++){
            TipElemenata prvi, drugi;
            otvori.seekg(i * sizeof(TipElemenata));
            otvori.read(reinterpret_cast<char *>(&prvi), sizeof(TipElemenata));
            otvori.seekg(j * sizeof(TipElemenata));
            otvori.read(reinterpret_cast<char *>(&drugi), sizeof(TipElemenata));
            if(!kriterij(prvi,drugi)){
                otvori.seekp(i * sizeof(TipElemenata));
                otvori.write(reinterpret_cast<char *>(&drugi), sizeof(TipElemenata));
                otvori.seekp(j * sizeof(TipElemenata));
                otvori.write(reinterpret_cast<char *>(&prvi), sizeof(TipElemenata));
            }
        }

    }
}


int main ()
{
	return 0;
}
