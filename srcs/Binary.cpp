#include "Binary.hpp"

Binary::Binary()
{
	_binary = "";
	_size = 0;
	_pos = 0;
}

Binary::Binary(std::string binary)
{
	_binary = binary;
	_size = binary.size();
	_pos = 0;
}

Binary::Binary(const Binary& other)
{
	_binary = other._binary;
	_size = other._size;
	_pos = other._pos;
}

Binary::~Binary()
{}

Binary& Binary::operator=(const Binary& other)
{
	_binary = other._binary;
	_size = other._size;
	_pos = other._pos;
	return *this;
}

Binary& Binary::operator=(const std::string& binary)
{
	_binary = binary;
	_size = binary.size();
	_pos = 0;
	return *this;
}

void	Binary::writeBool(bool value)
{
	if (_pos + 1 > _size)
		_binary.resize(_pos + 1);
	_binary[_pos] = value;
	_pos += 1;
}

void	Binary::writeByte(int value)
{
	if (_pos + 1 > _size)
		_binary.resize(_pos + 1);
	_binary[_pos] = value & 255;
	_pos += 1;
}

void	Binary::writeShort(short value)
{
	if (_pos + 2 > _size)
		_binary.resize(_pos + 2);
	_binary[_pos] = (value >> 8) & 255;
	_binary[_pos + 1] = value & 255;
	_pos += 2;
}

void	Binary::writeInt(int value)
{
	if (_pos + 4 > _size)
		_binary.resize(_pos + 4);
	_binary[_pos] = (value >> 24) & 255;
	_binary[_pos + 1] = (value >> 16) & 255;
	_binary[_pos + 2] = (value >> 8) & 255;
	_binary[_pos + 3] = value & 255;
	_pos += 4;
}

void	Binary::writeLong(long value)
{
	if (_pos + 8 > _size)
		_binary.resize(_pos + 8);
	_binary[_pos] = (value >> 56) & 255;
	_binary[_pos + 1] = (value >> 48) & 255;
	_binary[_pos + 2] = (value >> 40) & 255;
	_binary[_pos + 3] = (value >> 32) & 255;
	_binary[_pos + 4] = (value >> 24) & 255;
	_binary[_pos + 5] = (value >> 16) & 255;
	_binary[_pos + 6] = (value >> 8) & 255;
	_binary[_pos + 7] = value & 255;
	_pos += 8;
}

void	Binary::writeFloat(float value)
{
	unsigned int *ptr = (unsigned int*)&value;
	writeInt(*ptr);
}

void	Binary::writeDouble(double value)
{
	unsigned long *ptr = (unsigned long*)&value;
	writeLong(*ptr);
}

void	Binary::writeString(std::string value)
{
	writeInt(value.size());
	for (unsigned int i = 0; i < value.size(); i++)
		writeByte(value[i]);
}

void	Binary::writeIntVar(unsigned int value)
{
	while (value > 127)
	{
		writeByte((value & 127) | 128);
		value >>= 7;
	}
	writeByte(value);
}

void	Binary::writeLongVar(unsigned long value)
{
	while (value > 127)
	{
		writeByte((value & 127) | 128);
		value >>= 7;
	}
	writeByte(value);
}

void	Binary::writeZlib(std::string value)
{
	writeInt(value.size());
	for (unsigned int i = 0; i < value.size(); i++)
		writeByte(value[i]);
}

void	Binary::writeStaticString(std::string value)
{
	for (unsigned int i = 0; i < value.size(); i++)
		writeByte(value[i]);
}

bool	Binary::readBool()
{
	bool value = _binary[_pos];
	_pos += 1;
	return value;
}

unsigned int	Binary::readByte()
{
	unsigned int value = 0;
	value = (_binary[_pos] & 255);
	_pos += 1;
	return value;
}

int	Binary::readUByte()
{
	int value = readByte();
	if (value > 127)
		value -= 256;
	return value;
}

unsigned short	Binary::readShort()
{
	unsigned short value = 0;
	value = (_binary[_pos] & 255) << 8;
	value |= (_binary[_pos + 1] & 255);
	_pos += 2;
	return value;
}

short	Binary::readUShort()
{
	short value = readShort();
	if (value > 32767)
		value -= 65536;
	return value;
}

unsigned int	Binary::readInt()
{
	unsigned int value = 0;
	value = (_binary[_pos] & 255) << 24;
	value |= (_binary[_pos + 1] & 255) << 16;
	value |= (_binary[_pos + 2] & 255) << 8;
	value |= (_binary[_pos + 3] & 255);
	_pos += 4;
	return value;
}

int	Binary::readUInt()
{
	int value = readInt();
	if (value > 2147483647)
		value -= 4294967296;
	return value;
}

unsigned long	Binary::readLong()
{
	unsigned long value = 0;
	value = ((uint64_t)_binary[_pos] & 255) << 56;
	value |= ((uint64_t)_binary[_pos + 1] & 255) << 48;
	value |= ((uint64_t)_binary[_pos + 2] & 255) << 40;
	value |= ((uint64_t)_binary[_pos + 3] & 255) << 32;
	value |= ((uint64_t)_binary[_pos + 4] & 255) << 24;
	value |= ((uint64_t)_binary[_pos + 5] & 255) << 16;
	value |= ((uint64_t)_binary[_pos + 6] & 255) << 8;
	value |= ((uint64_t)_binary[_pos + 7] & 255);
	_pos += 8;
	return value;
}

long	Binary::readULong()
{
	long value = readLong();
	if (value > 9223372036854775807)
		value -= LONG_MAX;
	return value;
}

float	Binary::readFloat()
{
	unsigned int value = readInt();
	return *(float*)&value;
}

double	Binary::readDouble()
{
	unsigned long value = readLong();
	return *(double*)&value;
}

std::string	Binary::readString()
{
	std::string value = "";
	unsigned int size = readInt();
	for (unsigned int i = 0; i < size; i++)
		value += readByte();
	return value;
}

int	Binary::readIntVar()
{
	int value = 0;
	int i = 0;
	int b = 0;
	while (((b = readByte()) & 128) != 0)
	{
		value |= (b & 127) << i;
		i += 7;
	}
	value |= b << i;
	return value;
}

long	Binary::readLongVar()
{
	long value = 0;
	int i = 0;
	int b = 0;
	while (((b = readByte()) & 128) != 0)
	{
		value |= ((uint64_t)b & 127) << i;
		i += 7;
	}
	value |= (uint64_t)b << i;
	return value;
}

std::string	Binary::readZlib()
{
	std::string value = "";
	unsigned int size = readInt();
	for (unsigned int i = 0; i < size; i++)
		value += readByte();
	return value;
}

std::string	Binary::readStaticString(unsigned int size)
{
	std::string value = "";
	for (unsigned int i = 0; i < size; i++)
		value += readByte();
	return value;
}

std::string	Binary::getBinary() const
{
	return _binary;
}

unsigned int	Binary::getSize() const
{
	return _size;
}

unsigned int	Binary::getPos() const
{
	return _pos;
}

void	Binary::setBinary(std::string binary)
{
	_binary = binary;
	_size = binary.size();
	_pos = 0;
}

void	Binary::setSize(unsigned int size)
{
	_size = size;
}

void	Binary::setPos(unsigned int pos)
{
	_pos = pos;
}
