#include <gtest/gtest.h>
#include "object.h"

TEST(Environment, Define)
{
    ENV environment;
    environment.define("foo", std::make_shared<Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));
}

TEST(Environment, Assign)
{
    ENV environment;
    environment.define("foo", std::make_shared<Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));
    environment.assign("foo", std::make_shared<Number>(43.0));
    ASSERT_TRUE(environment.contains("foo"));

    auto value = environment.get("foo");
    Casting casting;
    TypeCheckVisitor visitor;
    value->get()->accept(visitor);
    ASSERT_EQ(visitor.get_type(), ObjectType::NUMBER);
    double number = casting.cast_to_number(*value);
    ASSERT_EQ(number, 43.0);
}

TEST(Environment, Get)
{
    ENV environment;
    environment.define("foo", std::make_shared<Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));

    auto value = environment.get("foo");
    Casting casting;
    TypeCheckVisitor visitor;
    value->get()->accept(visitor);
    ASSERT_EQ(visitor.get_type(), ObjectType::NUMBER);
    double number = casting.cast_to_number(*value);
    ASSERT_EQ(number, 42.0);
}

TEST(Environment, IsDefined)
{
    ENV environment;
    environment.define("foo", std::make_shared<Number>(42.0));
    ASSERT_TRUE(environment.contains("foo"));
    ASSERT_FALSE(environment.contains("bar"));
}

TEST(Environment, Undefined)
{
    ENV environment;
    ASSERT_THROW(environment.get("foo"), std::runtime_error);
}

TEST(Environment, STRING){
    ENV environment;
    environment.define("foo", std::make_shared<String>("Hello, World!"));
    ASSERT_TRUE(environment.contains("foo"));

    auto value = environment.get("foo");
    Casting casting;
    TypeCheckVisitor visitor;
    value->get()->accept(visitor);
    ASSERT_EQ(visitor.get_type(), ObjectType::STRING);
    std::string str = casting.cast_to_string(*value);
    ASSERT_EQ(str, "Hello, World!");
}