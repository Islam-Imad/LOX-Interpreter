#ifndef OBJECT_VISITOR_H
#define OBJECT_VISITOR_H

class Number;
class String;
class Boolean;
class Nil;
class Function;

enum class ObjectType
{
    NUMBER,
    STRING,
    FUNCTION,
    BOOLEAN,
    NIL
};

class ObjectVisitor
{
public:
    virtual void visit(const Number &n) = 0;
    virtual void visit(const String &s) = 0;
    virtual void visit(const Boolean &b) = 0;
    virtual void visit(const Nil &n) = 0;
    virtual void visit(const Function &f) = 0;
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

#endif // OBJECT_VISITOR_H