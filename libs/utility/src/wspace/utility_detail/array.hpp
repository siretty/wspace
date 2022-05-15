#ifndef WSPACE_ARRAY_HPP_397260C559F644318306439175BF798D
#define WSPACE_ARRAY_HPP_397260C559F644318306439175BF798D

#include <concepts>
#include <ostream>
#include <utility>

#include <cstddef>

namespace wspace::utility_detail {

template <typename T, std::size_t N>
class Array
{
public:
    constexpr Array() noexcept = default;

    template <typename... U>
    requires(sizeof...(U) == N && (std::convertible_to<U, T> && ...))
    constexpr Array(U &&...u);

    consteval static auto size() -> std::size_t;

    constexpr auto data() const -> const T *;
    constexpr auto data() -> T *;

    constexpr auto operator[](std::size_t dim) const -> const T &;
    constexpr auto operator[](std::size_t dim) -> T &;

    template <typename F>
    constexpr static void apply_index_sequence(F &&f);

private:
    T components[N];
};

template <typename T, std::size_t N, typename Tag>
auto operator<<(std::ostream &ostream, const Array<T, N> &array) -> std::ostream &;

#define WSPACE_ARRAY_DECLARE_GENERIC_ARITHMETIC_ASSIGNMENT_OPERATOR(OPERATOR, LHS_T, RHS_T)                            \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(LHS_T<T, N> &lhs, const RHS_T<T, N> &rhs)->LHS_T<T, N> &;

#define WSPACE_ARRAY_DECLARE_GENERIC_BINARY_ARITHMETIC_OPERATOR(OPERATOR, LHS_T, RHS_T, RET_T)                         \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(const LHS_T<T, N> &lhs, const RHS_T<T, N> &rhs)->RET_T<T, N>;

#define WSPACE_ARRAY_DECLARE_ARITHMETIC_OPERATOR(OPERATOR, TYPE_T)                                                     \
    WSPACE_ARRAY_DECLARE_GENERIC_ARITHMETIC_ASSIGNMENT_OPERATOR(OPERATOR## =, TYPE_T, TYPE_T)                          \
    WSPACE_ARRAY_DECLARE_GENERIC_BINARY_ARITHMETIC_OPERATOR(OPERATOR, TYPE_T, TYPE_T, TYPE_T)

#define WSPACE_ARRAY_DECLARE_GENERIC_SCALAR_ARITHMETIC_ASSIGNMENT_OPERATOR_L(OPERATOR, LHS_T)                          \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(LHS_T<T, N> &lhs, const T &rhs)->LHS_T<T, N> &;

#define WSPACE_ARRAY_DECLARE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_L(OPERATOR, LHS_T, RET_T)                       \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(const LHS_T<T, N> &lhs, const T &rhs)->RET_T<T, N>;

#define WSPACE_ARRAY_DECLARE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_R(OPERATOR, RHS_T, RET_T)                       \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(const T &lhs, const RHS_T<T, N> &rhs)->RET_T<T, N>;

#define WSPACE_ARRAY_DECLARE_SCALAR_ARITHMETIC_OPERATOR(OPERATOR, TYPE_T)                                              \
    WSPACE_ARRAY_DECLARE_GENERIC_SCALAR_ARITHMETIC_ASSIGNMENT_OPERATOR_L(OPERATOR## =, TYPE_T)                         \
    WSPACE_ARRAY_DECLARE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_L(OPERATOR, TYPE_T, TYPE_T)                         \
    WSPACE_ARRAY_DECLARE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_R(OPERATOR, TYPE_T, TYPE_T)

} // namespace wspace::utility_detail

// ============================================================
// Implementation
// ============================================================

#include "apply_integer_sequence.hpp"

namespace wspace::utility_detail {

template <typename T, std::size_t N>
template <typename... U>
requires(sizeof...(U) == N && (std::convertible_to<U, T> && ...))
constexpr Array<T, N>::Array(U &&...u) : components{static_cast<T>(u)...}
{
}

template <typename T, std::size_t N>
consteval auto Array<T, N>::size() -> std::size_t
{
    return N;
}

template <typename T, std::size_t N>
constexpr auto Array<T, N>::data() const -> const T *
{
    return &components[0];
}

template <typename T, std::size_t N>
constexpr auto Array<T, N>::data() -> T *
{
    return &components[0];
}

template <typename T, std::size_t N>
constexpr auto Array<T, N>::operator[](const std::size_t dim) const -> const T &
{
    return components[dim];
}

template <typename T, std::size_t N>
constexpr auto Array<T, N>::operator[](const std::size_t dim) -> T &
{
    return components[dim];
}

template <typename T, std::size_t N>
template <typename F>
constexpr void Array<T, N>::apply_index_sequence(F &&f)
{
    utility_detail::apply_integer_sequence(std::make_index_sequence<N>{}, std::forward<F>(f));
}

template <typename T, std::size_t N>
auto operator<<(std::ostream &ostream, const Array<T, N> &array) -> std::ostream &
{
    ostream << '(';
    array.template apply_index_sequence([&ostream, &array](const auto dim_0, const auto... dim_n) {
        ostream << array[dim_0];
        ((ostream << ',' << array[dim_n]), ...);
    });
    return ostream << ')';
}

#define WSPACE_ARRAY_DEFINE_GENERIC_ARITHMETIC_ASSIGNMENT_OPERATOR(OPERATOR, LHS_T, RHS_T)                             \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(LHS_T<T, N> &lhs, const RHS_T<T, N> &rhs)->LHS_T<T, N> &                          \
    {                                                                                                                  \
        lhs.template apply_index_sequence([&lhs, &rhs](const auto... dim) { ((lhs[dim] OPERATOR rhs[dim]), ...); });   \
        return lhs;                                                                                                    \
    }

#define WSPACE_ARRAY_DEFINE_GENERIC_BINARY_ARITHMETIC_OPERATOR(OPERATOR, LHS_T, RHS_T, RET_T)                          \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(const LHS_T<T, N> &lhs, const RHS_T<T, N> &rhs)->RET_T<T, N>                      \
    {                                                                                                                  \
        RET_T<T, N> ret;                                                                                               \
        ret.template apply_index_sequence(                                                                             \
            [&ret, &lhs, &rhs](const auto... dim) { ((ret[dim] = lhs[dim] OPERATOR rhs[dim]), ...); });                \
        return ret;                                                                                                    \
    }

#define WSPACE_ARRAY_DEFINE_ARITHMETIC_OPERATOR(OPERATOR, TYPE_T)                                                      \
    WSPACE_ARRAY_DEFINE_GENERIC_ARITHMETIC_ASSIGNMENT_OPERATOR(OPERATOR## =, TYPE_T, TYPE_T)                           \
    WSPACE_ARRAY_DEFINE_GENERIC_BINARY_ARITHMETIC_OPERATOR(OPERATOR, TYPE_T, TYPE_T, TYPE_T)

#define WSPACE_ARRAY_DEFINE_GENERIC_SCALAR_ARITHMETIC_ASSIGNMENT_OPERATOR_L(OPERATOR, LHS_T)                           \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(LHS_T<T, N> &lhs, const T &rhs)->LHS_T<T, N> &                                    \
    {                                                                                                                  \
        lhs.template apply_index_sequence([&lhs, &rhs](const auto... dim) { ((lhs[dim] OPERATOR rhs), ...); });        \
        return lhs;                                                                                                    \
    }

#define WSPACE_ARRAY_DEFINE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_L(OPERATOR, LHS_T, RET_T)                        \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(const LHS_T<T, N> &lhs, const T &rhs)->RET_T<T, N>                                \
    {                                                                                                                  \
        RET_T<T, N> ret;                                                                                               \
        ret.template apply_index_sequence(                                                                             \
            [&ret, &lhs, &rhs](const auto... dim) { ((ret[dim] = lhs[dim] OPERATOR rhs), ...); });                     \
        return ret;                                                                                                    \
    }

#define WSPACE_ARRAY_DEFINE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_R(OPERATOR, RHS_T, RET_T)                        \
    template <typename T, std::size_t N>                                                                               \
    constexpr auto operator OPERATOR(const T &lhs, const RHS_T<T, N> &rhs)->RET_T<T, N>                                \
    {                                                                                                                  \
        RET_T<T, N> ret;                                                                                               \
        ret.template apply_index_sequence(                                                                             \
            [&ret, &lhs, &rhs](const auto... dim) { ((ret[dim] = lhs OPERATOR rhs[dim]), ...); });                     \
        return ret;                                                                                                    \
    }

#define WSPACE_ARRAY_DEFINE_SCALAR_ARITHMETIC_OPERATOR(OPERATOR, TYPE_T)                                               \
    WSPACE_ARRAY_DEFINE_GENERIC_SCALAR_ARITHMETIC_ASSIGNMENT_OPERATOR_L(OPERATOR## =, TYPE_T)                          \
    WSPACE_ARRAY_DEFINE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_L(OPERATOR, TYPE_T, TYPE_T)                          \
    WSPACE_ARRAY_DEFINE_GENERIC_SCALAR_BINARY_ARITHMETIC_OPERATOR_R(OPERATOR, TYPE_T, TYPE_T)

} // namespace wspace::utility_detail

#endif // WSPACE_ARRAY_HPP_397260C559F644318306439175BF798D
