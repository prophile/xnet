#include "DataUnserialiser.h"
#include <assert.h>

namespace XNet
{

void DataUnserialiser::NextWord()
{
	if (words.size() == nextWord)
	{
		// early exit
		currentWord = 0;
		bitIndex = 0;
		return;
	}
	currentWord = words[nextWord++];
	bitIndex = 0;
}

void DataUnserialiser::Init(const void* data, size_t length)
{
	assert(length % 4 == 0);
	const uint32_t* wordPtr = (const uint32_t*)data;
	words.reserve(length / 4);
	for (size_t i = 0; i < length; i += 4)
	{
		words.push_back(Big32(wordPtr[i]));
	}
	nextWord = 0;
	NextWord();
}

uint32_t DataUnserialiser::GetWord(int significantBits)
{
	// TODO
	return 0;
}

DataUnserialiser::DataUnserialiser(const void* data, size_t length)
{
	Init(data, length);
}

DataUnserialiser::DataUnserialiser(const std::string& data)
{
	Init(data.data(), data.length());
}

DataUnserialiser& DataUnserialiser::operator>>(uint64_t& value)
{
	uint64_t result;
	uint32_t result32;
	*this >> result32;
	result = (uint64_t)result32 << 32;
	*this >> result32;
	result |= result32;
	value = result;
	return *this;
}

DataUnserialiser& DataUnserialiser::operator>>(std::string& value)
{
	uint32_t length = GetWord(24);
	value.resize(length);
	for (uint32_t i = 0; i < length; ++i)
	{
		value.at(i) = GetWord(8);
	}
	return *this;
}

}
