#include <iostream>
#include <string>
#include <fstream>
#include "version.h"
#include "scanner.h"
#include "parser.h"
#include "interpreter.h"
#include "expression.h"
#include "operator_strategy.h"

std::string read_file(const std::string &file_path)
{
    std::string sorce_code = "";
    std::ifstream file(file_path);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            sorce_code += line + '\n';
        }
        file.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file");
    }
    return sorce_code;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <source file>" << std::endl;
        return 1;
    }
    else if (argc > 2)
    {
        std::cerr << "Usage: " << argv[0] << " <source file>" << std::endl;
        return 1;
    }
    std::string source = read_file(argv[1]);
    TokenUtilites tu;
    Scanner scanner(source, tu);
    std::vector<Token> tokens = scanner.scan();
    // for(auto token : tokens)
    // {
    //     std::cout << tu.token_type_to_string(token.get_type()) << " " << token.get_line() << " " << token.get_start() << " " << token.get_offset() << std::endl;
    // }
    Parser parser(tokens, tu, source);
    std::vector<std::unique_ptr<Statement>> statements = parser.parse();
    OperationExecutor operation_executor = OperationExecutor(OperatorFactory());
    Interpreter interpreter(std::move(operation_executor));
    interpreter.interpret(statements);
    return 0;
}