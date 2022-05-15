#include "apply_integer_sequence.hpp"

#include <array>

#include <gtest/gtest.h>

namespace {

using namespace wspace::utility_detail;

TEST(apply_integer_sequence, expands_sequences)
{
    apply_integer_sequence(std::integer_sequence<int>{},
                           [](const auto... integer) { ASSERT_EQ(sizeof...(integer), 0); });

    apply_integer_sequence(std::integer_sequence<int, 1234>{}, [](const auto... integer) {
        ASSERT_EQ(sizeof...(integer), 1);
        ASSERT_EQ(integer..., 1234);
    });

    apply_integer_sequence(std::integer_sequence<int, 1, 3, 5, 7>{}, [](const auto... integer) {
        ASSERT_EQ(sizeof...(integer), 4);

        const auto a = std::array{integer...};
        ASSERT_EQ(a.size(), 4);
        ASSERT_EQ(a[0], 1);
        ASSERT_EQ(a[1], 3);
        ASSERT_EQ(a[2], 5);
        ASSERT_EQ(a[3], 7);
    });
}

} // namespace
