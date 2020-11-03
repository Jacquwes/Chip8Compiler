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

#include "abstractsyntaxtree.h"
#include "common.h"

namespace Chip8Compiler
{
	namespace Statements
	{
		class Operation;

		class FunctionCall : public Statement
		{
		public:
			FunctionCall(const std::string& functionName_, const std::vector<std::shared_ptr<Operation>>& arguments_)
				: arguments(arguments_)
				, functionName(functionName_)
				, Statement(Type::FunctionCall)
			{}

			std::vector<std::shared_ptr<Operation>> arguments;
			std::string functionName;
		};

		class FunctionDeclaration : public Statement
		{
		public:
			FunctionDeclaration(const std::string& name_, const std::vector<std::string>& arguments_)
				: arguments(arguments_)
				, name(name_)
				, Statement(Type::FunctionDeclaration)
			{}

			std::vector<std::string> arguments;
			std::string name;
			std::vector<Statement*> statements;
		};

		class Number : public Statement
		{
		public:
			Number(const int16_t& value_)
				: value(value_)
				, Statement(Type::Number)
			{}

			int16_t value;
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
				Modulus,
				Multiplication,
				Not,
				Or,
				Soustraction,
			};

			Operation(std::vector<OperationType> operators_, const std::vector<std::shared_ptr<Statement>>& operands_)
				: operators(operators_)
				, operands(operands_)
				, Statement(Type::Operation)
			{}

			std::vector<OperationType> operators;
			std::vector<std::shared_ptr<Statement>> operands;
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

		class VariableCall : public Statement
		{
		public:
			VariableCall(const std::string& name_)
				: name(name_)
				, Statement(Type::VariableCall)
			{}

			std::string name;
		};

		class VariableDeclaration : public Statement
		{
		public:
			VariableDeclaration(const std::string& name_, const std::shared_ptr<Operation>& value_)
				: name(name_)
				, value(value_)
				, Statement(Type::VariableDeclaration)
			{}

			std::string name;
			std::shared_ptr<Operation> value;
		};
	}
}
