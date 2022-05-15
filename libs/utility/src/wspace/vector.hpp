#ifndef WSPACE_VECTOR_HPP_3B1BD4FDDD8D4297A5DAFEC53C85A6CD
#define WSPACE_VECTOR_HPP_3B1BD4FDDD8D4297A5DAFEC53C85A6CD

#include "utility_detail/array.hpp"

namespace wspace {

template <typename T, std::size_t N>
class Vector : public utility_detail::Array<T, N>
{
public:
    using utility_detail::Array<T, N>::Array;
};

WSPACE_ARRAY_DECLARE_ARITHMETIC_OPERATOR(+, Vector)
WSPACE_ARRAY_DECLARE_ARITHMETIC_OPERATOR(-, Vector)

WSPACE_ARRAY_DECLARE_SCALAR_ARITHMETIC_OPERATOR(-, Vector)
WSPACE_ARRAY_DECLARE_SCALAR_ARITHMETIC_OPERATOR(+, Vector)
WSPACE_ARRAY_DECLARE_SCALAR_ARITHMETIC_OPERATOR(*, Vector)
WSPACE_ARRAY_DECLARE_SCALAR_ARITHMETIC_OPERATOR(/, Vector)

template <typename T, std::size_t N>
constexpr auto dot(const Vector<T, N> &lhs, const Vector<T, N> &rhs) -> T;

template <typename T, std::size_t N>
constexpr auto magnitude(const Vector<T, N> &vector) -> T;

template <typename T, std::size_t N>
constexpr auto normalize(Vector<T, N> vector) -> Vector<T, N>;

template <typename T, std::size_t N>
constexpr auto normalize_or_zero(Vector<T, N> vector) -> Vector<T, N>;

} // namespace wspace

// ============================================================
// Implementation
// ============================================================

#include <cmath>

namespace wspace {

WSPACE_ARRAY_DEFINE_ARITHMETIC_OPERATOR(+, Vector)
WSPACE_ARRAY_DEFINE_ARITHMETIC_OPERATOR(-, Vector)

WSPACE_ARRAY_DEFINE_SCALAR_ARITHMETIC_OPERATOR(-, Vector)
WSPACE_ARRAY_DEFINE_SCALAR_ARITHMETIC_OPERATOR(+, Vector)
WSPACE_ARRAY_DEFINE_SCALAR_ARITHMETIC_OPERATOR(*, Vector)
WSPACE_ARRAY_DEFINE_SCALAR_ARITHMETIC_OPERATOR(/, Vector)

template <typename T, std::size_t N>
constexpr auto dot(const Vector<T, N> &lhs, const Vector<T, N> &rhs) -> T
{
    auto result = T(0);
    lhs.apply_index_sequence([&result, &lhs, &rhs](const auto... dim) { ((result += lhs[dim] * rhs[dim]), ...); });
    return result;
}

template <typename T, std::size_t N>
constexpr auto magnitude(const Vector<T, N> &vector) -> T
{
    using std::sqrt;
    return sqrt(dot(vector, vector));
}

template <typename T, std::size_t N>
constexpr auto normalize(Vector<T, N> vector) -> Vector<T, N>
{
    return vector /= magnitude(vector);
}

template <typename T, std::size_t N>
constexpr auto normalize_or_zero(Vector<T, N> vector) -> Vector<T, N>
{
    using std::sqrt;
    const auto mag = magnitude(vector);
    const auto eps = sqrt(std::numeric_limits<T>::epsilon());
    return vector / (T(mag <= eps) * T(1) + T(mag > eps) * mag);
}

} // namespace wspace

#endif // WSPACE_VECTOR_HPP_3B1BD4FDDD8D4297A5DAFEC53C85A6CD
