#include "value.h"
#include <stdexcept>
#include <string>
#include <variant>

Value::Value(const double &value) : value(value), valueType(ValueType::Number) {}
Value::Value(const std::string &value) : value(value), valueType(ValueType::String) {}
Value::Value(const bool &value) : value(value), valueType(ValueType::Boolean) {}
Value::Value() : value(), valueType(ValueType::Nil) {}

ValueType Value::type() const
{
    return valueType;
}

bool Value::is_type(const ValueType &type) const
{
    return valueType == type;
}
