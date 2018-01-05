#ifndef CSETTINGS_HPP
#define CSETTINGS_HPP

#include <string>

#include "src/engine/helper/CSize.hpp"

#include "src/engine/system/CFileSystem.hpp"

class CSettings final
{
public:
	CSettings( const CFileSystem &p_filesystem, const std::string &settingsfile );

	struct s_Engine
	{
		const std::uint64_t tick { 33333 };
	} engine;

	struct s_Renderer final
	{
		struct s_Window final
		{
			CSize			size			{ 640, 480 };
			float			aspect_ratio	{ static_cast< float >( size.width ) / static_cast< float >( size.height ) };
			std::uint8_t	display			{ 0 };
			bool			fullscreen		{ false };
			bool			vsync			{ true };
			float			gamma			{ 1.0f };
			bool			antialiasing	{ false };
		} window;

		struct s_Textures final
		{
			std::uint8_t	anisotropic		{ 1 };
			std::uint8_t	picmip			{ 0 };
		} textures;

		struct s_Screenshot final
		{
			std::string	format			{ "png" };
			float		scale_factor	{ 1.0f };
		} screenshot;

	} renderer;

	struct s_Sound final
	{
		float			volume { 1.0f };
		std::uint16_t	buffer_size	{ 4096 };
	} sound;

	struct s_Input final
	{
		std::string controller_file;
	} input;

	class Exception: public std::exception
	{
	public:
		explicit Exception( void ) {}

		virtual ~Exception() throw() {}
	};

private:
	CSettings( const CSettings &rhs ) = delete;
	CSettings& operator = ( const CSettings &rhs ) = delete;
};

#endif // CSETTINGS_HPP
