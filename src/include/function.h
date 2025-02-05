#ifndef FUNCTIOON_H
#define FUNCTIOON_H

#include "object.h"
#include "object_visitor.h"
#include "interpreter.h"
#include "statement.h"
#include <vector>
#include <memory>
#include <exception>

class Callable : public Object
{
public:
    ENV env;
    int arity;
    virtual std::shared_ptr<Object> call(std::vector<std::shared_ptr<Object>> args, Interpreter &interpreter) = 0;
    void accept(ObjectVisitor &v) override = 0;
    virtual int get_arity() const = 0;
    std::shared_ptr<ENV> senv = nullptr;
};

class Function : public Callable
{
public:
    std::vector<std::string> args;
    std::shared_ptr<const Statement> body;
    Function(std::vector<std::string> args, std::shared_ptr<const Statement> body, ENV environment);
    void accept(ObjectVisitor &v) override;
    Value call(std::vector<Value> args, Interpreter &interpreter) override;
    std::string str() const override;
    int get_arity() const override;
};

class ReturnException : public std::exception
{
private:
    Value value;

public:
    ReturnException(Value value) : value(value) {}
    const char *what() const noexcept override
    {
        std::string msg = "Return: " + value->str();
        return msg.c_str();
    }
    Value get_value() const { return value; }
};

#endif // FUNCTIOON_H