#include "affine_space.hpp"

#include <gtest/gtest.h>

namespace {

using namespace wspace;

TEST(affine_operations, point_plus_vector_equals_point)
{
    const auto p = Point<float, 3>{1.f, 2.f, 3.f};
    const auto v = Vector<float, 3>{4.f, 5.f, 6.f};

    const auto q = p + v;
    ASSERT_TRUE((std::same_as<decltype(q), decltype(p)>));
    ASSERT_EQ(q.size(), 3);
    ASSERT_EQ(q[0], 5.f);
    ASSERT_EQ(q[1], 7.f);
    ASSERT_EQ(q[2], 9.f);

    auto r = p;
    r += v;
    ASSERT_TRUE((std::same_as<std::remove_const_t<decltype(q)>, decltype(r)>));
    ASSERT_EQ(r.size(), 3);
    ASSERT_EQ(r[0], q[0]);
    ASSERT_EQ(r[1], q[1]);
    ASSERT_EQ(r[2], q[2]);
}

TEST(affine_operations, point_minus_vector_equals_point)
{
    const auto p = Point<float, 3>{6.f, 5.f, 4.f};
    const auto v = Vector<float, 3>{1.f, 2.f, 3.f};

    const auto q = p - v;
    ASSERT_TRUE((std::same_as<decltype(q), decltype(p)>));
    ASSERT_EQ(q.size(), 3);
    ASSERT_EQ(q[0], 5.f);
    ASSERT_EQ(q[1], 3.f);
    ASSERT_EQ(q[2], 1.f);

    auto r = p;
    r -= v;
    ASSERT_TRUE((std::same_as<std::remove_const_t<decltype(q)>, decltype(r)>));
    ASSERT_EQ(r.size(), 3);
    ASSERT_EQ(r[0], q[0]);
    ASSERT_EQ(r[1], q[1]);
    ASSERT_EQ(r[2], q[2]);
}

TEST(affine_operations, point_minus_point_equals_vector)
{
    const auto p = Point<float, 3>{6.f, 5.f, 4.f};
    const auto v = Point<float, 3>{1.f, 2.f, 3.f};

    const auto q = p - v;
    ASSERT_TRUE((std::same_as<std::remove_const_t<decltype(q)>, Vector<float, 3>>));
    ASSERT_EQ(q.size(), 3);
    ASSERT_EQ(q[0], 5.f);
    ASSERT_EQ(q[1], 3.f);
    ASSERT_EQ(q[2], 1.f);
}

} // namespace
