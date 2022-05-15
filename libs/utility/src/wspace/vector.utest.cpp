#include "vector.hpp"

#include <gtest/gtest.h>

namespace {

using namespace wspace;

TEST(Vector, constructor)
{
    auto v = Vector<float, 3>{1.f, 2.f, 3.f};
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0], 1.f);
    ASSERT_EQ(v[1], 2.f);
    ASSERT_EQ(v[2], 3.f);
}

TEST(Vector, operator_add)
{
    const auto u = Vector<float, 3>{1.f, 2.f, 3.f};
    const auto v = Vector<float, 3>{4.f, 5.f, 6.f};

    const auto w = u + v;
    ASSERT_EQ(w.size(), 3);
    ASSERT_EQ(w[0], 5.f);
    ASSERT_EQ(w[1], 7.f);
    ASSERT_EQ(w[2], 9.f);

    auto x = u;
    x += v;
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x[0], w[0]);
    ASSERT_EQ(x[1], w[1]);
    ASSERT_EQ(x[2], w[2]);
}

TEST(Vector, operator_sub)
{
    const auto u = Vector<float, 3>{6.f, 5.f, 4.f};
    const auto v = Vector<float, 3>{1.f, 2.f, 3.f};

    const auto w = u - v;
    ASSERT_EQ(w.size(), 3);
    ASSERT_EQ(w[0], 5.f);
    ASSERT_EQ(w[1], 3.f);
    ASSERT_EQ(w[2], 1.f);

    auto x = u;
    x -= v;
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x[0], w[0]);
    ASSERT_EQ(x[1], w[1]);
    ASSERT_EQ(x[2], w[2]);
}

TEST(Vector, vector_plus_scalar)
{
    const auto u = Vector<float, 3>{1.f, 2.f, 3.f};

    const auto x = u + 1.f;
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x[0], 2.f);
    ASSERT_EQ(x[1], 3.f);
    ASSERT_EQ(x[2], 4.f);

    const auto y = 1.f + u;
    ASSERT_EQ(y.size(), 3);
    ASSERT_EQ(y[0], x[0]);
    ASSERT_EQ(y[1], x[1]);
    ASSERT_EQ(y[2], x[2]);

    auto z = u;
    z += 1.f;
    ASSERT_EQ(z.size(), 3);
    ASSERT_EQ(z[0], x[0]);
    ASSERT_EQ(z[1], x[1]);
    ASSERT_EQ(z[2], x[2]);
}

TEST(Vector, vector_minus_scalar)
{
    const auto u = Vector<float, 3>{1.f, 2.f, 3.f};

    const auto x = u - 1.f;
    ASSERT_EQ(x.size(), 3);
    ASSERT_EQ(x[0], 0.f);
    ASSERT_EQ(x[1], 1.f);
    ASSERT_EQ(x[2], 2.f);

    auto y = u;
    y -= 1.f;
    ASSERT_EQ(y.size(), 3);
    ASSERT_EQ(y[0], x[0]);
    ASSERT_EQ(y[1], x[1]);
    ASSERT_EQ(y[2], x[2]);
}

} // namespace
