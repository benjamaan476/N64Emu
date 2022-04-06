#pragma once
#include <memory>

class Ram : public std::enable_shared_from_this<Ram>
{
public:

	using SharedPtr = std::shared_ptr<Ram>;

	uint8_t readByteUnsinged(uint32_t address);
	void writeByteUnsined(uint32_t address, uint8_t byte);
	int8_t readByteSigned(uint32_t address);
	void writeByteSigned(uint32_t address, int8_t byte);



};