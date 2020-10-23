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
	class Lexer
	{
	public:
		inline Lexer(const std::string& program) : m_program(program), m_programCounter(0) {}

		enum CharacterType
		{
			Unknown,
			Blank,
			Digit,
			Identifier,
			Symbol,
			EndOfFile
		};
		static CharacterType getCharacterType(const char& character);

		Token next();
		inline const std::pair<uint64_t, uint64_t>& position() { return m_position; }
	private:
		std::string m_program;
		uint64_t m_programCounter;

		std::pair<uint64_t, uint64_t> m_position;

		inline char get(bool increment = false)
		{
			if (increment)
			{
				if (m_program[m_programCounter] == '\n')
				{
					++m_position.second;
					m_position.first = 1;
				}
				else
					++m_position.first;
			}
			return m_program[increment ? m_programCounter++ : m_programCounter]; 
		}
		inline char getLast() { return m_program[m_programCounter - 1]; }
		inline char getNext(int index = 1) { return m_program[m_programCounter + index]; }

		Token getIdentifier();
		Token getNumber();
		Token getSymbol();
	};
}