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

#pragma once

#include "common.h"
#include "abstractsyntaxtree.h"

namespace Chip8Compiler
{
	namespace Statements
	{
		class Function : public Statement
		{
		public:
			Function(const std::string& name_, const std::vector<std::string>& arguments_)
				: arguments(arguments_)
				, name(name_)
				, Statement(Type::Function)
			{}

			std::vector<std::string> arguments;
			std::string name;
			std::vector<Statement*> statements;
		};

		class Operation : public Statement
		{
		public:
			enum class OperationType
			{
				Addition,
				And,
				Division,
				LogicAnd,
				LogicNot,
				LogicOr,
				Multiplication,
				Not,
				Or,
				Soustraction,
			};

			Operation(const OperationType& type) : Statement(Type::Operation), operationType(type) {}

			std::pair<int16_t, int16_t> operands;
			OperationType operationType;
		};

		class SpriteDeclaration : public Statement
		{
		public:
			SpriteDeclaration(const std::vector<uint8_t>& data_, const std::string& name_)
				: Statement(Type::SpriteDeclaration)
				, data(data_)
				, name(name_)
			{}

			std::vector<uint8_t> data;
			std::string name;
		};

		class VariableDeclaration : public Statement
		{
		public:
			VariableDeclaration(const std::string& name_, const uint16_t& value_)
				: name(name_)
				, value(value_)
				, Statement(Type::VariableDeclaration)
			{}

			std::string name;
			uint16_t value;
		};
	}
}
