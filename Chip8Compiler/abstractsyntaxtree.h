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
#include "token.h"

namespace Chip8Compiler
{
	class Statement
	{
	public:
		enum class Type
		{
			Function,
			Operation,
			Section,
			SpriteDeclaration,
			VariableDeclaration,
		};

		Statement(const Type& type) : m_type(type) {}

		Type getType() { return m_type; }

	private:
		Type m_type;
	};

	class Section
	{
	public:
		enum class SectionType
		{
			Code,
			Sprites,
		};

		Section(const SectionType& type) : sectionType(type) {}

		SectionType sectionType;
		std::vector<Statement*> instructions;
	};

	class AST
	{
	public:
		inline AST()
		{
			m_sections.push_back(new Section(Section::SectionType::Code));
			m_sections.push_back(new Section(Section::SectionType::Sprites));
		}

		inline void addStatement(const Section::SectionType& section, Statement* statement)
		{
			m_sections[static_cast<size_t>(section)]->instructions.push_back(statement);
		}

		inline std::vector<Section*> getSections() { return m_sections; }

	private:
		std::vector<Section*> m_sections;
	};
}