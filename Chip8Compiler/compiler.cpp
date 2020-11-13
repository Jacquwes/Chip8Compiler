#include "compiler.h"

namespace Chip8Compiler
{
	const std::vector<uint8_t>& Compiler::compile(AST ast)
	{
		for (auto& section : ast.getSections())
		{
			switch (section->sectionType)
			{
			case Section::SectionType::Code:
			{
				for (auto& instruction : section->instructions)
				{
					switch (instruction->getType())
					{
					case Statement::Type::VariableDeclaration:
					{
						auto variable = as<Statements::VariableDeclaration>(instruction);
						if (m_globalVariables.contains(variable->name))
							throw std::exception(std::string("Redefinition of global variable \"" + variable->name + "\".").data());
						
						m_globalVariables.insert(std::make_pair(variable->name, m_output.size()));
						break;
					}
					case Statement::Type::FunctionDeclaration:
					{
						auto function = as<Statements::FunctionDeclaration>(instruction);

						m_functions.insert(std::make_pair(function->name, m_output.size() - 1));
						break;
					}
					}
				}
				break;
			}
			}
		}
	}

	const std::vector<uint16_t>& Compiler::m_compileOperation(std::shared_ptr<Statements::Operation> operation)
	{
		std::vector<uint16_t> output;

		for (int i = 0; i < operation->operands.size(); i++)
		{
			switch (operation->operands.at(i)->getType())
			{
			case Statement::Type::Number:
				break;
			default:
				throw std::exception("This type of operand isn't supported yet. Debug for more informations");
				break;
			}
		}
	}
}