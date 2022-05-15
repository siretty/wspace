#ifndef WSPACE_APPLY_INTEGER_SEQUENCE_HPP_44812BB596634DA7B3F5B986D643BABA
#define WSPACE_APPLY_INTEGER_SEQUENCE_HPP_44812BB596634DA7B3F5B986D643BABA

#include <utility>

namespace wspace {

template <typename T, T... integer, typename F>
void apply_integer_sequence(std::integer_sequence<T, integer...>, F &&f)
{
    std::forward<F>(f)(integer...);
}

template <std::size_t N, typename F>
void apply_index_sequence(F &&f)
{
    apply_integer_sequence(std::make_index_sequence<N>{}, std::forward<F>(f));
}

} // namespace wspace

#endif // WSPACE_APPLY_INTEGER_SEQUENCE_HPP_44812BB596634DA7B3F5B986D643BABA
