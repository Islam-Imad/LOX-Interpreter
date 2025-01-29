#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <gtest/gtest.h>
#include "interpreter.h"
#include "expression.h"
#include "operator_strategy.h"
#include "token.h"
#include "value.h"
#include "statement.h"
#include "parser.h"
#include "scanner.h"

TEST(Interpreter, TestInterpreter)
{
    std::string source = "print true;";

    TokenUtilites tu;

    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    int n = tokens.size();
    for (int i = 0; i < n; ++i)
    {
        std::cout << tu.token_type_to_string(tokens[i].get_type()) << ' ' << tokens[i].get_offset() << std::endl;
    }
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();

    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());
    ExpressionEvaluator expression_evaluator(std::move(operation_executor));

    Interpreter interpreter(std::move(expression_evaluator));
    interpreter.interpret(statements);
}
