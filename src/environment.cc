#include "environment.h"
#include "unordered_map"
#include <stdexcept>

std::string Environment::get_defined_error_message(const std::string &name) const
{
    return "Variable : " + name + " is already defined";
}

std::string Environment::get_undefined_error_message(const std::string &name) const
{
    return "Variable : " + name + " is not defined";
}

bool Environment::is_defined(const std::string &name) const
{
    return values.find(name) != values.end();
}

void Environment::define(const std::string &name, const Value &value)
{
    if(is_defined(name))
    {
        throw std::runtime_error(get_defined_error_message(name));
    }
    values[name] = value;
}

void Environment::assign(const std::string &name, const Value &value)
{
    if(!is_defined(name))
    {
        throw std::runtime_error(get_undefined_error_message(name));
    }
    values[name] = value;
}

Value Environment::get(const std::string &name) const
{
    if(!is_defined(name))
    {
        throw std::runtime_error(get_undefined_error_message(name));
    }
    return values.at(name);
}