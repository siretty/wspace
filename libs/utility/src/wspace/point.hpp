#ifndef WSPACE_POINT_HPP_88C89E62AE72475CBF5BC10646EB987C
#define WSPACE_POINT_HPP_88C89E62AE72475CBF5BC10646EB987C

#include "utility_detail/array.hpp"

namespace wspace {

template <typename T, std::size_t N>
class Point : public utility_detail::Array<T, N>
{
public:
    using utility_detail::Array<T, N>::Array;
};

} // namespace wspace

#endif // WSPACE_POINT_HPP_88C89E62AE72475CBF5BC10646EB987C
