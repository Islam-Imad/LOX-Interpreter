#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <unordered_map>
#include <string>
#include <value.h>

class Environment
{
private:
    Environment *parent = nullptr;
    std::unordered_map<std::string, Value> values;
    static std::string get_defined_error_message(const std::string &name);
    static std::string get_undefined_error_message(const std::string &name);
public:
    Environment();
    Environment(Environment *parent);
    void define(const std::string &name, const Value &value);
    void assign(const std::string &name, const Value &value);
    Value get(const std::string &name) const;
    bool is_defined(const std::string &name) const;
};

#endif // ENVIRONMENT_H