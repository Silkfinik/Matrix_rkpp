#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>

#include "Rational.h"

template <size_t M, size_t N, typename Field = int>
class Matrix {
 public:
  Matrix(const std::vector<std::vector<Field>>& data) : data_(data) {}

  //операторы сравнения
  bool operator==(const Matrix& other) const { return data_ == other.data_; }
  bool operator!=(const Matrix& other) const { return !(*this == other); }

  //умножение на скаляр
  Matrix operator*(const int& scalar) const;

  // операторы += и -=
  template <size_t M1, size_t N1>
  typename std::enable_if<(M == M1 && N == N1), Matrix<M, N, Field>&>::type
  operator+=(const Matrix<M1, N1, Field>& other);

  template <size_t M1, size_t N1>
  typename std::enable_if<(M == M1 && N == N1), Matrix<M, N, Field>&>::type
  operator-=(const Matrix<M1, N1, Field>& other);

  //оператор индексации
  Field& operator()(size_t i, size_t j) { return data_[i][j]; }
  const Field& operator()(size_t i, size_t j) const { return data_[i][j]; }

  Matrix transposed() const;
  size_t rank() const;

  //операторы ввода-вывода
  friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    size_t M1 = matrix.data_.size();
    size_t N1 = matrix.data_[0].size();
    for (size_t i = 0; i < M1; ++i) {
      for (size_t j = 0; j < N1; ++j) {
        out << matrix.data_[i][j] << ' ';
      }
      out << std::endl;
    }
    return out;
  }

  friend std::istream& operator>>(std::istream& in, Matrix& matrix) {
    std::cout << "Enter the matrix(" << M << "x" << N << ")";
    // size_t M1 = matrix.data_.size();
    // size_t N1 = matrix.data_[0].size();
    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < N; ++j) {
        in >> matrix.data_[i][j];
      }
    }
    return in;
  }

  std::vector<Field> getRow(size_t i) const { return data_[i]; }
  std::vector<Field> getColumn(size_t j) const;

  template <size_t M1, size_t N1>
  typename std::enable_if<(N == M1), Matrix<M1, N1, Field>>::type operator*(
      const Matrix<M1, N1, Field>& other) const;

 protected:
  std::vector<std::vector<Field>> data_;

  Matrix() : data_(M, std::vector<Field>(N)) {
    for (size_t i = 0; i < M; ++i) {
      data_[i][i] = 1;
    }
  }
};

//--------------------------------------------------------------------------------------

// реализация методов
template <size_t M, size_t N, typename Field>
Matrix<M, N, Field> Matrix<M, N, Field>::operator*(const int& scalar) const {
  Matrix result = *this;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      result.data_[i][j] *= scalar;
    }
  }
  return result;
}

template <size_t M, size_t N, typename Field>
template <size_t M1, size_t N1>
typename std::enable_if<(M == M1 && N == N1), Matrix<M, N, Field>&>::type
Matrix<M, N, Field>::operator+=(const Matrix<M1, N1, Field>& other) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      data_[i][j] += other(i, j);
    }
  }
  return *this;
}

template <size_t M, size_t N, typename Field>
template <size_t M1, size_t N1>
typename std::enable_if<(M == M1 && N == N1), Matrix<M, N, Field>&>::type
Matrix<M, N, Field>::operator-=(const Matrix<M1, N1, Field>& other) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      data_[i][j] -= other(i, j);
    }
  }
  return *this;
}

template <size_t M, size_t N, typename Field>
Matrix<M, N, Field> Matrix<M, N, Field>::transposed() const {
  std::vector<std::vector<Field>> transposed_data(N, std::vector<Field>(M));
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      transposed_data[j][i] = data_[i][j];
    }
  }
  return Matrix(transposed_data);
}

template <size_t M, size_t N, typename Field>
size_t Matrix<M, N, Field>::rank() const {
  // Transpose the matrix to work with row vectors
  Matrix transposed_matrix = transposed();

  std::vector<std::vector<Field>> matrix = transposed_matrix.data_;

  size_t rank = 0;
  size_t lead = 0;
  const size_t rows = matrix.size();
  const size_t cols = matrix[0].size();

  for (size_t r = 0; r < rows; ++r) {
    if (lead >= cols) break;

    size_t i = r;
    while (matrix[i][lead] == 0) {
      ++i;
      if (i == rows) {
        i = r;
        ++lead;
        if (lead == cols) break;
      }
    }

    if (lead < cols) {
      std::swap(matrix[i], matrix[r]);
      Field div = matrix[r][lead];
      for (size_t j = 0; j < cols; ++j) matrix[r][j] /= div;

      for (size_t i = 0; i < rows; ++i) {
        if (i != r) {
          Field sub = matrix[i][lead];
          for (size_t j = 0; j < cols; ++j) matrix[i][j] -= sub * matrix[r][j];
        }
      }

      ++lead;
      ++rank;
    }
  }
  return rank;
}

template <size_t M, size_t N, typename Field>
template <size_t M1, size_t N1>
typename std::enable_if<(N == M1), Matrix<M1, N1, Field>>::type
Matrix<M, N, Field>::operator*(const Matrix<M1, N1, Field>& other) const {
  // Initialize the result matrix with appropriate dimensions
  std::vector<std::vector<int>> result(M, std::vector<int>(other.N, 0));

  // Perform matrix multiplication using Strassen's algorithm
  for (size_t i = 0; i < M; ++i) {
    for (size_t k = 0; k < N; ++k) {
      for (size_t j = 0; j < other.N; ++j) {
        result[i][j] += data_[i][k] * other.data_[k][j];
      }
    }
  }

  return Matrix(result);
}

// ========================================================================

template <size_t N, typename Field = int>
class SquareMartix : public Matrix<N, N, Field> {
 public:
  SquareMartix() : Matrix<N, N, Field>() {}
};

#endif  // MATRIX_H