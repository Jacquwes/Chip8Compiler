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

#include "lexer.h"

namespace Chip8Compiler
{
	Lexer::CharacterType Lexer::getCharacterType(const char& c)
	{
		CharacterType characterType = Unknown;

		if (c == 0)
			characterType = EndOfFile;
		else if (
			c == ' ' ||
			c == '\n' ||
			c == '\r' ||
			c == '\t'
			) characterType = Blank;
		else if (
			c == '!' ||
			c == '"' ||
			(c >= '%' && c <= '/') ||
			(c >= ';' && c <= '>') ||
			(c >= '{' && c <= '~')
			) characterType = Symbol;
		else if (c >= '0' && c <= '9')
			characterType = Digit;
		else if (
			(c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') ||
			c == '_'
			) characterType = Identifier;

		return characterType;
	}

	Token Lexer::getNumber()
	{
		std::string number;
		while (getCharacterType(get()) == CharacterType::Digit)
			number.push_back(get(true));
		Token token(Token::Type::Number, number);
		token.setPosition(m_position);
		return token;
	}

	Token Lexer::getIdentifier()
	{
		std::string identifier;
		while (getCharacterType(get()) == CharacterType::Identifier || getCharacterType(get()) == CharacterType::Digit)
			identifier.push_back(get(true));
		Token token(Token::Type::Identifier, identifier);
		token.setPosition(m_position);
		return token;
	}

	Token Lexer::getSymbol()
	{
		std::string symbol;
		char symbol_ = get(true);
		symbol.push_back(symbol_);
		if ((symbol_ == '&' ||
			symbol_ == '+' ||
			symbol_ == '|' ||
			symbol_ == '<' ||
			symbol_ == '>' ||
			symbol_ == '-' ||
			symbol_ == '=' ||
			symbol_ == '!') &&
			symbol.size() <= 2
			)
		{
			char secondCharacter = get();
			if (secondCharacter == '&' ||
				secondCharacter == '+' ||
				secondCharacter == '|' ||
				secondCharacter == '<' ||
				secondCharacter == '>' ||
				secondCharacter == '-' ||
				secondCharacter == '='
				) symbol.push_back(get(true));
		}

		Token::Type t = Token::Type::Unknown;

		using tt = Token::Type;
		if (symbol.size() == 1)
		{
			switch (symbol[0])
			{
			case '&':
				t = tt::And;
				break;
			case ',':
				t = tt::Comma;
				break;
			case '.':
				t = tt::Dot;
				break;
			case '"':
				t = tt::DoubleQuote;
				break;
			case '=':
				t = tt::Equal;
				break;
			case '{':
				t = tt::LeftCurlyBrace;
				break;
			case '(':
				t = tt::LeftParenthesis;
				break;
			case '<':
				t = tt::LeftShift;
				break;
			case '!':
				t = tt::LogicNot;
				break;
			case '-':
				t = tt::Minus;
				break;
			case '%':
				t = tt::Modulus;
				break;
			case '~':
				t = tt::Not;
				break;
			case '|':
				t = tt::Or;
				break;
			case '+':
				t = tt::Plus;
				break;
			case '}':
				t = tt::RightCurlyBrace;
				break;
			case ')':
				t = tt::RightParenthesis;
				break;
			case '>':
				t = tt::RightShift;
				break;
			case ';':
				t = tt::SemiColon;
				break;
			case '\'':
				t = tt::SingleQuote;
				break;
			case '/':
				if (get() == '/')
				{
					symbol = "";
					t = tt::Comment;
					while (get() != '\n')
						get(true);
				}
				else
					t = tt::Slash;
			}
		}
		else
		{
			if (symbol == "==")
				t = tt::EqualTo;
			else if (symbol == ">=")
				t = tt::GreaterThan;
			else if (symbol == "<=")
				t = tt::LessThan;
			else if (symbol == "&&")
				t = tt::LogicAnd;
			else if (symbol == "||")
				t = tt::LogicOr;
		}

		Token token(t, symbol);
		token.setPosition(m_position);
		return token;
	}

	Token Chip8Compiler::Lexer::next()
	{
		while (getCharacterType(get()) == Blank)
			get(true);

		CharacterType characterType = getCharacterType(get());

		switch (characterType)
		{
		case Chip8Compiler::Lexer::Digit:
		{
			bool isNumber = true;
			for (int i = 1; getCharacterType(getNext(i)) == Digit || getCharacterType(getNext(i)) == Identifier; i++)
				if (getCharacterType(getNext(i)) == Identifier)
					return getIdentifier();
			return getNumber();
		}
		case Chip8Compiler::Lexer::Identifier:
			return getIdentifier();
		case Chip8Compiler::Lexer::Symbol:
			return getSymbol();
		case Chip8Compiler::Lexer::EndOfFile:
			return Token(Token::Type::EndOfFile);
		case Chip8Compiler::Lexer::Unknown:
		default:
			Token token(Token::Type::Unknown, std::string(1, get(true)));
			token.setPosition(m_position);
			return token;
		}
	}
}