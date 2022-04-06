#include "R3400i.h"

R3400i::SharedPtr R3400i::create()
{
	return std::make_shared<R3400i>();
}