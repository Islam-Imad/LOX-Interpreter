#include "environment.h"
#include "unordered_map"
#include <stdexcept>

std::string Environment::get_defined_error_message(const std::string &name)
{
    return "Variable : " + name + " is already defined";
}

std::string Environment::get_undefined_error_message(const std::string &name)
{
    return "Variable : " + name + " is not defined";
}

bool Environment::is_defined(const std::string &name) const
{
    if (values.find(name) != values.end())
    {
        return true;
    }
    return false;
}

void Environment::define(const std::string &name, const Value &value)
{
    if (is_defined(name))
    {
        throw std::runtime_error(get_defined_error_message(name));
    }
    values[name] = value;
}

void Environment::assign(const std::string &name, const Value &value)
{
    if (!is_defined(name))
    {
        if (parent != nullptr)
        {
            parent->assign(name, value);
            return;
        }
        throw std::runtime_error(get_undefined_error_message(name));
    }
    values[name] = value;
}

Value Environment::get(const std::string &name) const
{
    if (!is_defined(name))
    {
        if (parent != nullptr)
        {
            return parent->get(name);
        }
        throw std::runtime_error(get_undefined_error_message(name));
    }
    return values.at(name);
}

Environment::Environment() {}

Environment::Environment(Environment *parent) : parent(parent) {}