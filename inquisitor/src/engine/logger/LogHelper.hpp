#ifndef LOGHELPER_HPP
#define LOGHELPER_HPP

namespace LogHelper
{
	inline std::string prettyFunctionNicer( const std::string &str )
	{
		const std::string::size_type s_end = str.find_first_of( "(" );
		const std::string::size_type s_start = str.find_last_of( " ", s_end ) + 1;

		return( str.substr( s_start, s_end - s_start ) );
	}
}

#endif // LOGHELPER_HPP
