#include "array.hpp"

#include <gtest/gtest.h>

namespace {

using namespace wspace::utility_detail;

TEST(Array, float_3)
{
    auto a = Array<float, 3>();
    ASSERT_EQ(a.size(), 3);
    for (std::size_t dim = 0; dim < a.size(); ++dim)
    {
        EXPECT_EQ(a[dim], 0);
    }
    for (std::size_t dim = 0; dim < a.size(); ++dim)
    {
        a[dim] = float(dim);
    }
    for (std::size_t dim = 0; dim < a.size(); ++dim)
    {
        EXPECT_EQ(a[dim], float(dim));
    }

    auto b = Array<float, 3>{1.f, 2.f, 3.f};
    ASSERT_EQ(b.size(), 3);
    EXPECT_EQ(b[0], 1.f);
    EXPECT_EQ(b[1], 2.f);
    EXPECT_EQ(b[2], 3.f);
}

} // namespace
