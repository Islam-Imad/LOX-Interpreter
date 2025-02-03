#include "object.h"
#include <memory>

namespace OBJ
{

    Number::Number(double value)
    {
        this->value = value;
    }

    void Number::accept(ObjectVisitor &v)
    {
        v.visit(*this);
    }

    double Number::get_value() const
    {
        return value;
    }

    std::string Number::str() const
    {
        return std::to_string(value);
    }

    String::String(std::string value)
    {
        this->value = value;
    }

    void String::accept(ObjectVisitor &v)
    {
        v.visit(*this);
    }

    std::string String::get_value() const
    {
        return value;
    }

    std::string String::str() const
    {
        return value;
    }

    Boolean::Boolean(bool value)
    {
        this->value = value;
    }

    void Boolean::accept(ObjectVisitor &v)
    {
        v.visit(*this);
    }

    bool Boolean::get_value() const
    {
        return value;
    }

    std::string Boolean::str() const
    {
        return value ? "true" : "false";
    }

    Nil::Nil()
    {
    }

    void Nil::accept(ObjectVisitor &v)
    {
        v.visit(*this);
    }

    std::string Nil::str() const
    {
        return "nil";
    }

    ENV::ENV()
    {
        parent = nullptr;
    }

    ENV::ENV(ENV *parent)
    {
        this->parent = parent;
    }

    bool ENV::contains(const std::string &name)
    {
        return objects.find(name) != objects.end();
    }

    void ENV::define(const std::string &name, std::shared_ptr<OBJ::Object> value)
    {
        if (contains(name))
        {
            throw std::runtime_error("Variable already defined: " + name);
        }
        objects[name] = std::make_shared<std::shared_ptr<OBJ::Object>>(value);
    }

    void ENV::assign(const std::string &name, std::shared_ptr<OBJ::Object> value)
    {
        if (contains(name))
        {
            *objects[name] = std::move(value);
        }
        else if (parent != nullptr)
        {
            parent->assign(name, std::move(value));
        }
        else
        {
            throw std::runtime_error("Undefined variable: " + name);
        }
    }

    std::shared_ptr<std::shared_ptr<OBJ::Object>> ENV::get(const std::string &name)
    {
        if (objects.find(name) != objects.end())
        {
            return objects[name];
        }
        else if (parent != nullptr)
        {
            return parent->get(name);
        }
        else
        {
            throw std::runtime_error("Undefined variable: " + name);
            return nullptr;
        }
    }

    Function::Function(std::vector<std::string> args, std::shared_ptr<int> body, ENV env)
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

    void TypeCheckVisitor::visit(const Number &n)
    {
        type = ObjectType::NUMBER;
    }

    void TypeCheckVisitor::visit(const String &s)
    {
        type = ObjectType::STRING;
    }

    void TypeCheckVisitor::visit(const Function &f)
    {
        type = ObjectType::FUNCTION;
    }

    void TypeCheckVisitor::visit(const Boolean &b)
    {
        type = ObjectType::BOOLEAN;
    }

    void TypeCheckVisitor::visit(const Nil &n)
    {
        type = ObjectType::NIL;
    }

    ObjectType TypeCheckVisitor::get_type() const
    {
        return type;
    }

    bool TypeCheckVisitor::mathces(ObjectType type) const
    {
        return this->type == type;
    }

    double Casting::cast_to_number(const std::shared_ptr<Object> &object)
    {
        object->accept(visitor);
        if (visitor.mathces(ObjectType::NUMBER))
        {
            return dynamic_cast<Number &>(*object).get_value();
        }
        else
        {
            throw std::runtime_error("Invalid cast to number");
        }
    }

    std::string Casting::cast_to_string(const std::shared_ptr<Object> &object)
    {
        object->accept(visitor);
        if (visitor.mathces(ObjectType::STRING))
        {
            return dynamic_cast<String &>(*object).get_value();
        }
        else
        {
            throw std::runtime_error("Invalid cast to string");
        }
    }

    bool Casting::cast_to_boolean(const std::shared_ptr<Object> &object)
    {
        object->accept(visitor);
        if (visitor.mathces(ObjectType::BOOLEAN))
        {
            return dynamic_cast<Boolean &>(*object).get_value();
        }
        else
        {
            throw std::runtime_error("Invalid cast to boolean");
        }
    }

} // namespace OBJ