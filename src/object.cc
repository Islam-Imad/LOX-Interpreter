#include "object.h"
#include <memory>

Number::Number(double value)
{
    this->value = value;
}

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

String::String(std::string value)
{
    this->value = value;
}

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

ENV::ENV(ENV *parent)
{
    this->parent = parent;
}

bool ENV::contains(const std::string &name)
{
    return objects.find(name) != objects.end();
}

void ENV::define(const std::string &name, std::shared_ptr<Object> value)
{
    if (contains(name))
    {
        throw std::runtime_error("Variable already defined: " + name);
    }
    objects[name] = value;
}

void ENV::assign(const std::string &name, std::shared_ptr<Object> value)
{
    if (contains(name))
    {
        objects[name] = value;
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

std::shared_ptr<Object> ENV::get(const std::string &name)
{
    if (objects.find(name) != objects.end())
    {
        return objects[name];
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

double Casting::cast_to_number(const std::shared_ptr<Object> &object)
{
    object->accept(visitor);
    if (visitor.mathces(ObjectType::NUMBER))
    {
        return dynamic_cast<Number &>(*object).get_value();
    }
    else
    {
        throw std::runtime_error("Invalid cast to number");
    }
}

std::string Casting::cast_to_string(const std::shared_ptr<Object> &object)
{
    object->accept(visitor);
    if (visitor.mathces(ObjectType::STRING))
    {
        return dynamic_cast<String &>(*object).get_value();
    }
    else
    {
        throw std::runtime_error("Invalid cast to string");
    }
}

bool Casting::cast_to_boolean(const std::shared_ptr<Object> &object)
{
    object->accept(visitor);
    if (visitor.mathces(ObjectType::BOOLEAN))
    {
        return dynamic_cast<Boolean &>(*object).get_value();
    }
    else
    {
        throw std::runtime_error("Invalid cast to boolean");
    }
}
