#ifndef COPENGLADAPTER_HPP
#define COPENGLADAPTER_HPP

#include <exception>

class COpenGlAdapter final
{
public:
	COpenGlAdapter();
	~COpenGlAdapter();

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};
};

#endif // COPENGLADAPTER_HPP
