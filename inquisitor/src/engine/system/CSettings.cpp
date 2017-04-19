#include "CSettings.hpp"

#include "src/ext/json/json.hpp"
using json = nlohmann::json;

#include "src/engine/logger/CLogger.hpp"


CSettings::CSettings( const CFileSystem &p_filesystem, const std::string &settingsfile )
{
	const std::string filename = settingsfile.empty() ? "settings.json" : settingsfile;

	logINFO( "using settings-file '{0}'", filename );

	if( !p_filesystem.Exists( filename ) )
	{
		logWARNING( "settings-file '{0}' does not exist", filename );
	}
	else
	{
		const auto settings_root = [&]() -> json {
			try
			{
				return( json::parse( p_filesystem.LoadFileToString( filename ) ) );
			}
			catch( json::parse_error &e )
			{
				logWARNING( "failed to parse settings-file '{0}' because of: {1}", filename, e.what() );
				throw Exception();
			}
		} ();

		const auto renderer_root = settings_root.find( "renderer" );
		if( std::end( settings_root ) == renderer_root )
		{
			logWARNING( "'settings.renderer' not found" );
		}
		else
		{
			const auto window_root = renderer_root->find( "window" );
			if( renderer_root->end() == window_root )
			{
				logWARNING( "'settings.renderer.window' not found" );
			}
			else
			{
				const auto width = window_root->find( "width" );
				if( window_root->end() == width )
				{
					logWARNING( "'settings.renderer.window.width' not found" );
				}
				else
				{
					renderer.window.size.width = width->get<std::uint32_t>();
				}

				const auto height = window_root->find( "height" );
				if( window_root->end() == height )
				{
					logERROR( "'settings.renderer.window.height' not found" );
				}
				else
				{
					renderer.window.size.height = height->get<std::uint32_t>();
				}

				renderer.window.aspect_ratio = static_cast< float >( renderer.window.size.width ) / static_cast< float >( renderer.window.size.height );

				const auto fullsreen = window_root->find( "fullscreen" );
				if( window_root->end() == fullsreen )
				{
					logWARNING( "'settings.renderer.window.fullscreen' not found" );
				}
				else
				{
					renderer.window.fullscreen = fullsreen->get<bool>();
				}

				const auto vsync = window_root->find( "vsync" );
				if( window_root->end() == vsync )
				{
					logWARNING( "'settings.renderer.window.vsync' not found" );
				}
				else
				{
					renderer.window.vsync = vsync->get<bool>();
				}

				const auto gamma = window_root->find( "gamma" );
				if( window_root->end() == gamma )
				{
					logWARNING( "'settings.renderer.window.gamma' not found" );
				}
				else
				{
					renderer.window.gamma = gamma->get<float>();
				}

				const auto antialiasing = window_root->find( "antialiasing" );
				if( window_root->end() == antialiasing )
				{
					logWARNING( "'settings.renderer.window.antialiasing' not found" );
				}
				else
				{
					renderer.window.antialiasing = antialiasing->get<bool>();
				}
			}

			const auto textures_root = renderer_root->find( "textures" );
			if( renderer_root->end() == textures_root )
			{
				logWARNING( "'settings.renderer.textures' not found" );
			}
			else
			{
				const auto anisotropic = textures_root->find( "anisotropic" );
				if( textures_root->end() == anisotropic )
				{
					logWARNING( "'settings.renderer.textures.anisotropic' not found" );
				}
				else
				{
					renderer.textures.anisotropic = anisotropic->get<std::uint8_t>();
				}

				const auto picmip = textures_root->find( "picmip" );
				if( textures_root->end() == picmip )
				{
					logWARNING( "'settings.renderer.textures.picmip' not found" );
				}
				else
				{
					renderer.textures.picmip = picmip->get<std::uint8_t>();
				}
			}

			const auto screenshot_root = renderer_root->find( "screenshot" );
			if( renderer_root->end() == screenshot_root )
			{
				logWARNING( "'settings.renderer.screenshot' not found" );
			}
			else
			{
				const auto format = screenshot_root->find( "format" );
				if( screenshot_root->end() == format )
				{
					logWARNING( "'settings.renderer.screenshot.format' not found" );
				}
				else
				{
					renderer.screenshot.format = format->get<std::string>();
				}

				const auto scale_factor = screenshot_root->find( "scale_factor" );
				if( screenshot_root->end() == scale_factor )
				{
					logWARNING( "'settings.renderer.screenshot.scale_factor' not found" );
				}
				else
				{
					renderer.screenshot.scale_factor = scale_factor->get<float>();
				}
			}
		}

		const auto sound_root = settings_root.find( "sound" );
		if( std::end( settings_root ) == sound_root )
		{
			logWARNING( "'settings.sound' not found" );
		}
		else
		{
			const auto buffer_size = sound_root->find( "buffer_size" );
			if( sound_root->end() == buffer_size )
			{
				logWARNING( "'settings.sound.buffer_size' not found" );
			}
			else
			{
				sound.buffer_size = buffer_size->get<std::uint16_t>();
			}
		}

		const auto input_root = settings_root.find( "input" );
		if( std::end( settings_root ) == input_root )
		{
			logWARNING( "'settings.input' not found" );
		}
		else
		{
			const auto controller_file = input_root->find( "controller_file" );
			if( input_root->end() == controller_file )
			{
				logWARNING( "'settings.input.controller_file' not found" );
			}
			else
			{
				input.controller_file = controller_file->get<std::string>();
			}
		}
	}
}
