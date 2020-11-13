#pragma once

#include "common.h"
#include "abstractsyntaxtree.h"
#include "statements.h"

namespace Chip8Compiler
{
	class Compiler
	{
	public:
		Compiler();
		const std::vector<uint8_t>& compile(AST ast);

	private:
		struct Function
		{
			std::vector<std::shared_ptr<Statement>> satements;
			std::vector<std::string> variables;
		};

		

	private:
		std::vector<uint16_t> m_output;

		// easily cast statements
		template <typename T>
		inline std::shared_ptr<T> as(std::shared_ptr<Statement> statement) { return std::dynamic_pointer_cast<T>(statement); }

		// convert operations to byte code
		const std::vector<uint16_t>& m_compileOperation(std::shared_ptr<Statements::Operation> operation);

		// global things
		// name: adress
		std::unordered_map<std::string, uint32_t> m_functions;
		std::unordered_map<std::string, uint32_t> m_globalVariables;

		// display, clear, etc...
		std::unordered_map<std::string, std::function<uint16_t(const uint16_t&, const uint16_t&, const uint16_t&)>> m_defaultFunctions;

		struct defaultOperationsFactory
		{
			uint16_t ret();
			uint16_t jump(const uint16_t& address);
			uint16_t call(const uint16_t& address);
			uint16_t vxToNn(const uint8_t& vx, const uint8_t& nn);
			uint16_t vxPlusNn(const uint8_t& vx, const uint8_t& nn);
			uint16_t vxToVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t vxOrVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t vxAndVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t vxXorVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t vxPlusVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t vxMinusVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t vxRightShiftVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t vyMinusVx(const uint8_t& vx, const uint8_t& vy);
			uint16_t vxLeftShiftVy(const uint8_t& vx, const uint8_t& vy);
			uint16_t iToNnn(const uint8_t& nnn);
			uint16_t jumpV0(const uint8_t& nnn);
		} m_defaultOperationsFactory;
	};
}