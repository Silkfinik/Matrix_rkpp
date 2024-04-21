#include "Rational.h"

// Арифметические операции
Rational Rational::operator+(const Rational& other) const {
  int newNumerator =
      numerator_ * other.denominator_ + other.numerator_ * denominator_;
  int newDenominator = denominator_ * other.denominator_;
  return Rational(newNumerator, newDenominator);
}

Rational Rational::operator-(const Rational& other) const {
  int newNumerator =
      numerator_ * other.denominator_ - other.numerator_ * denominator_;
  int newDenominator = denominator_ * other.denominator_;
  return Rational(newNumerator, newDenominator);
}

Rational Rational::operator*(const Rational& other) const {
  int newNumerator = numerator_ * other.numerator_;
  int newDenominator = denominator_ * other.denominator_;
  return Rational(newNumerator, newDenominator);
}

Rational Rational::operator/(const Rational& other) const {
  int newNumerator = numerator_ * other.denominator_;
  int newDenominator = denominator_ * other.numerator_;
  return Rational(newNumerator, newDenominator);
}

// Сравнение
bool Rational::operator==(const Rational& other) const {
  return (numerator_ == other.numerator_ && denominator_ == other.denominator_);
}

bool Rational::operator!=(const Rational& other) const {
  return !(*this == other);
}

bool Rational::operator<(const Rational& other) const {
  return (numerator_ * other.denominator_ < other.numerator_ * denominator_);
}

bool Rational::operator<=(const Rational& other) const {
  return (*this < other || *this == other);
}

bool Rational::operator>(const Rational& other) const {
  return !(*this <= other);
}

bool Rational::operator>=(const Rational& other) const {
  return !(*this < other);
}

// Ввод и вывод
std::istream& operator>>(std::istream& in, Rational& rational) {
  char delimiter;
  in >> rational.numerator_ >> delimiter >> rational.denominator_;
  rational.simplify();
  return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& rational) {
  out << rational.numerator_ << "/" << rational.denominator_;
  return out;
}

// Упрощение дроби
void Rational::simplify() {
  int gcdValue = std::gcd(numerator_, denominator_);
  numerator_ /= gcdValue;
  denominator_ /= gcdValue;
}