#include "CSettings.hpp"

#include <json/json.h>

#include "../logger/CLogger.hpp"


CSettings::CSettings( const CFileSystem &p_filesystem, const std::string &settingsfile )
{
	const std::string filename = settingsfile.empty() ? "settings.json" : settingsfile;

	LOG( logINFO ) << "using settings-file '" << filename << "'";

	if( !p_filesystem.Exists( filename ) )
	{
		LOG( logWARNING ) << "settings-file '" << filename << "' does not exist";
	}
	else
	{
		Json::Reader reader;
		Json::Value settings_root;

		if( !reader.parse( p_filesystem.LoadTextFileToBuffer( filename ), settings_root ) )
		{
			LOG( logWARNING ) << "failed to parse settings-file '" << filename << "' because of " << reader.getFormattedErrorMessages();
		}
		else
		{
			const Json::Value renderer_root = settings_root[ "renderer" ];
			if( !renderer_root.isNull() )
			{
				const Json::Value window_root = renderer_root[ "window" ];
				if( !window_root.isNull() )
				{
					const Json::Value width = window_root[ "width" ];
					if( width.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.window.width' not found";
					}
					else
					{
						renderer.window.size.width = width.asUInt();
					}

					const Json::Value height = window_root[ "height" ];
					if( height.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.window.height' not found";
					}
					{
						renderer.window.size.height = height.asUInt();
					}

					const Json::Value fullsreen = window_root[ "fullscreen" ];
					if( fullsreen.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.window.fullscreen' not found";
					}
					else
					{
						renderer.window.fullscreen = fullsreen.asBool();
					}

					const Json::Value vsync = window_root[ "vsync" ];
					if( vsync.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.window.vsync' not found";
					}
					else
					{
						renderer.window.vsync = vsync.asBool();
					}

					const Json::Value gamma = window_root[ "gamma" ];
					if( gamma.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.window.gamma' not found";
					}
					else
					{
						renderer.window.gamma = gamma.asDouble();
					}

					const Json::Value antialiasing = window_root[ "antialiasing" ];
					if( antialiasing.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.window.antialiasing' not found";
					}
					else
					{
						renderer.window.antialiasing = antialiasing.asBool();
					}
				}
				else
				{
					LOG( logWARNING ) << "'settings.renderer.window' not found";
				}

				const Json::Value textures_root = renderer_root[ "textures" ];
				if( !textures_root.isNull() )
				{
					const Json::Value anisotropic = textures_root[ "anisotropic" ];
					if( anisotropic.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.textures.anisotropic' not found";
					}
					else
					{
						renderer.textures.anisotropic = anisotropic.asUInt();
					}

					const Json::Value picmip = textures_root[ "picmip" ];
					if( picmip.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.textures.picmip' not found";
					}
					else
					{
						renderer.textures.picmip = picmip.asUInt();
					}
				}
				else
				{
					LOG( logWARNING ) << "'settings.renderer.textures' not found";
				}

				const Json::Value screenshot_root = renderer_root[ "screenshot" ];
				if( !screenshot_root.isNull() )
				{
					const Json::Value format = screenshot_root[ "format" ];
					if( format.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.screenshot.format' not found";
					}
					else
					{
						renderer.screenshot.format = format.asString();
					}

					const Json::Value scale_factor = screenshot_root[ "scale_factor" ];
					if( scale_factor.isNull() )
					{
						LOG( logWARNING ) << "'settings.renderer.screenshot.scale_factor' not found";
					}
					else
					{
						renderer.screenshot.scale_factor = scale_factor.asDouble();
					}
				}
				else
				{
					LOG( logWARNING ) << "'settings.renderer.screenshot' not found";
				}
			}
			else
			{
				LOG( logWARNING ) << "'settings.renderer' not found";
			}

			const Json::Value sound_root = settings_root[ "sound" ];
			if( !sound_root.isNull() )
			{
				const Json::Value buffer_size = sound_root[ "buffer_size" ];
				if( buffer_size.isNull() )
				{
					LOG( logWARNING ) << "'settings.sound.buffer_size' not found";
				}
				else
				{
					sound.buffer_size = buffer_size.asUInt();
				}
			}
			else
			{
				LOG( logWARNING ) << "'settings.sound' not found";
			}

			const Json::Value input_root = settings_root[ "input" ];
			if( !input_root.isNull() )
			{
				const Json::Value controller_file = input_root[ "controller_file" ];
				if( controller_file.isNull() )
				{
					LOG( logWARNING ) << "'settings.input.controller_file' not found";
				}
				else
				{
					input.controller_file = controller_file.asString();
				}
			}
			else
			{
				LOG( logWARNING ) << "'settings.input' not found";
			}
		}
	}
}
