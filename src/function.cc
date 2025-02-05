#include "function.h"
#include "object_visitor.h"
#include "interpreter.h"
#include "operator_strategy.h"
#include <memory>

Function::Function(std::vector<std::string> args, std::shared_ptr<const Statement> body, ENV env)
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

std::shared_ptr<Object> Function::call(std::vector<std::shared_ptr<Object>> args, Interpreter &interpreter)
{
    if (senv == nullptr)
    {
        senv = std::make_shared<ENV>(env);
    }
    std::shared_ptr<ENV> nested_env = senv;
    for (size_t i = 0; i < args.size(); i++)
    {
        nested_env->define(this->args[i], std::move(args[i]));
    }
    std::shared_ptr<ENV> new_environment = nested_env;
    std::shared_ptr<ENV> old_environment = interpreter.environment;
    interpreter.environment = new_environment;

    try
    {
        body->accept(interpreter);
    }
    catch (const ReturnException &e)
    {
        interpreter.environment = old_environment;
        return e.get_value();
    }
    interpreter.environment = old_environment;
    return std::make_shared<Nil>();
}