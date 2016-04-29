#ifndef CSETTINGS_HPP
#define CSETTINGS_HPP

#include <string>

#include "../helper/CSize.hpp"

#include "../system/CFileSystem.hpp"

class CSettings final
{
public:
	CSettings( const CFileSystem &p_filesystem, const std::string &settingsfile );

	struct structEngine
	{
		const std::uint64_t tick { 33333 };
	} engine;

	struct structRenderer final
	{
		struct structWindow final
		{
			CSize	size			{ 640, 480 };
			bool	fullscreen		{ false };
			bool	vsync			{ true };
			float	gamma			{ 1.0f };
			bool	antialiasing	{ false };
		} window;

		struct structTextures final
		{
			unsigned int	anisotropic		{ 1 };
			unsigned int	picmip			{ 0 };
		} textures;

		struct structScreenshot final
		{
			std::string	format			{ "png" };
			float		scale_factor	{ 1.0f };
		} screenshot;

	} renderer;

	struct structSound final
	{
		unsigned int	buffer_size	{ 4096 };
	} sound;

	struct structInput final
	{
		std::string controller_file;
	} input;
};

#endif // CSETTINGS_HPP
