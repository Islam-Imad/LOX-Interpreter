#include <gtest/gtest.h>
#include "object.h"

TEST(Environment, Define)
{
    OBJ::ENV environment;
    environment.define("foo", std::make_shared<OBJ::Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));
}

TEST(Environment, Assign)
{
    OBJ::ENV environment;
    environment.define("foo", std::make_shared<OBJ::Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));
    environment.assign("foo", std::make_shared<OBJ::Number>(43.0));
    ASSERT_TRUE(environment.contains("foo"));

    auto value = environment.get("foo");
    OBJ::Casting casting;
    OBJ::TypeCheckVisitor visitor;
    value->get()->accept(visitor);
    ASSERT_EQ(visitor.get_type(), OBJ::ObjectType::NUMBER);
    double number = casting.cast_to_number(*value);
    ASSERT_EQ(number, 43.0);
}

TEST(Environment, Get)
{
    OBJ::ENV environment;
    environment.define("foo", std::make_shared<OBJ::Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));

    auto value = environment.get("foo");
    OBJ::Casting casting;
    OBJ::TypeCheckVisitor visitor;
    value->get()->accept(visitor);
    ASSERT_EQ(visitor.get_type(), OBJ::ObjectType::NUMBER);
    double number = casting.cast_to_number(*value);
    ASSERT_EQ(number, 42.0);
}

TEST(Environment, IsDefined)
{
    OBJ::ENV environment;
    environment.define("foo", std::make_shared<OBJ::Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));
    ASSERT_FALSE(environment.contains("bar"));
}

TEST(Environment, Undefined)
{
    OBJ::ENV environment;
    ASSERT_THROW(environment.get("foo"), std::runtime_error);
}

TEST(Environment, STRING){
    OBJ::ENV environment;
    environment.define("foo", std::make_shared<OBJ::String>("Hello, World!"));
    ASSERT_TRUE(environment.contains("foo"));

    auto value = environment.get("foo");
    OBJ::Casting casting;
    OBJ::TypeCheckVisitor visitor;
    value->get()->accept(visitor);
    ASSERT_EQ(visitor.get_type(), OBJ::ObjectType::STRING);
    std::string str = casting.cast_to_string(*value);
    ASSERT_EQ(str, "Hello, World!");
}