#ifndef PACKETHEADER_HPP

# define PACKETHEADER_HPP

# include <iostream>
# include <string>

# include "Binary.hpp"

class PacketHeader : public Binary
{
	public:
		PacketHeader(unsigned int, unsigned int, Binary *);
		PacketHeader(const PacketHeader&);
		~PacketHeader();

		PacketHeader& operator=(const PacketHeader&);

		unsigned int	getId() const;
		unsigned int	getSize() const;
		std::string		getPacket() const;

		void		setId(unsigned int);
		void		setSize(unsigned int);
		void		setPacket(std::string);

	protected:
		unsigned int _id;
		unsigned int _size;
		std::string	_packet;
};

#endif // PACKETHEADER_HPP
