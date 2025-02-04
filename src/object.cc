#include "object.h"
#include "function.h"
#include <memory>

Number::Number(double value) : value(value) {}

void Number::accept(ObjectVisitor &v)
{
    v.visit(*this);
}

double Number::get_value() const
{
    return value;
}

std::string Number::str() const
{
    return std::to_string(value);
}

String::String(std::string value) : value(value) {}

void String::accept(ObjectVisitor &v)
{
    v.visit(*this);
}

std::string String::get_value() const
{
    return value;
}

std::string String::str() const
{
    return value;
}

Boolean::Boolean(bool value)
{
    this->value = value;
}

void Boolean::accept(ObjectVisitor &v)
{
    v.visit(*this);
}

bool Boolean::get_value() const
{
    return value;
}

std::string Boolean::str() const
{
    return value ? "true" : "false";
}

Nil::Nil()
{
}

void Nil::accept(ObjectVisitor &v)
{
    v.visit(*this);
}

std::string Nil::str() const
{
    return "nil";
}

ENV::ENV()
{
    parent = nullptr;
}

ENV::ENV(std::shared_ptr<ENV> parent) : parent(parent)
{
}

bool ENV::contains(const std::string &name)
{
    return objects.find(name) != objects.end();
}

void ENV::define(const std::string &name, Value value)
{
    if (contains(name))
    {
        throw std::runtime_error("Variable already defined: " + name);
    }
    objects[name] = std::make_shared<Value>(value);
}

void ENV::assign(const std::string &name, Value value)
{
    if (contains(name))
    {
        *objects[name] = value;
    }
    else if (parent != nullptr)
    {
        parent->assign(name, value);
    }
    else
    {
        throw std::runtime_error("Undefined variable: " + name);
    }
}

Value ENV::get(const std::string &name)
{
    if (objects.find(name) != objects.end())
    {
        return *objects[name];
    }
    else if (parent != nullptr)
    {
        return parent->get(name);
    }
    else
    {
        throw std::runtime_error("Undefined variable: " + name);
        return nullptr;
    }
}

std::shared_ptr<Number> Casting::cast_to_number(const Value &object)
{
    object->accept(visitor);
    if (visitor.mathces(ObjectType::NUMBER))
    {
        return std::make_shared<Number>(dynamic_cast<Number &>(*object).get_value());
    }
    else
    {
        throw std::runtime_error("Invalid cast to number");
    }
}

std::shared_ptr<String> Casting::cast_to_string(const Value &object)
{
    object->accept(visitor);
    if (visitor.mathces(ObjectType::STRING))
    {
        return std::make_shared<String>(dynamic_cast<String &>(*object).get_value());
    }
    else
    {
        throw std::runtime_error("Invalid cast to string");
    }
}

std::shared_ptr<Boolean> Casting::cast_to_boolean(const Value &object)
{
    object->accept(visitor);
    if (visitor.mathces(ObjectType::BOOLEAN))
    {
        return std::make_shared<Boolean>(dynamic_cast<Boolean &>(*object).get_value());
    }
    else
    {
        throw std::runtime_error("Invalid cast to boolean");
    }
}

std::shared_ptr<Function> Casting::cast_to_function(const Value &object)
{
    object->accept(visitor);
    if (visitor.mathces(ObjectType::FUNCTION))
    {
        return std::make_shared<Function>(dynamic_cast<Function &>(*object).args, dynamic_cast<Function &>(*object).body, dynamic_cast<Function &>(*object).env);
    }
    else
    {
        throw std::runtime_error("Invalid cast to function");
    }
}