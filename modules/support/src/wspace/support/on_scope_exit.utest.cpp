#include "on_scope_exit.hpp"

#include <stdexcept>

#include <gtest/gtest.h>

namespace {

using namespace wspace;

TEST(on_scope_exit, normal_exit)
{
    unsigned trigger_count = 0;

    ASSERT_EQ(trigger_count, 0);
    {
        on_scope_exit([&trigger_count] { ++trigger_count; });
    }
    EXPECT_EQ(trigger_count, 1);
}

TEST(on_scope_exit, exception_exit)
{
    unsigned trigger_count = 0;

    ASSERT_EQ(trigger_count, 0);
    {
        try
        {
            on_scope_exit([&trigger_count] { ++trigger_count; });
            throw std::runtime_error("boom");
        }
        catch (const std::exception &)
        {
        }
    }
    EXPECT_EQ(trigger_count, 1);
}

} // namespace