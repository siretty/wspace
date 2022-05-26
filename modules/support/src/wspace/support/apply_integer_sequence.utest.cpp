#include "apply_integer_sequence.hpp"

#include <gtest/gtest.h>

#include <array>

namespace {

using namespace wspace;

TEST(apply_integer_sequence, correct_expansion)
{
    apply_integer_sequence(std::integer_sequence<int, 3, 2, 1>{}, [](const auto... items) {
        const auto array = std::array{items...};
        ASSERT_EQ(array.size(), 3);
        EXPECT_EQ(array, (std::array<int, 3>{3, 2, 1}));
    });
}

TEST(apply_index_sequence, correct_expansion)
{
    apply_index_sequence<3>([](const auto... indices) {
        const auto array = std::array{indices...};
        ASSERT_EQ(array.size(), 3);
        EXPECT_EQ(array, (std::array<std::size_t, 3>{0, 1, 2}));
    });
}

} // namespace
