#ifndef WSPACE_VECTOR_HPP_B0A6F8F5B9AF4240B451F03BAD55350C
#define WSPACE_VECTOR_HPP_B0A6F8F5B9AF4240B451F03BAD55350C

#include <concepts>
#include <limits>
#include <ostream>
#include <utility>

#include <cstddef>

namespace wspace {

template <typename T, std::size_t N, typename Tag = void>
class Vector
{
public:
    constexpr Vector() noexcept = default;

    template <typename U, typename UTag>
    requires(std::convertible_to<U, T>)
    constexpr Vector(const Vector<U, N, UTag> &other);

    template <typename U, typename UTag>
    requires(std::convertible_to<U, T>)
    constexpr Vector(Vector<U, N, UTag> &&other);

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

template <typename Tag>
using Vector1FT = Vector<float, 1, Tag>;
using Vector1F = Vector1FT<void>;

template <typename Tag>
using Vector2FT = Vector<float, 2, Tag>;
using Vector2F = Vector2FT<void>;

template <typename Tag>
using Vector3FT = Vector<float, 3, Tag>;
using Vector3F = Vector3FT<void>;

template <typename Tag>
using Vector1DT = Vector<double, 1, Tag>;
using Vector1D = Vector1DT<void>;

template <typename Tag>
using Vector2DT = Vector<double, 2, Tag>;
using Vector2D = Vector2DT<void>;

template <typename Tag>
using Vector3DT = Vector<double, 3, Tag>;
using Vector3D = Vector3DT<void>;

// Vector @= Vector

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator+=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &;

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator-=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &;

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator*=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &;

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator/=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &;

// Vector @ Vector -> Vector

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator+(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator-(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator*(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator/(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>;

// Vector @= Scalar -> Vector

template <typename T, std::size_t N, typename LHS>
constexpr auto operator+=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &;

template <typename T, std::size_t N, typename LHS>
constexpr auto operator-=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &;

template <typename T, std::size_t N, typename LHS>
constexpr auto operator*=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &;

template <typename T, std::size_t N, typename LHS>
constexpr auto operator/=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &;

// Vector @ Scalar -> Vector

template <typename T, std::size_t N, typename LHS>
constexpr auto operator+(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename LHS>
constexpr auto operator-(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename LHS>
constexpr auto operator*(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename LHS>
constexpr auto operator/(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>;

// Scalar @ Vector -> Vector

template <typename T, std::size_t N, typename RHS>
constexpr auto operator+(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename RHS>
constexpr auto operator-(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename RHS>
constexpr auto operator*(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>;

template <typename T, std::size_t N, typename RHS>
constexpr auto operator/(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>;

// Mathematical Functions

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto dot(const Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> T;

template <typename T, std::size_t N, typename Tag>
constexpr auto magnitude(const Vector<T, N, Tag> &vector) -> T;

template <typename T, std::size_t N, typename Tag>
constexpr auto normalized_or_zero(Vector<T, N, Tag> vector) -> Vector<T, N>;

template <typename T, std::size_t N, typename Tag>
constexpr auto cmin(const Vector<T, N, Tag> &vector) -> T;

template <typename T, std::size_t N, typename Tag>
constexpr auto cmax(const Vector<T, N, Tag> &vector) -> T;

template <typename T, std::size_t N, typename Tag>
constexpr auto cminmax(const Vector<T, N, Tag> &vector) -> std::pair<T, T>;

// Stream Output

template <typename T, std::size_t N, typename Tag>
constexpr auto operator<<(std::ostream &ostream, const Vector<T, N, Tag> &vector) -> std::ostream &;

} // namespace wspace

// ============================================================
// Implementation
// ============================================================

#include "apply_integer_sequence.hpp"

#include <algorithm>
#include <iterator>

#include <cmath>

namespace wspace {

template <typename T, std::size_t N, typename Tag>
template <typename U, typename UTag>
requires(std::convertible_to<U, T>)
constexpr Vector<T, N, Tag>::Vector(const Vector<U, N, UTag> &other)
{
    apply_index_sequence<N>([this, &other](const auto... dim) { ((this->components[dim] = T(other[dim])), ...); });
}

template <typename T, std::size_t N, typename Tag>
template <typename U, typename UTag>
requires(std::convertible_to<U, T>)
constexpr Vector<T, N, Tag>::Vector(Vector<U, N, UTag> &&other)
{
    apply_index_sequence<N>([this, &other](const auto... dim) { ((this->components[dim] = T(other[dim])), ...); });
}

template <typename T, std::size_t N, typename Tag>
template <typename... U>
requires(sizeof...(U) == N && (std::convertible_to<U, T> && ...))
constexpr Vector<T, N, Tag>::Vector(U &&...u) : components{static_cast<T>(u)...}
{
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::size() -> std::size_t
{
    return N;
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::data() const -> const T *
{
    return &components[0];
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::data() -> T *
{
    return &components[0];
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::begin() const -> const T *
{
    return data();
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::begin() -> T *
{
    return data();
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::end() const -> const T *
{
    return std::next(begin(), size());
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::end() -> T *
{
    return std::next(data(), size());
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::operator[](const std::size_t dim) const -> const T &
{
    return components[dim];
}

template <typename T, std::size_t N, typename Tag>
constexpr auto Vector<T, N, Tag>::operator[](const std::size_t dim) -> T &
{
    return components[dim];
}

// Vector @= Vector

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator+=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] += rhs[dim]), ...); });
    return lhs;
}

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator-=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] -= rhs[dim]), ...); });
    return lhs;
}

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator*=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] *= rhs[dim]), ...); });
    return lhs;
}

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator/=(Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] /= rhs[dim]), ...); });
    return lhs;
}

// Vector @ Vector -> Vector

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator+(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>
{
    return lhs += rhs;
}

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator-(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>
{
    return lhs -= rhs;
}

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator*(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>
{
    return lhs *= rhs;
}

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto operator/(Vector<T, N, LHS> lhs, const Vector<T, N, RHS> &rhs) -> Vector<T, N>
{
    return lhs /= rhs;
}

// Vector @= Scalar -> Vector

template <typename T, std::size_t N, typename LHS>
constexpr auto operator+=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] += rhs), ...); });
    return lhs;
}

template <typename T, std::size_t N, typename LHS>
constexpr auto operator-=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] -= rhs), ...); });
    return lhs;
}

template <typename T, std::size_t N, typename LHS>
constexpr auto operator*=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] *= rhs), ...); });
    return lhs;
}

template <typename T, std::size_t N, typename LHS>
constexpr auto operator/=(Vector<T, N, LHS> &lhs, const T &rhs) -> Vector<T, N, LHS> &
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((lhs[dim] /= rhs), ...); });
    return lhs;
}

// Vector @ Scalar -> Vector

template <typename T, std::size_t N, typename LHS>
constexpr auto operator+(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>
{
    return lhs += rhs;
}

template <typename T, std::size_t N, typename LHS>
constexpr auto operator-(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>
{
    return lhs -= rhs;
}

template <typename T, std::size_t N, typename LHS>
constexpr auto operator*(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>
{
    return lhs *= rhs;
}

template <typename T, std::size_t N, typename LHS>
constexpr auto operator/(Vector<T, N, LHS> lhs, const T &rhs) -> Vector<T, N>
{
    return lhs /= rhs;
}

// Scalar @ Vector -> Vector

template <typename T, std::size_t N, typename RHS>
constexpr auto operator+(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>
{
    return rhs += lhs;
}

template <typename T, std::size_t N, typename RHS>
constexpr auto operator-(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((rhs[dim] = lhs - rhs[dim]), ...); });
    return rhs;
}

template <typename T, std::size_t N, typename RHS>
constexpr auto operator*(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>
{
    return rhs *= lhs;
}

template <typename T, std::size_t N, typename RHS>
constexpr auto operator/(const T &lhs, Vector<T, N, RHS> rhs) -> Vector<T, N>
{
    apply_index_sequence<N>([&lhs, &rhs](const auto... dim) { ((rhs[dim] = lhs / rhs[dim]), ...); });
    return rhs;
}

// Mathematical Functions

template <typename T, std::size_t N, typename LHS, typename RHS>
constexpr auto dot(const Vector<T, N, LHS> &lhs, const Vector<T, N, RHS> &rhs) -> T
{
    auto result = T(0);
    apply_index_sequence<N>([&result, &lhs, &rhs](const auto... dim) { result = ((lhs[dim] * rhs[dim]) + ...); });
    return result;
}

template <typename T, std::size_t N, typename Tag>
constexpr auto magnitude(const Vector<T, N, Tag> &vector) -> T
{
    return std::sqrt(dot(vector, vector));
}

template <typename T, std::size_t N, typename Tag>
constexpr auto normalized_or_zero(Vector<T, N, Tag> vector) -> Vector<T, N>
{
    const auto mag = magnitude(vector);
    const auto eps = std::sqrt(std::numeric_limits<T>::epsilon());
    return vector / (T(mag < eps) * T(1) + T(mag >= eps) * mag);
}

template <typename T, std::size_t N, typename Tag>
constexpr auto cmin(const Vector<T, N, Tag> &vector) -> T
{
    return *std::min_element(vector.begin(), vector.end());
}

template <typename T, std::size_t N, typename Tag>
constexpr auto cmax(const Vector<T, N, Tag> &vector) -> T
{
    return *std::max_element(vector.begin(), vector.end());
}

template <typename T, std::size_t N, typename Tag>
constexpr auto cminmax(const Vector<T, N, Tag> &vector) -> std::pair<T, T>
{
    const auto [min_it, max_it] = std::minmax_element(vector.begin(), vector.end());
    return std::make_pair(*min_it, *max_it);
}

// Stream Output

template <typename T, std::size_t N, typename Tag>
constexpr auto operator<<(std::ostream &ostream, const Vector<T, N, Tag> &vector) -> std::ostream &
{
    apply_index_sequence<N>([&ostream, &vector](const auto dim0, const auto... dims) {
        ostream << '[' << vector[dim0];
        ((ostream << ',' << vector[dims]), ...);
        ostream << ']';
    });
    return ostream;
}

} // namespace wspace

#endif // WSPACE_VECTOR_HPP_B0A6F8F5B9AF4240B451F03BAD55350C
