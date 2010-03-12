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
	std::vector<uint32_t> words;
	uint32_t currentWord;
public:
	DataSerialiser();

	void PutWord(uint32_t value, int significantBits);

	void Sync();
	std::string StringValue();

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
