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

namespace Chip8Compiler
{
	class Token
	{
	public:
		enum class Type
		{
			And,
			Asterisk,
			Comma,
			Comment,
			DifferentTo,
			Dot,
			DoubleQuote,
			Equal,
			EqualTo,
			EndOfFile,
			GreaterThan,
			Identifier,
			LeftCurlyBrace,
			LeftParenthesis,
			LeftShift,
			LessThan,
			LogicAnd,
			LogicNot,
			LogicOr,
			Minus,
			Modulus,
			Not,
			Number,
			Or,
			Pipe,
			Plus,
			RightCurlyBrace,
			RightParenthesis,
			RightShift,
			SemiColon,
			SingleQuote,
			Slash,
			Unknown
		};

		inline Token(const Type& type) : m_type(type), m_content("") {}
		inline Token(const Type& type, const std::string& content) : m_type(type), m_content(content) {}

		inline std::string getContent() { return m_content; }
		inline std::string getPosition()
		{
			return std::to_string(m_position.first) + ":" + std::to_string(m_position.second);
		}
		inline Type getType() { return m_type; }

		inline void setContent(const std::string& content) { m_content = content; }
		inline void setPosition(const std::pair<uint64_t, uint64_t>& potision) { m_position = potision; }
		inline void setType(const Type& type) { m_type = type; }


	private:
		std::string m_content;
		std::pair<uint64_t, uint64_t> m_position;
		Type m_type;
	};
}