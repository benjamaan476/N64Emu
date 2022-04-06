#include <memory>

#include "../R3400i/R3400i.h"
#include "../R3400i/InstructionSet.h"


int main()
{
	R3400i::SharedPtr cpu = R3400i::create();
	auto instructionSet = InstructionSet::create(cpu);



	int i = 0;
}