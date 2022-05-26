#include "wrapper.hpp"

#include <gtest/gtest.h>

namespace {

using namespace wspace;

struct Thing
{
    int value;
};

TEST(wrapper, implicit_constructor)
{
    constexpr auto check = [](Wrapper<Thing> thing, int expected) { ASSERT_EQ(thing->value, expected); };
    check(Thing{1}, 1);
    check(Thing{2}, 2);
    check(Thing{3}, 3);
}

struct NamedInt : Wrapper<int>
{
    using Wrapper<int>::Wrapper;
};

TEST(wrapper, named_implicit_constructor)
{
    constexpr auto check = [](NamedInt named_int, int expected) { ASSERT_EQ(named_int.get(), expected); };
    check(NamedInt(1), 1);
    check(NamedInt(2), 2);
    check(NamedInt(3), 3);
}

} // namespace
