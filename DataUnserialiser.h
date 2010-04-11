#ifndef __XNET_DATA_UNSERIALISER__
#define __XNET_DATA_UNSERIALISER__

#include <vector>
#include <string>
#include <inttypes.h>

namespace XNet
{

class DataUnserialiser
{
private:
#if defined(__LITTLE_ENDIAN__) && defined(__clang__)
	static uint32_t Big32(uint32_t x)
		{ return __builtin_bswap32(x); }
#elif defined(__LITTLE_ENDIAN__)
	static uint32_t Big32(uint32_t x)
		{ return ((x << 24) & 0xFF000000) |
		         ((x << 16) & 0x00FF0000) |
		         ((x << 8)  & 0x0000FF00) |
		         ((x << 0)  & 0x000000FF); }
#else
	static uint32_t Big32(uint32_t x)
		{ return x; }
#endif
	std::vector<uint32_t> words;
	uint32_t currentWord, bitIndex, nextWord;
	void NextWord();
	void Init(const void* data, size_t len);
public:
	DataUnserialiser(const void* data, size_t len);
	DataUnserialiser(const std::string& data);

	uint32_t GetWord(int significantBits);
	void Sync() { NextWord(); }

	DataUnserialiser& operator>>(bool& value)
		{ value = GetWord(1) == 1; return *this; }
	DataUnserialiser& operator>>(int8_t& value)
		{ value = GetWord(8); return *this; }
	DataUnserialiser& operator>>(uint8_t& value)
		{ value = GetWord(8); return *this; }
	DataUnserialiser& operator>>(int16_t& value)
		{ value = GetWord(16); return *this; }
	DataUnserialiser& operator>>(uint16_t& value)
		{ value = GetWord(16); return *this; }
	DataUnserialiser& operator>>(int32_t& value)
		{ value = GetWord(32); return *this; }
	DataUnserialiser& operator>>(uint32_t& value)
		{ value = GetWord(32); return *this; }
	DataUnserialiser& operator>>(uint64_t& value);
	DataUnserialiser& operator>>(int64_t& value)
		{ return *this >> (uint64_t&)value; }
	DataUnserialiser& operator>>(std::string& value);
	DataUnserialiser& operator>>(float& value)
		{
			union { float fval; uint32_t ival; } bitcast;
			*this >> bitcast.ival;
			value = bitcast.fval;
			return *this;
		}
	DataUnserialiser& operator>>(double& value)
		{
			union { double fval; uint64_t ival; } bitcast;
			*this >> bitcast.ival;
			value = bitcast.fval;
			return *this;
		}
};

}

#endif
