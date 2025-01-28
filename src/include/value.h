#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <variant>
#include <stdexcept>

enum ValueType
{
    Number,
    String,
    Boolean,
    Nil
};

template <typename T>
ValueType get_type()
{
    if constexpr (std::is_same_v<T, double>)
    {
        return ValueType::Number;
    }
    else if constexpr (std::is_same_v<T, std::string>)
    {
        return ValueType::String;
    }
    else if constexpr (std::is_same_v<T, bool>)
    {
        return ValueType::Boolean;
    }
    else
    {
        return ValueType::Nil;
    }
}

class Value
{
private:
    std::variant<double, bool, std::string> value;
    ValueType valueType;

public:
    explicit Value(const double &value);
    explicit Value(const bool &value);
    explicit Value(const std::string &value);
    explicit Value();

    ValueType type() const;
    bool is_type(const ValueType &type) const;

    template <typename T>
    T get() const
    {
        if (valueType != get_type<T>())
        {
            throw std::runtime_error("Invalid type");
        }
        else if (valueType == ValueType::Nil)
        {
            throw std::runtime_error("Value is nil");
        }
        return std::get<T>(value);
    }
};

#endif // VALUE_H