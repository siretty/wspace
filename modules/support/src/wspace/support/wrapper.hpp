#ifndef WSPACE_WRAPPER_HPP_258B1246D8FF4069AC2F7184FCE147B6
#define WSPACE_WRAPPER_HPP_258B1246D8FF4069AC2F7184FCE147B6

#include <concepts>
#include <utility>

namespace wspace {

template <typename T>
class Wrapper
{
public:
    using WrapperType = Wrapper<T>;

    template <typename... U>
    requires(std::constructible_from<T, U...>)
    constexpr Wrapper(U &&...args) : _wrapped(std::forward<U>(args)...)
    {
    }

    constexpr operator T &() &
    {
        return _wrapped;
    }

    constexpr operator const T &() const &
    {
        return _wrapped;
    }

    constexpr operator T &&() &&
    {
        return std::move(_wrapped);
    }

    constexpr void swap(Wrapper &other)
    {
        using std::swap;
        swap(_wrapped, other._wrapped);
    }

    constexpr auto get() const & -> const T &
    {
        return _wrapped;
    }

    constexpr auto get() & -> T &
    {
        return _wrapped;
    }

    constexpr auto get() && -> T &&
    {
        return std::move(_wrapped);
    }

    constexpr void set(const T &wrapped)
    {
        _wrapped = wrapped;
    }

    constexpr void set(T &&wrapped)
    {
        _wrapped = std::move(wrapped);
    }

    constexpr auto operator*() const & -> const T &
    {
        return _wrapped;
    }

    constexpr auto operator*() & -> T &
    {
        return _wrapped;
    }

    constexpr auto operator->() const -> const T *
    {
        return std::addressof(_wrapped);
    }

    constexpr auto operator->() -> T *
    {
        return std::addressof(_wrapped);
    }

private:
    T _wrapped = {};
};

} // namespace wspace

#endif // WSPACE_WRAPPER_HPP_258B1246D8FF4069AC2F7184FCE147B6
