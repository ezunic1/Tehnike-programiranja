// TP 2023/2024: Zadaća 5, Zadatak 1
#include <cmath>
#include <iostream>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>

class Razlomak {
  long long int br;
  long long int na;
  static long long int NZD(long long int a, long long int b) {
    if (b == 0)
      return a;
    return NZD(b, a % b);
  }
  static long long int provjeriM(long long int a, long long int b) {
    if (a > 0 && b > 0 && b > (std::numeric_limits<long long int>::max() / a))
      throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    if (a > 0 && b < 0 && b < (std::numeric_limits<long long int>::min() / a))
      throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    if (b > 0 && a < 0 && a < (std::numeric_limits<long long int>::min() / b))
      throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    if (a < 0 && b < 0 && b < (std::numeric_limits<long long int>::max() / a))
      throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    return a * b;
  }
  static long long int provjeriS(long long int a, long long int b) {
    if (a > 0 && b > 0 && b > (std::numeric_limits<long long int>::max() - a))
      throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    if (a < 0 && b < 0 && b < (std::numeric_limits<long long int>::min() - a))
      throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    return a + b;
  }

public:
  Razlomak(long long int a, long long int b);
  Razlomak(long long int a) : br(a), na(1) {}
  Razlomak() : br(0), na(1) {}
  long long int DajBrojnik() const { return br; }
  long long int DajNazivnik() const { return na; }
  void ispisi() { std::cout << br << "/" << na << std::endl; }
  friend Razlomak operator+(const Razlomak &r1, const Razlomak &r2) {
    long long int r = NZD(r1.na, r2.na);
    long long int p1 = provjeriM(r1.br, r2.na / r);
    long long int p2 = provjeriM(r2.br, r1.na / r);
    long long int q1 = provjeriM(r1.na, r2.na / r);
    long long int pom = provjeriS(p1, p2);
    return {pom, q1};
  }
  friend Razlomak operator-(const Razlomak &r1, const Razlomak &r2) {
    long long int r = NZD(r1.na, r2.na);
    long long int p1 = provjeriM(r1.br, r2.na / r);
    long long int p2 = provjeriM(r2.br, r1.na / r);
    long long int q1 = provjeriM(r1.na, r2.na / r);
    long long int pom = provjeriS(p1, -p2);
    return {pom, q1};
  }
  friend Razlomak operator*(const Razlomak &r1, const Razlomak &r2) {
    long long int s = NZD(r1.br, r2.na);
    long long int t = NZD(r2.br, r1.na);
    long long int p1p2 = provjeriM(r1.br / s, r2.br / t);
    long long int q1q2 = provjeriM(r1.na / s, r2.na / t);
    return {p1p2, q1q2};
  }
  friend Razlomak operator/(const Razlomak &r1, const Razlomak &r2) {
    long long int r = NZD(r1.na, r2.na);
    long long int u = NZD(r1.br, r2.br);
    long long int p1q2 = provjeriM(r1.br / u, r2.na / r);
    long long int p2q1 = provjeriM(r1.na / r, r2.br / u);
    return {p1q2, p2q1};
    // return {p1p2,q1q2};
  }
  Razlomak &operator+=(const Razlomak &r) {
    *this = *this + r;
    return *this;
  }
  Razlomak &operator-=(const Razlomak &r) {
    *this = *this - r;
    return *this;
  }
  Razlomak &operator*=(const Razlomak &r) {
    *this = *this * r;
    return *this;
  }
  Razlomak &operator/=(const Razlomak &r) {
    *this = *this / r;
    return *this;
  }
  Razlomak operator-() const { return Razlomak(-br, na); }
  Razlomak operator+() const { return *this; }
  Razlomak &operator++() {
    *this += 1;
    return *this;
  }
  Razlomak operator++(int) {
    auto pom = *this;
    ++(*this);
    return pom;
  }
  Razlomak &operator--() {
    *this -= 1;
    if (na < 0) {
      br *= -1;
      na *= -1;
    }
    return *this;
  }
  Razlomak operator--(int) {
    auto pom = *this;
    --(*this);
    return pom;
  }
  operator long double() const { return static_cast<long double>(br) / na; }
  friend bool operator<(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1) < static_cast<long double>(r2);
  }
  friend bool operator>(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1) > static_cast<long double>(r2);
  }
  friend bool operator<=(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1) <= static_cast<long double>(r2);
  }
  friend bool operator>=(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1) >= static_cast<long double>(r2);
  }
  friend bool operator==(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1) == static_cast<long double>(r2);
  }
  friend bool operator!=(const Razlomak &r1, const Razlomak &r2) {
    return static_cast<long double>(r1) != static_cast<long double>(r2);
  }
  friend std::ostream &operator<<(std::ostream &tok, const Razlomak &r) {
    tok << r.br;
    if (r.na != 1)
      tok << "/" << r.na;
    return tok;
  }
  friend std::istream &operator>>(std::istream &tok, Razlomak &r) {
    long long int b, n = 1;
    char znak;
    tok >> std::ws;

    if (tok.peek() == '-' || tok.peek() == '+')
      tok >> znak;
    tok >> b;
    if (tok.peek() == '.') {
      tok.setstate(std::ios::failbit);
      return tok;
    }
    if (tok.peek() == '/') {
      tok >> znak >> n;
      if (tok.peek() == '.') {
        tok.setstate(std::ios::failbit);
        return tok;
      }
    }

    if (tok.peek() != EOF && !std::isspace(tok.peek())) {
      tok.setstate(std::ios::failbit);
      return tok;
    }
    if (b != 0) {
      r = Razlomak(b, n);
    } else {
      tok.setstate(std::ios::failbit);
    }
    return tok;
  }
};
Razlomak::Razlomak(long long int a, long long int b) {
  if (b == 0)
    throw std::logic_error("Nekorektan razlomak");
  if (b < 0) {
    a *= -1;
    b *= -1;
  }
  br = a;
  na = b;
  long long int pom = NZD(a, b);
  if (pom != -1) {
    na /= pom;
    br /= pom;
  }
}

int main() {
  Razlomak a{110,10};
  Razlomak c{1,5};
  Razlomak b = a * c;
  a.ispisi();
  b.ispisi();
  Razlomak d;
  std::cin >> d;
  //d.ispisi();
  std::cout << d;
      return 0;
}
