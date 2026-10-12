#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>

namespace clmath {
template <typename T, std::size_t n, std::size_t m> struct Matrix_Small {
  T data[n * m];

  constexpr T &operator[](std::size_t i) { return data[i]; }

  constexpr const T &operator[](std::size_t i) const { return data[i]; }

  constexpr std::size_t size() const { return n * m; }
}; 

template <typename T> struct Matrix {
  std::size_t rows;
  std::size_t cols;
  std::vector<T> data;

  Matrix(std::size_t n, std::size_t m) : rows(n), cols(m), data(rows * cols) {}

  T &operator() (std::size_t i, std::size_t j) { return data[i * cols + j]; }

  const T &operator() (std::size_t i, std::size_t j) const { return data[i*cols + j]; }

  std::size_t size() const { return rows * cols; }
};

template <typename T> 
void matmult(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& out) {
  assert(a.cols == b.rows && out.rows == a.rows && out.cols == b.cols);
  std::fill(out.data.begin(), out.data.end(), T{});
  for (std::size_t i {0}; i < a.rows; ++i) {
    for (std::size_t k {0}; k < b.rows; ++k) {
      const T a_value = a(i, k);
      for (std::size_t j {0}; j < b.cols; ++j) {
        out(i, j) += a_value * b(k, j);
      }
    }
  }
}
}
