#ifndef WSPACE_APPLY_INTEGER_SEQUENCE_HPP_44812BB596634DA7B3F5B986D643BABA
#define WSPACE_APPLY_INTEGER_SEQUENCE_HPP_44812BB596634DA7B3F5B986D643BABA

#include <utility>

namespace wspace::utility_detail {

template <typename T, T... integer, typename F>
void apply_integer_sequence(std::integer_sequence<T, integer...>, F &&f)
{
    std::forward<F>(f)(integer...);
}

} // namespace wspace::utility_detail

#endif // WSPACE_APPLY_INTEGER_SEQUENCE_HPP_44812BB596634DA7B3F5B986D643BABA
