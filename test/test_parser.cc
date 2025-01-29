#include <gtest/gtest.h>
#include "parser.h"
#include "expression.h"
#include "token.h"
#include "value.h"
#include "scanner.h"

TEST(Parser, Test_01)
{
    std::vector<Token> tokens;
    TokenUtilites token_utilites;
    std::string source = "1 + 2";
    tokens.push_back(Token(NUMBER, 1, 0, 1));
    tokens.push_back(Token(PLUS, 1, 2, 1));
    tokens.push_back(Token(NUMBER, 1, 4, 1));
    Parser parser(tokens, token_utilites, source);
    std::unique_ptr<Expression> expression = parser.expression();

    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());
    ExpressionEvaluator evaluator(std::move(operation_executor));
    expression->accept(evaluator);

    Value result = evaluator.get_result();
    ASSERT_EQ(result.get<double>(), 3);
}

TEST(Parser, Test_02)
{
    std::vector<Token> tokens;
    TokenUtilites token_utilites;
    std::string source = "1 + 2 * 3 ** 2";
    tokens.push_back(Token(NUMBER, 1, 0, 1));
    tokens.push_back(Token(PLUS, 1, 2, 1));
    tokens.push_back(Token(NUMBER, 1, 4, 1));

    tokens.push_back(Token(STAR, 1, 6, 1));
    tokens.push_back(Token(NUMBER, 1, 8, 1));
    tokens.push_back(Token(STAR_STAR, 1, 10, 2));
    tokens.push_back(Token(NUMBER, 1, 13, 1));

    Parser parser(tokens, token_utilites, source);
    std::unique_ptr<Expression> expression = parser.expression();

    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());
    ExpressionPrinter printer;
    ExpressionEvaluator evaluator(std::move(operation_executor));
    expression->accept(evaluator);
    expression->accept(printer);
    std::cout << printer.get_result() << '\n';

    Value result = evaluator.get_result();
    ASSERT_EQ(result.get<double>(), 19);
}

TEST(Parser, Test_03)
{
    std::vector<Token> tokens;
    TokenUtilites token_utilites;
    std::string source = "true or false";
    tokens.push_back(Token(BOOLEAN, 1, 0, 4));
    tokens.push_back(Token(OR, 1, 5, 2));
    tokens.push_back(Token(BOOLEAN, 1, 8, 5));

    Parser parser(tokens, token_utilites, source);
    std::unique_ptr<Expression> expression = parser.expression();

    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());
    ExpressionPrinter printer;
    ExpressionEvaluator evaluator(std::move(operation_executor));
    expression->accept(evaluator);
    expression->accept(printer);
    // std::cout << printer.get_result() << '\n';

    Value result = evaluator.get_result();
    ASSERT_EQ(result.get<bool>(), true);
}