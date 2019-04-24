#pragma once

#include <string>

#include "src/core/Types.hpp"

#include "src/helper/CSize.hpp"

#include "src/system/CFileSystem.hpp"

class CSettings final
{
public:
	CSettings( const CFileSystem &p_filesystem, const std::string &settingsfile );

	struct s_Engine
	{
		const u64 tick { 33333 };
	} engine;

	struct s_Renderer final
	{
		struct s_Window final
		{
			CSize	size			{ 640, 480 };
			f16		aspect_ratio	{ static_cast< f16 >( size.width ) / static_cast< f16 >( size.height ) };
			u8		display			{ 0 };
			bool	fullscreen		{ false };
			bool	vsync			{ true };
			f16		gamma			{ 1.0f };
			bool	antialiasing	{ false };
		} window;

		struct s_Textures final
		{
			u8	anisotropic	{ 1 };
			u8	picmip		{ 0 };
		} textures;

		struct s_Screenshot final
		{
			std::string	format			{ "png" };
			f16			scale_factor	{ 1.0f };
		} screenshot;

	} renderer;

	struct s_Audio final
	{
		f16	volume { 1.0f };
		u16	buffer_size	{ 4096 };
	} audio;

	struct s_Input final
	{
		std::string controller_file;
	} input;

private:
	CSettings( const CSettings &rhs ) = delete;
	CSettings& operator = ( const CSettings &rhs ) = delete;
};
