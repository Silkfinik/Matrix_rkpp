#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

template <size_t M, size_t N, typename Field = double>
class Matrix {
 public:
  //==============================================================================
  template <typename T>
  Matrix(const std::vector<std::vector<T>>& data) {
    data_.resize(data.size());
    for (int i = 0; i < data.size(); ++i) {
      data_[i].resize(data[i].size());
    }
    for (int i = 0; i < data_.size(); ++i) {
      for (int j = 0; j < data_[i].size(); ++j) {
        data_[i][j] = static_cast<double>(data[i][j]);
      }
    }
  }

  std::vector<std::vector<Field>> getData() const { return data_; }
  void setData(const std::vector<std::vector<Field>>& data) { data_ = data; }

  //операторы сравнения
  bool operator==(const Matrix& other) const { return data_ == other.data_; }
  bool operator!=(const Matrix& other) const { return !(*this == other); }

  //умножение на скаляр
  template <typename T>
  Matrix operator*(const T& scalar) const;

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
  typename std::enable_if<(N == M1), Matrix<M, N, Field>>::type operator*(
      const Matrix<M1, N1, Field>& other) const;

  // *=
  template <size_t M1, size_t N1>
  typename std::enable_if<(N == M && N1 == M1), Matrix<M, N, Field>>::type
  operator*=(const Matrix<M1, N1, Field>& other) {
    *this = *this * other;
    return *this;
  }

  // trace
  template <typename T = Field>
  typename std::enable_if<(M == N), T>::type trace() const {
    T result = 0;
    for (size_t i = 0; i < M; ++i) {
      result += data_[i][i];
    }
    return result;
  }

  // =========================================
  // Метод для вычисления определителя методом Гаусса
  template <typename T = Field>
  typename std::enable_if<(M == N), T>::type det() const {
    double result = 1.0;
    std::vector<std::vector<double>> temp_data(N, std::vector<double>(N));

    // Копируем данные из исходной матрицы во временную
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        temp_data[i][j] = static_cast<double>(this->data_[i][j]);
      }
    }

    for (size_t row = 0; row < N - 1; ++row) {
      size_t next_row = row + 1;
      if (temp_data[row][row] == 0) {
        while (next_row != N && temp_data[next_row][row] == 0) {
          ++next_row;
        }
        if (next_row == N)
          return Field(0);
        else {
          std::swap(temp_data[next_row], temp_data[row]);
          for (size_t j = 0; j < N; ++j) {
            temp_data[row][j] *= -1;  // Умножаем на -1 целую строку, чтобы
                                      // сохранить знак определителя
          }
        }
      }
      for (size_t i = next_row; i < N; ++i) {
        double factor = temp_data[i][row] / temp_data[row][row];
        for (size_t j = row; j < N; ++j) {
          double temp_value = temp_data[row][j] * factor;
          temp_data[i][j] -= temp_value;
        }
      }
    }

    for (size_t i = 0; i < N; ++i) {
      result *= temp_data[i][i];
    }

    return result;
  }
  // =========================================

  // обратная матрица
  template <typename T = double>
  typename std::enable_if<(M == N), Matrix<M, N, T>>::type inverted() const {
    Matrix<M, N, T> inverse;
    Field determinant = det();
    if (determinant == Field(0)) {
      throw std::runtime_error("Matrix is singular");
    }
    Matrix<M, N, T> adjoint = adjointMatrix();

    double temp = 1.0 / determinant;

    inverse = adjoint * temp;

    return inverse;
  }

  Matrix() : data_(M, std::vector<Field>(N)) {
    static_assert(M == N && M != 0,
                  "Matrix dimensions must be square (M == N)");
    for (size_t i = 0; i < M; ++i) {
      data_[i][i] = 1;
    }
  }

  void invert() { *this = this->inverted(); }

 protected:
  std::vector<std::vector<Field>> data_;

  // Matrix() : data_(M, std::vector<Field>(N)) {
  //   for (size_t i = 0; i < M; ++i) {
  //     data_[i][i] = 1;
  //   }
  // }

  // матрица алгебраических дополнений
  Matrix<N, N, Field> adjointMatrix() const {
    Matrix<M, N, Field> adjoint;

    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        // Создаем подматрицу без i-ой строки и j-го столбца
        Matrix<M - 1, N - 1, Field> minor;
        size_t minor_row = 0;
        size_t minor_col = 0;
        for (size_t row = 0; row < N; ++row) {
          if (row == i) continue;
          for (size_t col = 0; col < N; ++col) {
            if (col == j) continue;
            minor(minor_row, minor_col) = data_[row][col];
            ++minor_col;
          }
          ++minor_row;
          minor_col = 0;
        }

        // Вычисляем определитель подматрицы
        Field minor_det = minor.det();

        // Знак алгебраического дополнения
        Field sign = ((i + j) % 2 == 0) ? Field(1) : Field(-1);

        // Присваиваем алгебраическое дополнение элементу матрицы
        adjoint(j, i) = minor_det * sign;
      }
    }

    return adjoint;
  }

  //оператор =
  Matrix& operator=(const Matrix& other);
};

//--------------------------------------------------------------------------------------

// реализация методов
template <size_t M, size_t N, typename Field>
template <typename T>
Matrix<M, N, Field> Matrix<M, N, Field>::operator*(const T& scalar) const {
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
std::vector<Field> Matrix<M, N, Field>::getColumn(size_t j) const {
  std::vector<Field> column;
  for (size_t i = 0; i < M; ++i) {
    column.push_back(data_[i][j]);
  }
  return column;
}

template <size_t M, size_t N, typename Field>
template <size_t M1, size_t N1>
typename std::enable_if<(N == M1), Matrix<M, N, Field>>::type
Matrix<M, N, Field>::operator*(const Matrix<M1, N1, Field>& other) const {
  std::vector<std::vector<Field>> result(M, std::vector<Field>(N1));
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N1; ++j) {
      for (size_t k = 0; k < N; ++k) {
        result[i][j] += data_[i][k] * other(k, j);
      }
    }
  }
  return Matrix(result);
}

template <size_t M, size_t N, typename Field>
Matrix<M, N, Field>& Matrix<M, N, Field>::operator=(
    const Matrix<M, N, Field>& other) {
  if (this == &other) {
    return *this;
  }
  data_ = other.data_;
  return *this;
}

// ========================================================================

template <size_t N, typename Field = double>
class SquareMatrix : public Matrix<N, N, Field> {
 public:
  SquareMatrix() : Matrix<N, N>(){};
};

#endif  // MATRIX_H