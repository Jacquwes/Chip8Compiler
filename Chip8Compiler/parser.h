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
#include "statements.h"
#include "token.h"

namespace Chip8Compiler
{
	class Parser
	{
	public:
		Parser();

		AST parse(std::vector<Token>& tokens);

	private:
		enum class ScopeType
		{
			Base,
			Section,
			Function,
			Loop,
		};
		std::stack<ScopeType> m_scope;

		enum
		{
			Code,
			None,
			Sprites,
		} m_currentSection;

		Statements::Function* m_currentFunction;
	};
}