#ifndef FUNCTIOON_H
#define FUNCTIOON_H

#include "object.h"
#include "object_visitor.h"
#include "statement.h"
#include <vector>
#include <memory>

class Function : public Callable
{
public:
    std::vector<std::string> args;
    std::shared_ptr<Statement> body;
    Function(std::vector<std::string> args, std::shared_ptr<Statement> body, ENV env);
    void accept(ObjectVisitor &v) override;
    ENV call(std::vector<std::shared_ptr<Object>> args) override;
    std::string str() const override;
    int get_arity() const override;
};

#endif // FUNCTIOON_H