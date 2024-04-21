#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <numeric>

class Rational {
 public:
  // Конструкторы
  Rational() : numerator_(0), denominator_(1) {}
  Rational(int numerator, int denominator)
      : numerator_(numerator), denominator_(denominator) {
    simplify();
  }
  Rational(int numerator) : numerator_(numerator), denominator_(1) {}

  // Геттеры
  int numerator() const { return numerator_; }
  int denominator() const { return denominator_; }

  // Сеттеры
  void setNumerator(int numerator) {
    numerator_ = numerator;
    simplify();
  }
  void setDenominator(int denominator) {
    denominator_ = denominator;
    simplify();
  }

  // Арифметические операции
  Rational operator+(const Rational& other) const;
  Rational operator-(const Rational& other) const;
  Rational operator*(const Rational& other) const;
  Rational operator/(const Rational& other) const;

  // Сравнение
  bool operator==(const Rational& other) const;
  bool operator!=(const Rational& other) const;
  bool operator<(const Rational& other) const;
  bool operator<=(const Rational& other) const;
  bool operator>(const Rational& other) const;
  bool operator>=(const Rational& other) const;

  // Ввод и вывод
  friend std::istream& operator>>(std::istream& in, Rational& rational);
  friend std::ostream& operator<<(std::ostream& out, const Rational& rational);

 private:
  int numerator_;
  int denominator_;

  // Упрощение дроби
  void simplify();
};

#endif  // RATIONAL_H