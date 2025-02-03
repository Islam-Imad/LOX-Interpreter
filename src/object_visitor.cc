#include "object_visitor.h"

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