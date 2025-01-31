#include <gtest/gtest.h>
#include "environment.h"

TEST(Environment, Define)
{
    Environment environment;
    environment.define("foo", Value(42.0));
    ASSERT_TRUE(environment.is_defined("foo"));
    ASSERT_EQ(environment.get("foo").get<double>(), 42.0);
}

TEST(Environment, Assign)
{
    Environment environment;
    environment.define("foo", Value(42.0));
    ASSERT_TRUE(environment.is_defined("foo"));
    environment.assign("foo", Value(43.0));
    ASSERT_TRUE(environment.is_defined("foo"));
    ASSERT_EQ(environment.get("foo").get<double>(), 43.0);
}

TEST(Environment, Get)
{
    Environment environment;
    environment.define("foo", Value(42.0));
    ASSERT_TRUE(environment.is_defined("foo"));
    ASSERT_EQ(environment.get("foo").get<double>(), 42.0);
}

TEST(Environment, IsDefined)
{
    Environment environment;
    environment.define("foo", Value(42.0));
    ASSERT_TRUE(environment.is_defined("foo"));
    ASSERT_FALSE(environment.is_defined("bar"));
}

TEST(Environment, Undefined)
{
    Environment environment;
    ASSERT_THROW(environment.get("foo"), std::runtime_error);
}