#ifndef __XNET_DATA_SERIALISER__
#define __XNET_DATA_SERIALISER__

#include <vector>
#include <string>
#include <inttypes.h>

namespace XNet
{

class DataSerialiser
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
	uint32_t currentWord, index;
public:
	DataSerialiser();

	void PutWord(uint32_t value, int significantBits);

	void Sync()
		{ words.push_back(Big32(currentWord));
		  currentWord = index = 0; }
	const void* DataValue(size_t& length) const;
	std::string StringValue() const
		{ size_t len;
		  const char* bytes = (const char*)DataValue(len);
		  return std::string(bytes, len); }

	DataSerialiser& operator<<(bool value)
		{ PutWord(value ? 1 : 0, 1); return *this; }
	DataSerialiser& operator<<(uint8_t value)
		{ PutWord(value, 8); return *this; }
	DataSerialiser& operator<<(int8_t value)
		{ PutWord(value, 8); return *this; }
	DataSerialiser& operator<<(uint16_t value)
		{ PutWord(value, 16); return *this; }
	DataSerialiser& operator<<(int16_t value)
		{ PutWord(value, 16); return *this; }
	DataSerialiser& operator<<(uint32_t value)
		{ PutWord(value, 32); return *this; }
	DataSerialiser& operator<<(int32_t value)
		{ PutWord(value, 32); return *this; }
	DataSerialiser& operator<<(uint64_t value);
	DataSerialiser& operator<<(int64_t value)
		{ return *this << (uint64_t)value; }
	DataSerialiser& operator<<(const std::string& value);
	DataSerialiser& operator<<(const char* value)
		{ return *this << std::string(value); }
	DataSerialiser& operator<<(float value)
		{
			union { float fval; uint32_t ival; } bitcast;
			bitcast.fval = value;
			return *this << bitcast.ival;
		}
	DataSerialiser& operator<<(double value)
		{
			union { double fval; uint64_t ival; } bitcast;
			bitcast.fval = value;
			return *this << bitcast.ival;
		}
};

}

#endif
