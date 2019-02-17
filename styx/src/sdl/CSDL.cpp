#include "CSDL.hpp"

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "src/logger/CLogger.hpp"

CSDL::CSDL()
{
	// get some version-infos so we can check if the right version of SDL is beeing used
	SDL_version version_linked;
	SDL_version version_compiled;

	SDL_GetVersion( &version_linked );
	SDL_VERSION( &version_compiled );

	logDEBUG( "SDL has version '{0}.{1}.{2}'", version_linked.major, version_linked.minor, version_linked.patch );

	if( SDL_COMPILEDVERSION != SDL_VERSIONNUM( version_linked.major, version_linked.minor, version_linked.patch ) )
	{
		logERROR( "\tbut version '{0}.{1}.{2}' was expected", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL );
		throw Exception();
	}

	if( SDL_Init( 0 ) )
	{
		logERROR( "initialising SDL failed: {0}", SDL_GetError() );
		throw Exception();
	}

	#ifdef WIN32
		// redirect the output to the console because SDL would redirect it to the files stdout.txt and stderr.txt
		FILE* fileout;

		if( freopen_s( &fileout, "CON", "w", stdout ) != 0 )
		{
			logERROR( "couldn't redirect stdout" );
			throw Exception();
		}

		if( freopen_s( &fileout, "CON", "w", stderr ) != 0 )
		{
			logERROR( "couldn't redirect stdout" );
			throw Exception();
		}
	#endif
}

CSDL::~CSDL()
{
	SDL_Quit();
}
