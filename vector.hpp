#pragma once
#include <cstddef>
#include <random>

namespace clmath {

template <typename T, std::size_t N> struct Vector {
  T data[N];

  constexpr T &operator[](std::size_t i) { return data[i]; }

  constexpr const T &operator[](std::size_t i) const { return data[i]; }

  constexpr std::size_t size() const { return N; }
};

template <typename T, std::size_t N>
inline constexpr Vector<T, N> zero_vector{};

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
constexpr Vector<T, N> &operator+=(Vector<T, N> &left,
                                   const Vector<T, N> &right) {
  for (std::size_t i{0}; i < N; ++i) {
    left[i] += right[i];
  }
  return left;
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
constexpr Vector<T, N> &operator-=(Vector<T, N> &left,
                                   const Vector<T, N> &right) {
  for (std::size_t i{0}; i < N; ++i) {
    left[i] -= right[i];
  }
  return left;
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
constexpr Vector<T, N> &operator*=(Vector<T, N> &left, T scalar) {
  for (std::size_t i{0}; i < N; ++i) {
    left[i] *= scalar;
  }

  return left;
}

template <typename T, std::size_t N>
constexpr Vector<T, N> operator/(const Vector<T, N> &left, T scalar) {
  Vector<T, N> res{};
  T recip{1 / scalar};
  for (std::size_t i{0}; i < N; ++i) {
    res[i] = left[i] * recip;
  }

  return res;
}

template <typename T, std::size_t N>
constexpr Vector<T, N> &operator/=(Vector<T, N> &left, T scalar) {
  T recip{1 / scalar};
  for (std::size_t i{0}; i < N; ++i) {
    left[i] *= recip;
  }

  return left;
}

template <typename T, std::size_t N> Vector<T, N> randVec(T min, T max) {
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<T> dist{min, max};

  Vector<T, N> res{};
  for (std::size_t i{0}; i < N; ++i) {
    res[i] = dist(gen);
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
constexpr Vector<T, N> cross(const Vector<T, N> &left,
                             const Vector<T, N> &right) {
  if (N != 3) {
    return Vector<T, N>{};
  }
  Vector<T, N> res{};
  res[0] = (left[1] * right[2]) - (left[2] * right[1]);
  res[1] = -((left[0] * right[2]) - (left[2] * right[0]));
  res[2] = (left[0] * right[1]) - (left[1] * right[0]);

  return res;
}

template <typename T, std::size_t N>
constexpr double magnitude(const Vector<T, N> &vec) {
  double prod{0};
  for (std::size_t i{0}; i < N; ++i) {
    prod += vec[i] * vec[i];
  }

  return std::sqrt(prod);
}

template <typename T, std::size_t N>
constexpr double magnitudeSquared(const Vector<T, N> &vec) {
  double prod{0};
  for (std::size_t i{0}; i < N; ++i) {
    prod += vec[i] * vec[i];
  }

  return prod;
}

template <typename T, std::size_t N>
constexpr Vector<T, N> normalize(const Vector<T, N> &vec) {
  double mag{magnitude(vec)};
  if (mag == 0) {
    return zero_vector<T, N>;
  }
  return (1.0 / mag) * vec;
}
} // namespace clmath
