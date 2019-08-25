#include "ImageHandler.hpp"

#include <algorithm>
#include <array>

#include <FreeImagePlus.h>

#include "src/logger/CLogger.hpp"

#include "src/math/Math.hpp"

void SetOutputMessageFreeImage()
{
	FreeImage_SetOutputMessage(	[]( FREE_IMAGE_FORMAT fif, const char *msg )
								{
									if( fif != FIF_UNKNOWN )
									{
										logWARNING( "{0}: {1}", FreeImage_GetFormatFromFIF( fif ), msg );
									}
									else
									{
										logWARNING( msg );
									}
								} );
}

namespace ImageHandler
{
	/**	Loads an bitmap using FreeImage into a CImage.
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
			SetOutputMessageFreeImage();

			fipMemoryIO memIO( reinterpret_cast<BYTE*>( const_cast<std::byte*>( buffer.data() ) ), buffer.size() );

			fipImage image;

			if( !image.loadFromMemory( memIO ) )
			{
				logWARNING( "failed to load from memory" );
				return( nullptr );
			}

			if( image.isValid() )
			{
				if( image.accessPixels() == nullptr )
				{
					logWARNING( "image '{0}' only consists of metadata and no pixels", path.generic_string() );
					return( nullptr );
				}

				if( image.getPalette() != nullptr )
				{
					logWARNING( "palettized image '{0}' is not supported", path.generic_string() );
					return( nullptr );
				}

				CSize size { image.getWidth(), image.getHeight() };
				const u8 bpp	= image.getBitsPerPixel();

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
					// resize the image
					
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

					if( !image.rescale( size.width, size.height, FILTER_BSPLINE ) )
					{
						logWARNING( "failed to rescale image '{0}'", path.generic_string() );

						return( nullptr );
					}
				}

				if( flipVertically )
				{
					FreeImage_FlipVertical( image );
				}

				const u32 pitch = image.getScanWidth();

				auto imageData = std::make_unique<CImage::PixelBuffer>( pitch * size.height );

				std::copy( reinterpret_cast<std::byte*>( image.accessPixels() ), reinterpret_cast<std::byte*>( image.accessPixels() ) + ( pitch * size.height ), imageData->data() );

				return( std::make_shared<CImage>( size, bpp, pitch, std::move( imageData ) ) );
			}
			else
			{
				logWARNING( "image '{0}' is not valid", path.generic_string() );
				return( nullptr );
			}
		}
		else
		{
			logWARNING( "failed to open '{0}'", path.generic_string() );
			return( nullptr );
		}
	}

	bool Save( const CFileSystem &p_filesystem, const std::shared_ptr<const CImage> &image, const f16 scale_factor, const std::string &format, const fs::path &path )
	{
		if( !path.has_filename() )
		{
			logWARNING( "path '{0}' does not contain a filename", path.generic_string() );
			return( false );
		}

		SetOutputMessageFreeImage();

		FIBITMAP *bitmap = FreeImage_ConvertFromRawBits( reinterpret_cast<BYTE*>( const_cast<std::byte*>( image->RawPixelData() ) ), image->Size().width, image->Size().height, image->Size().width * 3, image->BPP(), FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK );
		if( nullptr == bitmap )
		{
			logWARNING( "unable to create FIBITMAP from CImage" );
			return( false );
		}
		else
		{
			fipImage fiImage;
			fiImage = bitmap;

			if( scale_factor < 1.0f )
			{
				logDEBUG( "resizing image by '{0}'", scale_factor );

				if( !fiImage.rescale( static_cast<unsigned int>( image->Size().width * scale_factor ), static_cast<unsigned int>( image->Size().height * scale_factor ), FILTER_BSPLINE ) )
				{
					logWARNING( "failed to rescale image" );
					return( false );
				}
			}

			FREE_IMAGE_FORMAT fiFormat;
			i32 flags;
			if( format == "png" )
			{
				fiFormat	= FIF_PNG;
				flags		= PNG_DEFAULT;
			}
			else if( ( format == "jpg" ) || ( format == "jpeg" ) )
			{
				fiFormat	= FIF_JPEG;
				flags		= JPEG_DEFAULT;
			}
			else
			{
				logWARNING( "unknown image-format '{0}', using default 'png' for now", format );
				fiFormat	= FIF_PNG;
				flags		= PNG_DEFAULT;
			}

			fipMemoryIO memIO;

			if( !fiImage.saveToMemory( fiFormat, memIO, flags ) )
			{
				logWARNING( "failed to save to memory" );
				return( false );
			}

			BYTE* data;
			DWORD sizeInBytes;
			memIO.acquire( &data, &sizeInBytes );

			CFileSystem::FileBuffer buffer( reinterpret_cast<std::byte*>( data ), reinterpret_cast<std::byte*>( data ) + sizeInBytes );

			return( p_filesystem.SaveBufferToFile( buffer, path ) );
		}
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

			auto blah = []( const CColor &color ) -> auto
			{
				return( ColorBytes{	static_cast<std::byte>( static_cast<u8>( std::round( color.r() * 255 ) ) ),
									static_cast<std::byte>( static_cast<u8>( std::round( color.g() * 255 ) ) ),
									static_cast<std::byte>( static_cast<u8>( std::round( color.b() * 255 ) ) ),
									static_cast<std::byte>( static_cast<u8>( std::round( color.a() * 255 ) ) ) } );
			};

			const std::array<ColorBytes, 2> colors = { blah( color1 ), blah( color2 ) };

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
