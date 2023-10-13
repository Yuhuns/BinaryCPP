#include "PacketHeader.hpp"

PacketHeader::PacketHeader(unsigned int u1, unsigned int u2, Binary *packet)
{
	Binary	*bin = new Binary();
	_id = (u1 << 8) | (u2 & 255);
	bin->writeShort(_id);
	_size = packet->getBinary().size();
	bin->writeShort(_size);
	_packet = (bin->getBinary() + packet->getBinary());
}

PacketHeader::PacketHeader(const PacketHeader& other)
{
	_id = other._id;
	_size = other._size;
	_packet = other._packet;
}

PacketHeader::~PacketHeader()
{
	if (_packet.size() > 0)
		_packet.clear();
}

PacketHeader& PacketHeader::operator=(const PacketHeader& other)
{
	_id = other._id;
	_size = other._size;
	_packet = other._packet;
	return *this;
}

unsigned int	PacketHeader::getId() const
{
	return _id;
}

unsigned int	PacketHeader::getSize() const
{
	return _size;
}

void	PacketHeader::setId(unsigned int id)
{
	_id = id;
}

void	PacketHeader::setSize(unsigned int size)
{
	_size = size;
}

std::string	PacketHeader::getPacket() const
{
	return _packet;
}

void	PacketHeader::setPacket(std::string packet)
{
	_packet = packet;
}
