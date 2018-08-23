#ifndef LOGHELPER_HPP
#define LOGHELPER_HPP

namespace LogHelper
{
	inline std::string prettyFunctionNicer( const std::string &str )
	{
		const std::string::size_type s_end = str.find_first_of( "(" );
		const std::string::size_type s_start = str.find_last_of( " ", s_end );

		if( s_start == std::string::npos )
		{
			return( str.substr( 0, s_end ) );
		}
		else
		{
			return( str.substr( s_start + 1, s_end - ( s_start + 1 ) ) );
		}
	}
}

#endif // LOGHELPER_HPP
