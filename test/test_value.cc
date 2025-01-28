#include <gtest/gtest.h>
#include "value.h"

TEST(ValueTest, Number)
{
    Value value(42.0);
    ASSERT_TRUE(value.is_type(ValueType::Number));
    ASSERT_EQ(value.get<double>(), 42.0);
}

TEST(ValueTest, String)
{
    std::string text = "Hello, World!";
    Value value(text);
    ASSERT_TRUE(value.is_type(ValueType::String));
    ASSERT_EQ(value.get<std::string>(), text);
}

TEST(ValueTest, Boolean)
{
    Value value(true);
    ASSERT_TRUE(value.is_type(ValueType::Boolean));
    ASSERT_EQ(value.get<bool>(), true);
}

TEST(ValueTest, Nil)
{
    Value value;
    ASSERT_TRUE(value.is_type(ValueType::Nil));
}
