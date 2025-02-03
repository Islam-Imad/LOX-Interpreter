#include <gtest/gtest.h>
#include "object.h"

TEST(ObjectTest, NumberTest)
{
    OBJ::Number number(5.0);
    ASSERT_EQ(number.get_value(), 5.0);
    std::string str = std::to_string(double(5.0));
    ASSERT_EQ(number.str(), str);
}

TEST(ObjectTest, StringTest)
{
    OBJ::String string("Hello, World!");
    ASSERT_EQ(string.get_value(), "Hello, World!");
    ASSERT_EQ(string.str(), "Hello, World!");
}

TEST(ObjectTest, BooleanTest)
{
    OBJ::Boolean boolean(true);
    ASSERT_EQ(boolean.get_value(), true);
    ASSERT_EQ(boolean.str(), "true");
}

TEST(ObjectTest, cast_to_number)
{
    OBJ::Casting casting;
    std::shared_ptr<OBJ::Object> number = std::make_unique<OBJ::Number>(5);
    OBJ::Number num = casting.cast_to_number(number);
    ASSERT_EQ(num.get_value(), 5);
    OBJ::TypeCheckVisitor visitor;
    number->accept(visitor);
    ASSERT_EQ(visitor.get_type(), OBJ::ObjectType::NUMBER);
}

TEST(ObjectTest, cast_to_string)
{
    OBJ::Casting casting;
    std::shared_ptr<OBJ::Object> string = std::make_unique<OBJ::String>("Hello, World!");
    OBJ::String str = casting.cast_to_string(string);
    ASSERT_EQ(str.get_value(), "Hello, World!");
    OBJ::TypeCheckVisitor visitor;
    string->accept(visitor);
    ASSERT_EQ(visitor.get_type(), OBJ::ObjectType::STRING);
}

TEST(ObjectTest, cast_to_boolean)
{
    OBJ::Casting casting;
    std::shared_ptr<OBJ::Object> boolean = std::make_unique<OBJ::Boolean>(true);
    OBJ::Boolean bool_ = casting.cast_to_boolean(boolean);
    ASSERT_EQ(bool_.get_value(), true);
    OBJ::TypeCheckVisitor visitor;
    boolean->accept(visitor);
    ASSERT_EQ(visitor.get_type(), OBJ::ObjectType::BOOLEAN);
}