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

std::shared_ptr<Object> Function::call(std::vector<std::shared_ptr<Object>> args)
{
    ENV nested_env(&this->env);
    for (size_t i = 0; i < args.size(); i++)
    {
        nested_env.define(this->args[i], std::move(args[i]));
    }
    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());
    Interpreter interpreter(std::move(operation_executor), nested_env);

    try
    {
        body->accept(interpreter);
    }
    catch (const ReturnException &e)
    {
        return e.get_value();
    }
    return std::make_shared<Nil>();
}