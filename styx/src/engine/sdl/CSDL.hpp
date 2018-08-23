#ifndef CSDL_HPP
#define CSDL_HPP

#include <exception>

class CSDL
{
public:
	CSDL();
	~CSDL();

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};
};

#endif // CSDL_HPP
