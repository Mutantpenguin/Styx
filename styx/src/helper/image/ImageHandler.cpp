#include "ImageHandler.hpp"

#include <memory>
#include <algorithm>
#include <array>

#include "external/stb/stb_image.h"
#include "external/stb/stb_image_resize.h"
#include "external/stb/stb_image_write.h"

#include "src/logger/CLogger.hpp"

#include "src/math/Math.hpp"

namespace ImageHandler
{
	/**	Loads an bitmap using stb_image into a CImage.
		If necessary it gets rescaled to maxSize
	*/
	std::shared_ptr<CImage> Load( const CFileSystem &p_filesystem, const fs::path &path, const u32 maxSize, const bool flipVertically )
	{
		if( !path.has_filename() )
		{
			logWARNING( "path '{0}' does not contain a filename", path.generic_string() );
			return( nullptr );
		}

		if( !p_filesystem.Exists( path ) )
		{
			logWARNING( "image '{0}' does not exist", path.generic_string() );
			return( nullptr );
		}

		auto const buffer = p_filesystem.LoadFileToBuffer( path );

		if( !buffer.empty() )
		{
			stbi_set_flip_vertically_on_load( !flipVertically );

			int width, height, components;

			std::unique_ptr<stbi_uc[], decltype( &stbi_image_free )> image( stbi_load_from_memory( reinterpret_cast<stbi_uc*>( const_cast<std::byte*>( buffer.data() ) ), buffer.size(), &width, &height, &components, STBI_default ), stbi_image_free );

			if( !image )
			{
				logWARNING( "failed to load image from memory: {0}", stbi_failure_reason() );
				return( nullptr );
			}

			CSize size { static_cast<u32>( width ), static_cast<u32>( height ) };

			if(	!Math::IsPowerOfTwo( size.width )
				||
				!Math::IsPowerOfTwo( size.height ) )
			{
				logWARNING( "the size of image '{0}' is not a power of two", path.generic_string() );

				return( nullptr );
			}

			if(	( size.width > maxSize )
				||
				( size.height > maxSize ) )
			{
				const auto original_size = size;

				logWARNING( "image '{0}' has to be scaled down because it's bigger than the allowed max size of '{1}' pixels", path.generic_string(), maxSize );
										
				// scale both axis down equally
				while(	( size.width > maxSize )
						||
						( size.height > maxSize ) )
				{
					size.width	>>= 1;
					size.height	>>= 1;
				}
					
				// if width or height are below 1 we can't rescale so clamp it to 1
				size.width	= (std::max)( static_cast<u32>( 1 ), size.width );
				size.height	= (std::max)( static_cast<u32>( 1 ), size.height );

				std::unique_ptr<stbi_uc[], decltype( &stbi_image_free )> image_resized( (stbi_uc*)malloc( size.width * size.height * components ), stbi_image_free );

				if( !stbir_resize_uint8( image.get(), original_size.width, original_size.height, 0,
										 image_resized.get(), size.width, size.height, 0,
					                     components ) )
				{
					logWARNING( "failed to rescale image '{0}'", path.generic_string() );

					return( nullptr );
				}

				image.reset( image_resized.release() );
			}

			const u32 pitch = components * size.width;
			const u32 bpp = components * 8;

			auto imageData = std::make_unique<CImage::PixelBuffer>( pitch * size.height );

			std::copy( reinterpret_cast<std::byte*>( image.get() ), reinterpret_cast<std::byte*>( image.get() ) + ( pitch * size.height ), imageData->data() );

			return( std::make_shared<CImage>( size, bpp, pitch, std::move( imageData ) ) );
		}
		else
		{
			logWARNING( "failed to open '{0}'", path.generic_string() );
			return( nullptr );
		}
	}

	bool Save( const CFileSystem &p_filesystem, const CImage &image, const std::string &format, const fs::path &path )
	{
		if( !path.has_filename() )
		{
			logWARNING( "path '{0}' does not contain a filename", path.generic_string() );
			return( false );
		}

		stbi_flip_vertically_on_write( 1 );

		auto buffer = std::make_unique<CFileSystem::FileBuffer>();

		auto write_func =	[]( void *context, void *data, int size )
							{
								auto buffer_ptr = static_cast<std::unique_ptr<CFileSystem::FileBuffer>*>( context );

								auto buffer = buffer_ptr->get();

								std::copy( reinterpret_cast<std::byte*>( data ), reinterpret_cast<std::byte*>( data ) + size, back_inserter( *buffer ) );
							};

		u16 write_status = 0;

		if( format == "png" )
		{
			write_status = stbi_write_png_to_func( write_func, &buffer, image.Size().width, image.Size().height, 3, image.RawPixelData(), image.Size().width * 3 );
		}
		else if( ( format == "jpg" ) || ( format == "jpeg" ) )
		{
			static const auto jpg_quality = 90;

			write_status = stbi_write_jpg_to_func( write_func, &buffer, image.Size().width, image.Size().height, 3, image.RawPixelData(), jpg_quality );
		}
		else
		{
			logWARNING( "unknown image-format '{0}'", format );
			return( false );
		}

		if( !write_status )
		{
			logWARNING( "failed to save to memory" );
			return( false );
		}

		return( p_filesystem.SaveBufferToFile( *buffer.get(), path ) );
	}

	std::shared_ptr<CImage> GenerateCheckerImage( const CSize &size, const CColor &color1, const CColor &color2 )
	{
		if( !Math::IsPowerOfTwo( size.width ) )
		{
			logWARNING( "width '{0}' is not a power of two", size.width );
			return( nullptr );
		}
		else if( !Math::IsPowerOfTwo( size.height ) )
		{
			logWARNING( "height '{0}' is not a power of two", size.height );
			return( nullptr );
		}
		else
		{
			using ColorBytes = std::array<std::byte, 4>;

			auto ConvertColorToByteArray = []( const CColor &color ) -> auto
			{
				return( ColorBytes{	static_cast<std::byte>( static_cast<u8>( std::round( color.r() * 255 ) ) ),
									static_cast<std::byte>( static_cast<u8>( std::round( color.g() * 255 ) ) ),
									static_cast<std::byte>( static_cast<u8>( std::round( color.b() * 255 ) ) ),
									static_cast<std::byte>( static_cast<u8>( std::round( color.a() * 255 ) ) ) } );
			};

			const std::array<ColorBytes, 2> colors = { ConvertColorToByteArray( color1 ), ConvertColorToByteArray( color2 ) };

			auto checkerImageData = std::make_unique<CImage::PixelBuffer>( size.width * size.height * 4 );

			for( u32 i = 0; i < size.height; ++i )
			{
				for( u32 j = 0; j < size.width; ++j )
				{
					// change color every 8 pixels
					const auto c = ( ( i & 0x8 ) == 0 ) ^ ( ( j & 0x8 ) == 0 );

					const auto &color = colors[ c ];

					const u32 index = ( ( i * size.width ) * 4 ) + ( j * 4 );
					checkerImageData->at( index + 0 ) = color[ 2 ];	// blue
					checkerImageData->at( index + 1 ) = color[ 1 ];	// green
					checkerImageData->at( index + 2 ) = color[ 0 ];	// red
					checkerImageData->at( index + 3 ) = color[ 3 ];	// alpha
				}
			}

			return( std::make_shared<CImage>( size, 32, size.width * 4, std::move( checkerImageData ) ) );
		}
	}
}
