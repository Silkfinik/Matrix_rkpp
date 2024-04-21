// Your main.cpp content here

#include <iostream>

#include "../include/Matrix.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);

int main() {
  Rational a(1, 2), b(3, 4);

  // std::cout << "Enter the first rational number (numerator/denominator): ";
  // std::cin >> a;
  // std::cout << "Enter the second rational number (numerator/denominator):";
  // std::cin >> b;

  // std::cout << "First rational number: " << a << std::endl;
  // std::cout << "Second rational number: " << b << std::endl;

  // Rational sum = a + b;
  // Rational difference = a - b;
  // Rational product = a * b;
  // Rational quotient = a / b;

  // std::cout << "Sum: " << sum << std::endl;
  // std::cout << "Difference: " << difference << std::endl;
  // std::cout << "Product: " << product << std::endl;
  // std::cout << "Quotient: " << quotient << std::endl;

  // if (a == b) {
  //   std::cout << "The two rational numbers are equal." << std::endl;
  // } else {
  //   std::cout << "The two rational numbers are not equal." << std::endl;
  // }

  // std::cout << "a: " << a << std::endl;
  // std::cout << "b: " << b << std::endl;
  const std::vector<std::vector<int>> data = {{1, 1}, {1, 1}};
  const std::vector<std::vector<int>> data3 = {
      {1, 2, 3}, {2, 4, 6}, {3, 6, 9}, {0, 0, 0}};
  Matrix<4, 3> m(data3);
  // Matrix<3, 3> m2(data);
  // Matrix<2, 3> m3(data3);

  // m -= m2;

  std::cout << "Matrix: " << std::endl;
  std::cout << m << std::endl;

  // std::cin >> m;
  // std::cout << m << std::endl;

  // m = m * 2;

  // std::cout << "m(0, 0): " << m(0, 0) << std::endl;
  // m(0, 0) = 10;
  // std::cout << "m(0, 0): " << m(0, 0) << std::endl;

  SquareMartix<2> sm;
  std::cout << "Square matrix: " << std::endl;
  std::cout << sm << std::endl;

  std::cout << "Transposed matrix: " << std::endl;
  std::cout << m.transposed() << std::endl;
  std::cout << "Matrix: " << std::endl;
  std::cout << m << std::endl;

  std::cout << "Row with index 2: " << m.getRow(2) << std::endl;
  std::cout << "Column with index 1: " << m.getColumn(1) << std::endl;

  std::cout << "Rank: " << m.rank() << std::endl;

  return 0;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  os << "[ ";
  for (const auto& element : vec) {
    os << element << " ";
  }
  os << "]";
  return os;
}