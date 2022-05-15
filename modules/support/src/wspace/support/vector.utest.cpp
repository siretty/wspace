#include "vector.hpp"

#include <gtest/gtest.h>

namespace {

using namespace wspace;

TEST(vector, component_construction)
{
    auto v1 = Vector1D(1.23);
    ASSERT_EQ(v1.size(), 1);
    ASSERT_DOUBLE_EQ(v1[0], 1.23);

    auto v2 = Vector2D(1.23, 4.56);
    ASSERT_EQ(v2.size(), 2);
    ASSERT_DOUBLE_EQ(v2[0], 1.23);
    ASSERT_DOUBLE_EQ(v2[1], 4.56);

    auto v3 = Vector3D(1.23, 4.56, 7.89);
    ASSERT_EQ(v3.size(), 3);
    ASSERT_DOUBLE_EQ(v3[0], 1.23);
    ASSERT_DOUBLE_EQ(v3[1], 4.56);
    ASSERT_DOUBLE_EQ(v3[2], 7.89);
}

TEST(vector, converting_construction)
{
    auto v1 = Vector1D(Vector1F(1.23f));
    ASSERT_EQ(v1.size(), 1);
    ASSERT_DOUBLE_EQ(v1[0], 1.23f);

    auto v2 = Vector2D(Vector2F(1.23f, 4.56f));
    ASSERT_EQ(v2.size(), 2);
    ASSERT_DOUBLE_EQ(v2[0], 1.23f);
    ASSERT_DOUBLE_EQ(v2[1], 4.56f);

    auto v3 = Vector3D(Vector3F(1.23f, 4.56f, 7.89f));
    ASSERT_EQ(v3.size(), 3);
    ASSERT_DOUBLE_EQ(v3[0], 1.23f);
    ASSERT_DOUBLE_EQ(v3[1], 4.56f);
    ASSERT_DOUBLE_EQ(v3[2], 7.89f);
}

TEST(vector, dot)
{
    const auto u = Vector3D(1., 2., 3.);
    const auto v = Vector3D(4., 5., 6.);
    ASSERT_DOUBLE_EQ(dot(u, v), (1. * 4.) + (2. * 5.) + (3. * 6.));
}

TEST(vector, magnitude)
{
    const auto u = Vector3D(1., 2., 3.);
    ASSERT_DOUBLE_EQ(magnitude(u), std::sqrt((1. * 1.) + (2. * 2.) + (3. * 3.)));
}

TEST(vector, cmin_cmax_cminmax)
{
    const auto u = Vector3D(1., 2., 3.);
    ASSERT_DOUBLE_EQ(cmin(u), 1.);
    ASSERT_DOUBLE_EQ(cmax(u), 3.);
    ASSERT_DOUBLE_EQ(cminmax(u).first, cmin(u));
    ASSERT_DOUBLE_EQ(cminmax(u).second, cmax(u));

    const auto v = Vector3D(2., 3., 1.);
    ASSERT_DOUBLE_EQ(cmin(v), 1.);
    ASSERT_DOUBLE_EQ(cmax(v), 3.);
    ASSERT_DOUBLE_EQ(cminmax(v).first, cmin(v));
    ASSERT_DOUBLE_EQ(cminmax(v).second, cmax(v));

    const auto w = Vector3D(3., 1., 2.);
    ASSERT_DOUBLE_EQ(cmin(w), 1.);
    ASSERT_DOUBLE_EQ(cmax(w), 3.);
    ASSERT_DOUBLE_EQ(cminmax(w).first, cmin(w));
    ASSERT_DOUBLE_EQ(cminmax(w).second, cmax(w));
}

} // namespace
