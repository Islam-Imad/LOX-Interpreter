#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "object_visitor.h"

class Object;
class ENV;

class Object
{
public:
    virtual void accept(ObjectVisitor &v) = 0;
    virtual std::string str() const = 0;
};

class ENV
{
private:
    std::unordered_map<std::string, std::shared_ptr<Object>> objects;
    ENV *parent;

public:
    ENV();
    ENV(ENV *parent);
    bool contains(const std::string &name);
    void define(const std::string &name, std::shared_ptr<Object> value);
    void assign(const std::string &name, std::shared_ptr<Object> value);
    std::shared_ptr<Object> get(const std::string &name);
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
    virtual std::shared_ptr<Object> call(std::vector<std::shared_ptr<Object>> args) = 0;
    void accept(ObjectVisitor &v) override = 0;
    virtual int get_arity() const = 0;
};

class Casting
{
    TypeCheckVisitor visitor;

public:
    double cast_to_number(const std::shared_ptr<Object> &object);
    std::string cast_to_string(const std::shared_ptr<Object> &object);
    bool cast_to_boolean(const std::shared_ptr<Object> &object);
    Function cast_to_function(const std::shared_ptr<Object> &object);
};

#endif