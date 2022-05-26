#ifndef WSPACE_ON_SCOPE_EXIT_HPP_177278E2A17341DC8F29A864A38836E9
#define WSPACE_ON_SCOPE_EXIT_HPP_177278E2A17341DC8F29A864A38836E9

#include <concepts>
#include <functional>

#include <utility>

namespace wspace {

template <typename F>
class OnScopeExit
{
public:
    OnScopeExit() = default;

    template <typename G>
    requires(std::invocable<std::remove_cvref_t<G>>)
    explicit OnScopeExit(G &&callback) : _callback(std::forward<G>(callback))
    {
    }

    ~OnScopeExit()
    {
        if constexpr (std::convertible_to<decltype(_callback), bool>)
        {
            if (!static_cast<bool>(_callback))
            {
                return;
            }
        }

        _callback();
    }

private:
    F _callback;
};

template <typename F>
requires(std::invocable<std::remove_cvref_t<F>>)
auto on_scope_exit(F &&f) -> OnScopeExit<std::remove_cvref_t<F>>
{
    return OnScopeExit<std::remove_cvref_t<F>>(std::forward<F>(f));
}

using OnScopeExitFunction = OnScopeExit<std::function<void()>>;

template <typename F>
requires(std::invocable<std::remove_cvref_t<F>>)
auto on_scope_exit_function(F &&f) -> OnScopeExitFunction
{
    return OnScopeExitFunction(std::forward<F>(f));
}

} // namespace wspace

#endif // WSPACE_ON_SCOPE_EXIT_HPP_177278E2A17341DC8F29A864A38836E9
