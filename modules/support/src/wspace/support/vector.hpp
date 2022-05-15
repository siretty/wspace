#ifndef WSPACE_VECTOR_HPP_B0A6F8F5B9AF4240B451F03BAD55350C
#define WSPACE_VECTOR_HPP_B0A6F8F5B9AF4240B451F03BAD55350C

#include <concepts>
#include <utility>

#include <cstddef>

namespace wspace {

template <typename T, std::size_t N>
class Vector
{
public:
    constexpr Vector() noexcept = default;

    template <typename U>
    requires(std::convertible_to<U, T>)
    explicit constexpr Vector(const Vector<U, N> &other);

    template <typename... U>
    requires(sizeof...(U) == N && (std::convertible_to<U, T> && ...))
    constexpr Vector(U &&...u);

    constexpr static auto size() -> std::size_t;

    constexpr auto data() const -> const T *;
    constexpr auto data() -> T *;

    constexpr auto begin() const -> const T *;
    constexpr auto begin() -> T *;

    constexpr auto end() const -> const T *;
    constexpr auto end() -> T *;

    constexpr auto operator[](std::size_t dim) const -> const T &;
    constexpr auto operator[](std::size_t dim) -> T &;

    constexpr bool operator==(const Vector &) const noexcept = default;
    constexpr bool operator!=(const Vector &) const noexcept = default;

private:
    T components[N];
};

using Vector1F = Vector<float, 1>;
using Vector2F = Vector<float, 2>;
using Vector3F = Vector<float, 3>;

using Vector1D = Vector<double, 1>;
using Vector2D = Vector<double, 2>;
using Vector3D = Vector<double, 3>;

template <typename T, std::size_t N>
constexpr auto operator+=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &;

template <typename T, std::size_t N>
constexpr auto operator-=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &;

template <typename T, std::size_t N>
constexpr auto operator*=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &;

template <typename T, std::size_t N>
constexpr auto operator/=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &;

template <typename T, std::size_t N>
constexpr auto operator+(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>;

template <typename T, std::size_t N>
constexpr auto operator-(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>;

template <typename T, std::size_t N>
constexpr auto operator*(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>;

template <typename T, std::size_t N>
constexpr auto operator/(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>;

template <typename T, std::size_t N>
constexpr auto dot(const Vector<T, N> &lhs, const Vector<T, N> &rhs) -> T;

template <typename T, std::size_t N>
constexpr auto magnitude(const Vector<T, N> &vector) -> T;

template <typename T, std::size_t N>
constexpr auto cmin(const Vector<T, N> &vector) -> T;

template <typename T, std::size_t N>
constexpr auto cmax(const Vector<T, N> &vector) -> T;

template <typename T, std::size_t N>
constexpr auto cminmax(const Vector<T, N> &vector) -> std::pair<T, T>;

} // namespace wspace

// ============================================================
// Implementation
// ============================================================

#include "apply_integer_sequence.hpp"

#include <algorithm>
#include <iterator>

#include <cmath>

namespace wspace {

template <typename T, std::size_t N>
template <typename U>
requires(std::convertible_to<U, T>)
constexpr Vector<T, N>::Vector(const Vector<U, N> &other)
{
    apply_index_sequence<N>([this, &other](const auto... dim) { ((this->components[dim] = T(other[dim])), ...); });
}

template <typename T, std::size_t N>
template <typename... U>
requires(sizeof...(U) == N && (std::convertible_to<U, T> && ...))
constexpr Vector<T, N>::Vector(U &&...u) : components{static_cast<T>(u)...}
{
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::size() -> std::size_t
{
    return N;
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::data() const -> const T *
{
    return &components[0];
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::data() -> T *
{
    return &components[0];
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::begin() const -> const T *
{
    return data();
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::begin() -> T *
{
    return data();
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::end() const -> const T *
{
    return std::next(begin(), size());
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::end() -> T *
{
    return std::next(data(), size());
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::operator[](const std::size_t dim) const -> const T &
{
    return components[dim];
}

template <typename T, std::size_t N>
constexpr auto Vector<T, N>::operator[](const std::size_t dim) -> T &
{
    return components[dim];
}

template <typename T, std::size_t N>
constexpr auto operator+=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] += rhs[dim]), ...); });
    return lhs;
}

template <typename T, std::size_t N>
constexpr auto operator-=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] += rhs[dim]), ...); });
    return lhs;
}

template <typename T, std::size_t N>
constexpr auto operator*=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] += rhs[dim]), ...); });
    return lhs;
}

template <typename T, std::size_t N>
constexpr auto operator/=(Vector<T, N> &lhs, const Vector<T, N> &rhs) -> Vector<T, N> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] += rhs[dim]), ...); });
    return lhs;
}

template <typename T, std::size_t N>
constexpr auto operator+(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>
{
    return lhs += rhs;
}

template <typename T, std::size_t N>
constexpr auto operator-(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>
{
    return lhs -= rhs;
}

template <typename T, std::size_t N>
constexpr auto operator*(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>
{
    return lhs *= rhs;
}

template <typename T, std::size_t N>
constexpr auto operator/(Vector<T, N> lhs, const Vector<T, N> &rhs) -> Vector<T, N>
{
    return lhs /= rhs;
}

template <typename T, std::size_t N>
constexpr auto dot(const Vector<T, N> &lhs, const Vector<T, N> &rhs) -> T
{
    auto result = T(0);
    apply_index_sequence<N>([&result, &lhs, &rhs](const auto... dim) { result = ((lhs[dim] * rhs[dim]) + ...); });
    return result;
}

template <typename T, std::size_t N>
constexpr auto magnitude(const Vector<T, N> &vector) -> T
{
    return std::sqrt(dot(vector, vector));
}

template <typename T, std::size_t N>
constexpr auto cmin(const Vector<T, N> &vector) -> T
{
    return *std::min_element(vector.begin(), vector.end());
}

template <typename T, std::size_t N>
constexpr auto cmax(const Vector<T, N> &vector) -> T
{
    return *std::max_element(vector.begin(), vector.end());
}

template <typename T, std::size_t N>
constexpr auto cminmax(const Vector<T, N> &vector) -> std::pair<T, T>
{
    const auto [min_it, max_it] = std::minmax_element(vector.begin(), vector.end());
    return std::make_pair(*min_it, *max_it);
}

} // namespace wspace

#endif // WSPACE_VECTOR_HPP_B0A6F8F5B9AF4240B451F03BAD55350C
