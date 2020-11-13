#include "compiler.h"

namespace Chip8Compiler
{
	Compiler::Compiler()
	{
		m_defaultFunctions = {
			std::make_pair("clear", [](auto&, auto&, auto&) -> uint16_t { return 0x00e0; }),
			std::make_pair("random",
				[](auto& vx, auto& nn, auto&) -> uint16_t
				{
					std::random_device device;
					std::mt19937 range(device());
					std::uniform_int_distribution<std::mt19937::result_type> distrib(0, 255);
					return distrib(range) & 0xff;
				}),
			std::make_pair("display", [](auto& x, auto& y, auto& height) -> uint16_t { return 0xD000 | (x << 0x8) | (y << 4) | (height & 0xf); }),
			std::make_pair("pressed", [](auto& key, auto&, auto&) -> uint16_t { return 0xe0a1 | (key << 8) }),
			// std::make_pair("delay", [](auto&, auto&, auto&) -> uint16_t { return  })
		};
	}

	uint16_t Compiler::defaultOperationsFactory::ret() { return 0x00ee; }
	uint16_t Compiler::defaultOperationsFactory::jump(const uint16_t& address) { return 0x1 | (address & 0x0fff); }
	uint16_t Compiler::defaultOperationsFactory::call(const uint16_t& address) { return 0x2 | (address & 0x0fff); }
	uint16_t Compiler::defaultOperationsFactory::vxToNn(const uint8_t& vx, const uint8_t& nn) { return 0x6 | (vx << 0x8) | (nn & 0xff); }
	uint16_t Compiler::defaultOperationsFactory::vxPlusNn(const uint8_t& vx, const uint8_t& nn) { return 0x7 | (vx << 0x8) | (nn & 0xff); }
	uint16_t Compiler::defaultOperationsFactory::vxToVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4); }
	uint16_t Compiler::defaultOperationsFactory::vxOrVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0x1; }
	uint16_t Compiler::defaultOperationsFactory::vxAndVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0x2; }
	uint16_t Compiler::defaultOperationsFactory::vxXorVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0x3; }
	uint16_t Compiler::defaultOperationsFactory::vxPlusVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0x4; }
	uint16_t Compiler::defaultOperationsFactory::vxMinusVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0x5; }
	uint16_t Compiler::defaultOperationsFactory::vxRightShiftVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0x6; }
	uint16_t Compiler::defaultOperationsFactory::vyMinusVx(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0x7; }
	uint16_t Compiler::defaultOperationsFactory::vxLeftShiftVy(const uint8_t& vx, const uint8_t& vy) { return 0x8 | (vx << 0x8) | (vy << 0x4) | 0xe; }
}