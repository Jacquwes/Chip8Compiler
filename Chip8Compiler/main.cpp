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

#include "common.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char** argv)
{


	std::cout
		<< "Chip8Compiler  Copyright (C) 2020  Jacques" << std::endl
		<< "This program comes with ABSOLUTELY NO WARRANTY." << std::endl
		<< "This is free software, and you are welcome to redistribute it" << std::endl
		<< "under certain conditions. Read license for more details." << std::endl << std::endl;


	bool error = false;

	std::string program;

	std::ifstream file("main.c8");
	for (char temp; file.read(&temp, sizeof(temp));)
		program.push_back(temp);


	Chip8Compiler::Lexer lexer(program);
	std::vector<Chip8Compiler::Token> tokens;

	std::cout << "Starting lexer." << std::endl;
	
	for (Chip8Compiler::Token token = lexer.next();
		token.getType() != Chip8Compiler::Token::Type::EndOfFile;
		token = lexer.next())
	{
		if (token.getType() == Chip8Compiler::Token::Type::Unknown)
		{
			error = true;
			std::cout << "Unknown token \"" << token.getContent() << "\" at position " << lexer.position().first << ":" << lexer.position().second << "." << std::endl;
		}
		else if (!error)
			tokens.push_back(token);
	}

	if (!error)
		std::cout << "Lexer returned no error." << std::endl;
	else
	{
		std::cout << "Lexer returned an error." << std::endl;
		return 1;
	}

	std::cout << "Starting parser." << std::endl;


	Chip8Compiler::Parser parser;
	Chip8Compiler::AST ast;
	try
	{
		ast = parser.parse(tokens);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	std::vector<Chip8Compiler::Statements::SpriteDeclaration*> sprites;
	std::vector<Chip8Compiler::Statements::FunctionDeclaration*> functions;
	std::vector<Chip8Compiler::Statements::VariableDeclaration*> variables;

	for (auto& section : ast.getSections())
		for (auto& instruction : section->instructions)
			if (instruction->getType() == Chip8Compiler::Statement::Type::FunctionDeclaration)
				functions.push_back((Chip8Compiler::Statements::FunctionDeclaration*)instruction.get());
			else if (instruction->getType() == Chip8Compiler::Statement::Type::SpriteDeclaration)
				sprites.push_back((Chip8Compiler::Statements::SpriteDeclaration*)instruction.get());
			else if (instruction->getType() == Chip8Compiler::Statement::Type::VariableDeclaration)
				variables.push_back((Chip8Compiler::Statements::VariableDeclaration*)instruction.get());

	std::cout << "Parser returned no error." << std::endl;
}