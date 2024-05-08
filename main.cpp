// Your main.cpp content here

#include <iostream>
#include <random>

#include "../include/Matrix.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);

int generateRandomNumber(int min, int max) {
  // Создание генератора случайных чисел с использованием std::mt19937
  static std::mt19937 gen(std::random_device{}());

  // Создание распределения для генерации случайных чисел в заданном диапазоне
  std::uniform_int_distribution<int> distribution(min, max);

  // Генерация случайного числа в заданном диапазоне и его возврат
  return distribution(gen);
}

int main() {
  std::cout << std::setprecision(2);
  // Rational a(1, 2), b(3, 4);

  // std::cout << "Enter the first rational number (numerator/denominator):
  // "; std::cin >> a; std::cout << "Enter the second rational number
  // (numerator/denominator):"; std::cin >> b;

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
  const std::vector<std::vector<double>> data = {{1, 1}, {1, 1}};
  const std::vector<std::vector<double>> data3 = {
      {1, 2, 3}, {2, 4, 6}, {3, 6, 9}, {0, 0, 0}};
  const std::vector<std::vector<double>> data5 = {
      {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const std::vector<std::vector<double>> data0 = {{1, 2}, {3, 4}};
  const std::vector<std::vector<int>> data6 = {
      {2, 1, 3}, {0, -1, 4}, {-2, 3, 1}};
  Matrix<3, 3> m5(data5);
  Matrix<3, 3> m6(data6);
  Matrix<2, 2> m0(data0);
  Matrix<4, 3> m(data3);
  SquareMatrix<3> m2302;
  std::cout << "Square matrix: " << std::endl;
  std::cout << m2302;
  std::cout << "Square matrix det: " << m2302.det() << std::endl;
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

  // SquareMatrix<3> sm;
  // std::cout << "Square matrix: " << std::endl;
  // std::cout << sm << std::endl;
  // SquareMatrix<3> sm2;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m6(i, j) = generateRandomNumber(0, 9);
    }
  }

  // std::cout << "Square matrix 2: " << std::endl;
  // std::cout << sm2 << std::endl;
  // sm *= sm2;
  // std::cout << "Square matrix * Square matrix 2: " << std::endl;
  // std::cout << sm << std::endl;
  // std::cout << sm.trace() << std::endl;
  // std::cout << "Determinant: " << sm2.GaussDet() << std::endl;
  // std::cout << "Square matrix 5: " << std::endl;
  // std::cout << m5 << std::endl;
  // std::cout << "m5^2" << std::endl;
  // std::cout << m5 * m6 << std::endl;
  // std::cout << "m5^2" << std::endl;
  // std::cout << m5 << std::endl;
  // std::cout << "m6 trace: " << m6.trace() << std::endl;
  std::cout << "Matrix 6: " << std::endl;
  std::cout << m6 << std::endl;
  std::cout << std::endl;
  // m6.makeUpperTriangular();
  // std::cout << m6 << std::endl;
  std::cout << "matrix 6 det: " << m6.det() << std::endl;
  std::cout << std::endl;

  std::cout << "Inverted matrix: " << std::endl;
  std::cout << m6.inverted() << std::endl;

  m6.invert();
  std::cout << "Matrix 6:" << std::endl;
  std::cout << m6 << std::endl;

  std::cout << "Transposed matrix: " << std::endl;
  std::cout << m.transposed() << std::endl;
  std::cout << "Matrix: " << std::endl;
  std::cout << m << std::endl;

  std::cout << "Row with index 2: " << m.getRow(2) << std::endl;
  std::cout << "Column with index 1: " << m.getColumn(1) << std::endl;

  std::cout << "Rank: " << m.rank() << std::endl;

  std::vector<std::vector<double>> data2 = {{1, 2, 3}, {4, 5, 6}};
  std::vector<std::vector<double>> data4 = {{4, 5}, {6, 7}, {8, 9}};
  Matrix<2, 3> m2(data2);
  Matrix<3, 2> m4(data4);
  std::cout << "Matrix 2: " << std::endl;
  std::cout << m2 << std::endl;
  std::cout << "Matrix 4: " << std::endl;
  std::cout << m4 << std::endl;
  std::cout << "Matrix 2 * Matrix 4: " << std::endl;
  std::cout << m2 * m4 << std::endl;

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