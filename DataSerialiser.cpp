#include "DataSerialiser.h"

namespace XNet
{

const void* DataSerialiser::DataValue(size_t& length) const
{
	length = words.size() * 4;
	return (const void*)&words[0];
}

DataSerialiser& DataSerialiser::operator<<(uint64_t value)
{
	return *this << ((uint32_t)(value >> 32)) << ((uint32_t)value);
}

DataSerialiser& DataSerialiser::operator<<(const std::string& value)
{
	PutWord(value.length(), 24);
	for (int i = 0; i < value.length(); ++i)
	{
		PutWord(value[i], 8);
	}
	return *this;
}

static uint32_t CheckSigBits(uint32_t value, int sigbits)
{
	return value & ((1 << sigbits)-1);
}

void DataSerialiser::PutWord(uint32_t value, int sigbits)
{
	// boundary-aligned case
	if (sigbits + index >= 32)
	{
		index += sigbits;
		currentWord <<= sigbits;
		currentWord |= CheckSigBits(value, sigbits);
		if (index == 32)
		{
			index = 0;
			words.push_back(currentWord);
			currentWord = 0;
		}
	}
	else // split case
	{
		// first handle the high-order bits, then the low-order bits
		int splitpoint = sigbits + index - 32;
		// TODO: fill in
	}
}

}
