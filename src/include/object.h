#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>


namespace OBJ
{

    class Object;
    class Number;
    class String;
    class Boolean;
    class Nil;
    class Callable;
    class Function;
    class ObjectVisitor;
    class ENV;
    class TypeCheckVisitor;

    enum class ObjectType
    {
        NUMBER,
        STRING,
        FUNCTION,
        BOOLEAN,
        NIL
    };

    class Object
    {
    public:
        virtual void accept(ObjectVisitor &v) = 0;
        virtual std::string str() const = 0;
    };

    class ENV
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<std::shared_ptr<OBJ::Object>>> objects;
        ENV *parent;

    public:
        ENV();
        ENV(ENV *parent);
        bool contains(const std::string &name);
        void define(const std::string &name, std::shared_ptr<OBJ::Object> value);
        void assign(const std::string &name, std::shared_ptr<OBJ::Object> value);
        std::shared_ptr<std::shared_ptr<OBJ::Object>> get(const std::string &name);
    };

    class ObjectVisitor
    {
    public:
        virtual void visit(const Number &n) = 0;
        virtual void visit(const String &s) = 0;
        virtual void visit(const Function &f) = 0;
        virtual void visit(const Boolean &b) = 0;
        virtual void visit(const Nil &n) = 0;
    };

    class Number : public Object
    {
    private:
        double value;

    public:
        Number(double value);
        void accept(ObjectVisitor &v) override;
        double get_value() const;
        std::string str() const override;
    };

    class String : public Object
    {
    private:
        std::string value;

    public:
        String(std::string value);
        void accept(ObjectVisitor &v) override;
        std::string get_value() const;
        std::string str() const override;
    };

    class Boolean : public Object
    {
    private:
        bool value;

    public:
        Boolean(bool value);
        void accept(ObjectVisitor &v) override;
        bool get_value() const;
        std::string str() const override;
    };

    class Nil : public Object
    {
    public:
        Nil();
        void accept(ObjectVisitor &v) override;
        std::string str() const override;
    };

    class Callable : public Object
    {
    public:
        ENV env;
        int arity;
        virtual ENV call(std::vector<std::shared_ptr<Object>> args) = 0;
        void accept(ObjectVisitor &v) override = 0;
        virtual int get_arity() const = 0;
    };

    class Function : public Callable
    {
    public:
        std::vector<std::string> args;
        std::shared_ptr<int> body;
        Function(std::vector<std::string> args, std::shared_ptr<int> body, ENV env);
        void accept(ObjectVisitor &v) override;
        ENV call(std::vector<std::shared_ptr<Object>> args) override;
        std::string str() const override;
        int get_arity() const override;
    };

    class TypeCheckVisitor : public ObjectVisitor
    {
    private:
        ObjectType type;

    public:
        void visit(const Number &n) override;
        void visit(const String &s) override;
        void visit(const Function &f) override;
        void visit(const Boolean &b) override;
        void visit(const Nil &n) override;
        ObjectType get_type() const;
        bool mathces(ObjectType type) const;
    };

    class Casting
    {
        TypeCheckVisitor visitor;

    public:
        double cast_to_number(const std::shared_ptr<Object> &object);
        std::string cast_to_string(const std::shared_ptr<Object> &object);
        bool cast_to_boolean(const std::shared_ptr<Object> &object);
    };
}; // namespace object;
#endif