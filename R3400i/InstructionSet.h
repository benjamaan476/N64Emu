#pragma once
#include <memory>
#include <bitset>
#include "R3400i.h"
#include <map>

/****************************************************************************
** Explanations**
****************************************************************************
rs = 5 - bit source register specifier
rt = 5 - bit target(source / destination) register or branch condition
rd = 5 - bit destination register specifier
sa = 5 - bit shift amount

fs = 5 - bit floating point source register specifier
ft = 5 - bit floating point target(source / destination)
register or branch condition
fd = 5 - bit floating point destination register specifier

base = 5 - bit value
imm = 16 bit immediate value
offset = 16 bit branch displacement or address displacement
target = 26 bit jump target address
*/



struct Instruction : std::enable_shared_from_this<Instruction>
{
	using SharedPtr = std::shared_ptr<Instruction>;

	uint32_t instruction;
	uint8_t opcode;

	virtual void execute(R3400i::SharedPtr cpu);
	static Instruction::SharedPtr create(R3400i::SharedPtr cpu);

protected:
	Instruction(uint32_t instruction) : instruction{ instruction }
	{
		opcode = (uint8_t)((instruction << 26 & 0xFF));
	}
	Instruction() {}

};

struct ImmediateInstruction : Instruction, std::enable_shared_from_this<ImmediateInstruction>
{

	using SharedPtr = std::shared_ptr<ImmediateInstruction>;

	uint8_t rs;
	uint8_t rt;
	uint16_t offset;

	void execute(R3400i::SharedPtr cpu) override = 0;
	
	ImmediateInstruction() : Instruction{} {}

	ImmediateInstruction(uint32_t instruction) : Instruction(instruction)
	{
		offset = instruction & 0xFFFF;
		rt = (uint8_t)((instruction << 16) & 0x1F); //There are only 32 registers?
		rs = (uint8_t)((instruction << 21) & 0x1F); //There are only 32 registers?
	}
};

class InstructionSet : public std::enable_shared_from_this<InstructionSet>
{
	using SharedPtr = std::shared_ptr<InstructionSet>;
	std::map<uint8_t, Instruction::SharedPtr> instructionSet;

public:

	static InstructionSet::SharedPtr create(R3400i::SharedPtr cpu)
	{
		return std::make_shared<InstructionSet>(cpu);
	}


	static Instruction::SharedPtr getInstruction(uint32_t instruction);
	
	InstructionSet(R3400i::SharedPtr cpu)
	{
		instructionSet.try_emplace(32, LB::create(cpu));

	}

#pragma region Load Instructions

	//Load Byte
	struct LB : ImmediateInstruction, std::enable_shared_from_this<LB>
	{
		using SharedPtr = std::shared_ptr<LB>;
		R3400i::SharedPtr cpuPtr;

		LB(R3400i::SharedPtr cpu) : ImmediateInstruction{}, cpuPtr{ cpu } {}
	
public:
		static Instruction::SharedPtr create(R3400i::SharedPtr cpu)
		{
			return std::make_shared<LB>(cpu);
		}

		void execute(uint32_t instruction)
		{
			offset = instruction & 0xFFFF;
			rt = (uint8_t)((instruction << 16) & 0x1F); //There are only 32 registers?
			rs = (uint8_t)((instruction << 21) & 0x1F); //There are only 32 registers?

			uint32_t address = (cpuPtr->reg.gpr[rs].reg + offset) & 0xFFFFFFFF;

			auto value = cpuPtr->ram->readByteSigned(address);
			cpuPtr->reg.gpr[rt].reg = value;
		}
	};

	//Load Byte Unsigned
	struct LBU : ImmediateInstruction
	{
		void execute(R3400i::SharedPtr cpu) final
		{
			uint32_t address = (cpu->reg.gpr[rs].reg + offset) & 0xFFFFFFFF;

			auto value = cpu->ram->readByteUnsinged(address);
			cpu->reg.gpr[rt].reg = value;
		}
	};

	//Load Double
	struct LD : ImmediateInstruction
	{

	};
#pragma endregion

};