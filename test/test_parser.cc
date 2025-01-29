#include <gtest/gtest.h>
#include "parser.h"
#include "expression.h"
#include "token.h"
#include "value.h"
#include "scanner.h"

TEST(Parser, Expression)
{
    std::vector<Token> tokens;
    TokenUtilites token_utilites;
    std::string source = "1 + 2";
    tokens.push_back(Token(NUMBER, 1, 0, 1));
    tokens.push_back(Token(PLUS, 1, 2, 1));
    tokens.push_back(Token(NUMBER, 1, 4, 1));
    Parser parser(tokens, token_utilites, source);
    std::unique_ptr<Expression> expression = parser.expression();
    OperatorFactory factory = OperatorFactory();
    
    OperationExecutor operation_executor = OperationExecutor(factory);
    ExpressionEvaluator evaluator(std::move(operation_executor));
    expression->accept(evaluator);
    
    Value result = evaluator.get_result();
    ASSERT_EQ(result.get<double>(), 3);
}