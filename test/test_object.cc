#include <gtest/gtest.h>
#include "object.h"

TEST(ObjectTest, NumberTest)
{
    Number number(5.0);
    ASSERT_EQ(number.get_value(), 5.0);
    std::string str = std::to_string(double(5.0));
    ASSERT_EQ(number.str(), str);
}

TEST(ObjectTest, StringTest)
{
    String string("Hello, World!");
    ASSERT_EQ(string.get_value(), "Hello, World!");
    ASSERT_EQ(string.str(), "Hello, World!");
}

TEST(ObjectTest, BooleanTest)
{
    Boolean boolean(true);
    ASSERT_EQ(boolean.get_value(), true);
    ASSERT_EQ(boolean.str(), "true");
}

TEST(ObjectTest, cast_to_number)
{
    Casting casting;
    std::shared_ptr<Object> number = std::make_unique<Number>(5);
    Number num = casting.cast_to_number(number);
    ASSERT_EQ(num.get_value(), 5);
    TypeCheckVisitor visitor;
    number->accept(visitor);
    ASSERT_EQ(visitor.get_type(), ObjectType::NUMBER);
}

TEST(ObjectTest, cast_to_string)
{
    Casting casting;
    std::shared_ptr<Object> string = std::make_unique<String>("Hello, World!");
    String str = casting.cast_to_string(string);
    ASSERT_EQ(str.get_value(), "Hello, World!");
    TypeCheckVisitor visitor;
    string->accept(visitor);
    ASSERT_EQ(visitor.get_type(), ObjectType::STRING);
}

TEST(ObjectTest, cast_to_boolean)
{
    Casting casting;
    std::shared_ptr<Object> boolean = std::make_unique<Boolean>(true);
    Boolean bool_ = casting.cast_to_boolean(boolean);
    ASSERT_EQ(bool_.get_value(), true);
    TypeCheckVisitor visitor;
    boolean->accept(visitor);
    ASSERT_EQ(visitor.get_type(), ObjectType::BOOLEAN);
}