#pragma once
#include <memory>
#include <bitset>
#include <vector>
#include "../RAM/Ram.h"

template <class T>
struct Register
{
	std::string name;
	T reg{ 0 };
};

struct Registers
{
#pragma region General Purpose Registers
	std::vector<Register<uint64_t>> gpr
	{
		{"r0"},
		{"at"},
		{"v0"},
		{"v1"},
		{"a0"},
		{"a1"},
		{"a2"},
		{"a3"},
		{"t0"},
		{"t1"},
		{"t2"},
		{"t3"},
		{"t4"},
		{"t5"},
		{"t6"},
		{"t7"},
		{"s0"},
		{"s1"},
		{"s2"},
		{"s3"},
		{"s4"},
		{"s5"},
		{"s6"},
		{"s7"},
		{"t8"},
		{"t9"},
		{"k0"},
		{"k1"},
		{"gp"},
		{"sp"},
		{"s8"},
		{"ra"},
	};
#pragma endregion

#pragma region Floating Point Registers
	std::vector<Register<double_t>> fpr{ 32 };
#pragma endregion

	Register<uint64_t> programCounter;
	Register<uint64_t> hi;
	Register<uint64_t> lo;
	Register<std::bitset<1>> llb;
	Register<float_t> fcr0;
	Register<float_t> fcr31;
};

class R3400i : public std::enable_shared_from_this<R3400i>
{
public:
	using SharedPtr = std::shared_ptr<R3400i>;

	Registers reg;

	Ram::SharedPtr ram;

	static R3400i::SharedPtr create();

	R3400i() = default;

};