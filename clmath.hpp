#pragma once
#include <cstddef>

template <typename T, std::size_t N> struct Vector {
  T data[N];

  constexpr T &operator[](std::size_t i) { return data[i]; }

  constexpr const T &operator[](std::size_t i) const { return data[i]; }

  constexpr std::size_t size() const { return N; }
};

template <typename T, std::size_t N>
constexpr Vector<T, N> operator+(const Vector<T, N> &left,
                                 const Vector<T, N> &right) {
  Vector<T, N> res{};
  for (std::size_t i{0}; i < N; ++i) {
    res[i] = left[i] + right[i];
  }

  return res;
}

template <typename T, std::size_t N>
constexpr Vector<T, N> operator-(const Vector<T, N> &left,
                                 const Vector<T, N> &right) {
  Vector<T, N> res{};
  for (std::size_t i{0}; i < N; ++i) {
    res[i] = left[i] - right[i];
  }

  return res;
}

template <typename T, std::size_t N>
constexpr Vector<T, N> operator*(T scalar, const Vector<T, N> &right) {
  Vector<T, N> res{};
  for (std::size_t i{0}; i < N; ++i) {
    res[i] = scalar * right[i];
  }

  return res;
}

template <typename T, std::size_t N>
constexpr Vector<T, N> operator*(const Vector<T, N> &left, T scalar) {
  Vector<T, N> res{};
  for (std::size_t i{0}; i < N; ++i) {
    res[i] = left[i] * scalar;
  }

  return res;
}

template <typename T, std::size_t N>
constexpr T dot(const Vector<T, N> &left, const Vector<T, N> &right) {
  T sum{};
  for (std::size_t i{0}; i < N; ++i) {
    sum += left[i] * right[i];
  }
  return sum;
}

template <typename T, std::size_t N>
constexpr Vector<T, N> cross(const Vector<T, N> &left, const Vector<T, N> &right) {
  if (N != 3) {
    return Vector<T,N> {};
  }
  Vector<T, N> res{};
  res[0] = (left[1] * right[2]) - (left[2] * right[1]);
  res[1] = -((left[0] * right[2]) - (left[2] * right[0]));
  res[2] = (left[0] * right[1]) - (left[1] * right[0]);

  return res;
}

