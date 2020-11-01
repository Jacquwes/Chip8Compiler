#include "common.h"
#include "parser.h"

namespace Chip8Compiler
{
	std::shared_ptr<Statements::Operation> Parser::m_parseOperation(std::vector<Token> tokens, int& i)
	{
        Token token = tokens[++i];

        std::vector<Statements::Operation::OperationType> operators;
        std::vector<std::shared_ptr<Statement>> operands;

        while (token.getType() != Token::Type::SemiColon)
        {
            if (operators.size() == operands.size())
            {
                if (token.getType() == Token::Type::Identifier)
                {
                    if (tokens[i + 1].getType() == Token::Type::LeftParenthesis)
                        operands.push_back(std::shared_ptr<Statements::FunctionCall>(m_parseFunctionCall(tokens, i)));
                    else
                        operands.push_back(std::shared_ptr<Statements::VariableCall>(new Statements::VariableCall(token.getContent())));
                }
                else if (token.getType() == Token::Type::Number)
                    operands.push_back(std::shared_ptr<Statements::Number>(new Statements::Number(std::stoi(token.getContent()))));
            }
            else
            {
                using tt = Token::Type;
                using oo = Statements::Operation::OperationType;
                switch (token.getType())
                {
                case tt::Plus:
                    operators.push_back(oo::Addition);
                    break;
                case tt::And:
                    operators.push_back(oo::And);
                    break;
                case tt::Slash:
                    operators.push_back(oo::Division);
                    break;
                case tt::Modulus:
                    operators.push_back(oo::Modulus);
                    break;
                case tt::Asterisk:
                    operators.push_back(oo::Multiplication);
                    break;
                case tt::Not:
                    operators.push_back(oo::Not);
                    break;
                case tt::Pipe:
                    operators.push_back(oo::Or);
                    break;
                case tt::Minus:
                    operators.push_back(oo::Soustraction);
                    break;
                default:
                    std::string errorMessage =
                        "Unknown token \"" + token.getContent() + "\" in variable declaration at position " + token.getPosition() + ".";
                    throw std::exception(errorMessage.data());
                    break;
                }
            }
        }

        return std::shared_ptr<Statements::Operation>(new Statements::Operation(operators, operands));
	}
}