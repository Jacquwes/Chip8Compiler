/*
    Copyright (C) 2020  Jacques

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "parser.h"

namespace Chip8Compiler
{
    Parser::Parser()
    {
        m_scope.push(ScopeType::Base);
        m_currentFunction = nullptr;
        m_currentSection = None;
    }

    AST Parser::parse(std::vector<Token>& tokens)
    {
        AST ast;

        for (int i = 0; i < tokens.size(); i++)
        {
            Token token = tokens[i];
            switch (m_scope.top())
            {
            case ScopeType::Base:
                switch (token.getType())
                {
                case Token::Type::Comment:
                    break;
                case Token::Type::Identifier:
                    if (token.getContent() == "section")
                    {
                        token = tokens[++i];
                        if (token.getContent() == "code")
                        {
                            m_currentSection = Code;
                            break;
                        }
                        else if (token.getContent() == "sprites")
                        {
                            m_currentSection = Sprites;
                            break;
                        }
                    }
                    [[fallthrough]];
                case Token::Type::LeftCurlyBrace:
                    if (i >= 2 && tokens[i - 2].getContent() == "section")
                    {
                        m_scope.push(ScopeType::Section);
                        break;
                    }
                    [[fallthrough]];
                default:
                    std::string errorMessage =
                        "Unknown token \"" + token.getContent() + "\" in base scope at position " + token.getPosition() + ".";
                    throw std::exception(errorMessage.data());
                    break;
                }
                break;
            case ScopeType::Section:
            {
                switch (m_currentSection)
                {
                case Chip8Compiler::Parser::Code: // TODO
                {


                    if (token.getContent() == "function")
                    {
                        token = tokens[++i];
                        std::string functionName;
                        if (token.getType() == Token::Type::Identifier)
                            functionName = token.getContent();
                        else
                        {
                            std::string errorMessage =
                                "Unexpected function name \"" + token.getContent() + "\" at position " + token.getPosition() + ".";
                            throw std::exception(errorMessage.data());
                        }

                        token = tokens[++i];
                        if (token.getType() != Token::Type::LeftParenthesis)
                        {
                            std::string errorMessage =
                                "Expected \"(\" but got \"" + token.getContent() + "\" at position" + token.getPosition() + ".";
                        }

                        // TODO ARGS
                        std::vector<std::string> arguments;
                        for (token = tokens[++i];
                            (token.getType() == Token::Type::Identifier || token.getType() == Token::Type::Comma) && token.getType() != Token::Type::RightParenthesis;
                            token = tokens[++i])
                            if (token.getType() == Token::Type::Identifier)
                                arguments.push_back(token.getContent());

                        m_currentFunction = std::shared_ptr<Statements::FunctionDeclaration>(new Statements::FunctionDeclaration(functionName, arguments));
                        ast.addStatement(Section::SectionType::Code, m_currentFunction);
                        m_scope.push(ScopeType::Function);
                    }



                    if (token.getContent() == "var")
                    {
                        ast.addStatement(Section::SectionType::Code, m_parseVariableDeclaration(tokens, i ));
                    }


                    break;
                }
                case Chip8Compiler::Parser::Sprites:
                    switch (token.getType())
                    {
                    case Token::Type::RightCurlyBrace:
                        m_scope.pop();
                        break;
                    case Token::Type::Identifier:
                    {
                        std::string spriteName = token.getContent();
                        if (tokens[++i].getType() == Token::Type::Equal)
                        {
                            std::vector<uint8_t> spriteData;
                            token = tokens[++i];
                            while (token.getType() != Token::Type::SemiColon && token.getType() == Token::Type::Identifier)
                            {
                                std::bitset<8> row(0);
                                for (int i = token.getContent().size() - 1, o = 0; i >= 0; i--, o++)
                                    if (token.getContent()[o] != '_')
                                        row.set(i, true);
                                spriteData.push_back(row.to_ulong());
                                token = tokens[++i];
                            }
                            ast.addStatement(Section::SectionType::Sprites, std::unique_ptr<Statements::SpriteDeclaration>(new Statements::SpriteDeclaration(spriteData, spriteName)));
                            break;
                        }
                    }
                    [[fallthrough]];
                    default:
                    case Token::Type::Comment:
                        break;
                        std::string errorMessage =
                            "Unknown token \"" + token.getContent() + "\" in sprites section scope at position " + token.getPosition() + ".";
                        throw std::exception(errorMessage.data());
                        break;
                    }
                    break;
                case Chip8Compiler::Parser::None: // TODO error msg
                default:
                    std::string errorMessage =
                        "Unknown token \"" + token.getContent() + "\" in section scope at position " + token.getPosition() + ".";
                    throw std::exception(errorMessage.data());
                    break;
                }
                break;
            }



            case ScopeType::Function:   // TODO
                                        // ONLY FUNCTION EXIT DONE
            {
                switch (token.getType())
                {
                case Token::Type::Identifier:
                {
                    if (token.getContent() == "var")
                        m_currentFunction->statements.push_back(m_parseVariableDeclaration(tokens, i));
                }
                case Token::Type::RightCurlyBrace:
                {
                    m_scope.pop();
                    if (m_scope.top() != ScopeType::Function)
                        m_currentFunction = nullptr;
                    break;
                }
                default:
                    break;
                }

                break;
            }
            case ScopeType::Loop:
                break;
            }
        }

        return ast;
    }
}