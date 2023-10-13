#ifndef BINARY_HPP
#define BINARY_HPP

#include <iostream>
#include <string>
#include <limits>

class Binary
{
	public:
		Binary();
		Binary(std::string);
		Binary(const Binary&);
		~Binary();

		Binary& operator=(const Binary&);
		Binary& operator=(const std::string&);

		void		writeBool(bool);
		void		writeByte(int);
		void		writeShort(short);
		void		writeInt(int);
		void		writeLong(long);
		void		writeFloat(float);
		void		writeDouble(double);
		void		writeString(std::string);
		void	    writeIntVar(unsigned int);
		void        writeLongVar(unsigned long);
		void        writeZlib(std::string);
		void		writeStaticString(std::string);

		bool		readBool();
		unsigned int	readByte();
		int readUByte();
		unsigned short	readShort();
		short readUShort();
		unsigned int	readInt();
		int	readUInt();
		unsigned long	readLong();
		long	readULong();
		float		readFloat();
		double		readDouble();
		std::string	readString();
		int	readIntVar();
		long	readLongVar();
		std::string	readZlib();
		std::string	readStaticString(unsigned int);
		
		std::string	getBinary() const;
		unsigned int	getSize() const;
		unsigned int	getPos() const;

		void		setBinary(std::string);
		void		setSize(unsigned int);
		void		setPos(unsigned int);

	protected:
		std::string _binary;
		unsigned int _size;
		unsigned int _pos;
};

#endif // BINARY_HPP
