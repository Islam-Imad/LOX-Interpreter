#include "function.h"
#include "object_visitor.h"
#include <memory>

Function::Function(std::vector<std::string> args, std::shared_ptr<Statement> body, ENV env)
{
    this->args = args;
    this->body = body;
    this->env = env;
    arity = args.size();
}

void Function::accept(ObjectVisitor &v)
{
    v.visit(*this);
}

int Function::get_arity() const
{
    return arity;
}

std::string Function::str() const
{
    return "Function";
}

ENV Function::call(std::vector<std::shared_ptr<Object>> args)
{
    if (args.size() != this->args.size())
    {
        throw std::runtime_error("Invalid number of arguments");
    }
    ENV nested_env(&this->env);
    for (size_t i = 0; i < args.size(); i++)
    {
        nested_env.define(this->args[i], std::move(args[i]));
    }
    return nested_env;
}