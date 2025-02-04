#ifndef FUNCTIOON_H
#define FUNCTIOON_H

#include "object.h"
#include "object_visitor.h"
#include "interpreter.h"
#include "statement.h"
#include <vector>
#include <memory>
#include <exception>

class Function : public Callable
{
public:
    std::vector<std::string> args;
    std::shared_ptr<const Statement> body;
    Function(std::vector<std::string> args, std::shared_ptr<const Statement> body, ENV env);
    void accept(ObjectVisitor &v) override;
    std::shared_ptr<Object> call(std::vector<std::shared_ptr<Object>> args) override;
    std::string str() const override;
    int get_arity() const override;
};

class ReturnException : public std::exception
{
private:
    std::shared_ptr<Object> value;

public:
    ReturnException(std::shared_ptr<Object> value) : value(value) {}
    const char *what() const noexcept override { 
        std::string msg = "Return: " + value->str();
        return msg.c_str();
    }
    std::shared_ptr<Object> get_value() const { return value; }
};

#endif // FUNCTIOON_H