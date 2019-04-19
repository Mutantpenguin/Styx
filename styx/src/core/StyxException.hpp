#pragma once

#include "external/fmt/format.h"

namespace styx_internal
{
	class StyxException: public std::runtime_error
	{
	public:
		explicit StyxException( const char * const file, const int line, const char * const function, const char * const message ) :
			std::runtime_error( message ),
			m_file { file },
			m_line { line },
			m_func { function }
		{}
		
		explicit StyxException( const char * const file, const int line, const char * const function, const std::string &message ) :
			std::runtime_error( message ),
			m_file { file },
			m_line { line },
			m_func { function }
		{}
		
		virtual ~StyxException() throw() {}
		
		const char * File() const
		{
			return( m_file );
		}
		
		int Line() const
		{
			return( m_line );
		}
		
		const char * Func() const
		{
			return( m_func );
		}
	
	private:
		const char * m_file;
		int m_line;
		const char * m_func;
	
	protected:
		inline std::string ClassName( const std::string& prettyFunction ) const
		{
			const size_t colons = prettyFunction.find( "::", prettyFunction.find( "::" ) + 1 );
			const size_t begin = prettyFunction.substr( 0, colons ).rfind( " " ) + 1;
			const size_t end = colons - begin;

			return( prettyFunction.substr( begin, end ) );
		}
	};
}

#define THROW_STYX_EXCEPTION( ... ) \
throw styx_internal::StyxException( __FILE__, __LINE__, __func__, fmt::format( __VA_ARGS__ ) );