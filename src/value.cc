// #include "value.h"
// #include <stdexcept>
// #include <string>
// #include <variant>

// Value::Value(const double &value) : value(value), valueType(ValueType::Number) {}
// Value::Value(const std::string &value) : value(value), valueType(ValueType::String) {}
// Value::Value(const bool &value) : value(value), valueType(ValueType::Boolean) {}
// Value::Value() : value(), valueType(ValueType::Nil) {}

// ValueType Value::type() const
// {
//     return valueType;
// }

// bool Value::is_type(const ValueType &type) const
// {
//     return valueType == type;
// }

// std::string Value::to_string() const
// {
//     switch (valueType)
//     {
//     case ValueType::Number:
//         return std::to_string(std::get<double>(value));
//     case ValueType::String:
//         return std::get<std::string>(value);
//     case ValueType::Boolean:
//         return std::get<bool>(value) ? "true" : "false";
//     case ValueType::Nil:
//         return "nil";
//     default:
//         throw std::runtime_error("Invalid type");
//     }
// }