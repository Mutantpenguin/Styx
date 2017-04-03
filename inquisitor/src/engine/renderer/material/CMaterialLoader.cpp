#include "CMaterialLoader.hpp"

#include <algorithm>

#include "src/ext/json/json.hpp"
using json = nlohmann::json;

#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/GLHelper.hpp"

std::uint16_t CMaterialLoader::m_dummyCounter { 0 };

CMaterialLoader::CMaterialLoader( const CFileSystem &filesystem, CTextureManager &textureManager, CShaderManager &shaderManager, const CSamplerManager &samplerManager ) :
	m_filesystem { filesystem },
	m_textureManager { textureManager },
	m_shaderManager { shaderManager },
	m_samplerManager { samplerManager }
{
}

CMaterialLoader::~CMaterialLoader( void )
{
	#ifdef INQ_DEBUG
	if( m_dummyCounter > 0 )
	{
		logWARNING( "{0} dummy materials were being created", m_dummyCounter );
	}
	#endif
}

void CMaterialLoader::FromFile( const std::string &path, std::shared_ptr< CMaterial > mat ) const
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "'{0}' does not exist", path );
		FromDummy( mat );
	}
	else
	{
		const std::string fileExtension = path.substr( path.find_last_of( "." ) + 1 );

		if( std::string( "mat" ) == fileExtension )
		{
			try
			{
				if( !FromMatFile( path, mat ) )
				{
					FromDummy( mat );
					return;
				}
			}
			catch( std::exception &e )
			{
				logWARNING( "error loading material '{0}': {1}", path, e.what() );
				FromDummy( mat );
			}
		}
		else
		{
			logWARNING( "file is not a material: '{0}'", path );
			FromDummy( mat );
		}
	}
}

bool CMaterialLoader::FromMatFile( const std::string &path, std::shared_ptr< CMaterial > mat ) const
{
	const std::string definition = m_filesystem.LoadFileToString( path );

	json mat_root;

	try
	{
		mat_root = json::parse( definition );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path, e.what() );
		return( false );
	}

	const auto mat_name = mat_root[ "name" ];

	mat->m_name = mat_name.get<std::string>();

	const auto mat_cullmode = mat_root.find( "cullmode" );
	if( mat_cullmode != mat_root.cend() )
	{
		if( ( !mat_cullmode->get<std::string>().empty() ) && GLHelper::FaceModeFromString( mat_cullmode->get<std::string>(), mat->m_cullfacemode ) )
		{
			mat->m_bCullFace = true;
		}
	}

	const auto mat_polygonmode = mat_root.find( "polygonmode" );
	if( mat_polygonmode != mat_root.cend() )
	{
		if( !GLHelper::PolygonModeFromString( mat_polygonmode->get<std::string>(), mat->m_polygonmode ) )
		{
			mat->m_polygonmode = GL_FILL;
		}
	}

	const auto mat_blending = mat_root.find( "blending" );
	if( mat_blending != mat_root.cend() )
	{
		const auto mat_blendingsrc = mat_blending->find( "src" );
		const auto mat_blendingdst = mat_blending->find( "dst" );
		if( ( mat_blendingsrc != mat_blending->cend() ) && GLHelper::SrcBlendFuncFromString( mat_blendingsrc->get<std::string>(), mat->m_blendSrc ) && ( mat_blendingdst != mat_blending->cend() ) && GLHelper::DstBlendFuncFromString( mat_blendingdst->get<std::string>(), mat->m_blendDst ) )
		{
			mat->m_blending = true;
		}
		else
		{
			mat->m_blending = false;
		}
	}
	else
	{
		mat->m_blending = false;
	}

	const auto mat_shaders = mat_root.find( "shaders" );
	if( mat_shaders == mat_root.cend() )
	{
		logWARNING( "no shaders specified in '{0}'", path );
		return( false );
	}
	else
	{
		std::string shader_vs_path;
		std::string shader_fs_path;

		const auto mat_shader_vs = mat_shaders->find( "vs" );
		if( mat_shader_vs == mat_shaders->cend() )
		{
			logWARNING( "no vertex shader specified in '{0}'", path );
			return( false );
		}
		else
		{
			shader_vs_path = mat_shader_vs->get<std::string>();
		}

		const auto mat_shader_fs = mat_shaders->find( "fs" );
		if( mat_shader_fs == mat_shaders->cend() )
		{
			logWARNING( "no fragment shader specified in '{0}'", path );
			return( false );
		}
		else
		{
			shader_fs_path = mat_shader_fs->get<std::string>();
		}

		const auto shader = m_shaderManager.LoadProgram( shader_vs_path, shader_fs_path );

		mat->m_shader = shader;

		const auto mat_textures = mat_root.find( "textures" );
		const auto mat_samplers = mat_root.find( "samplers" );

		if( !shader->RequiredSamplers().empty() )
		{
			if( ( mat_textures == mat_root.cend() )
				||
				mat_textures->empty() )
			{
				logWARNING( "no textures specified in '{0}'", path );
				return( false );
			}
			else
			{
				for( const auto &requiredSampler : shader->RequiredSamplers() )
				{
					const auto location = requiredSampler.first;
					const auto interface = requiredSampler.second;

					const auto mat_texture = mat_textures->find( interface.name );
					if( mat_texture == mat_textures->cend() )
					{
						logWARNING( "required texture for sampler '{0}' not specified in '{1}'", interface.name, path );
						return( false );
					}
					else
					{
						// check that sampler-type and type of texture match

						const std::shared_ptr< const CTexture > texture = m_textureManager.LoadTexture( mat_texture->get<std::string>() );

						#pragma clang diagnostic push
						#pragma clang diagnostic ignored "-Wswitch-enum"
						switch( interface.type )
						#pragma clang diagnostic pop
						{
							case GL_SAMPLER_2D:
								if( texture->Type() != CTexture::type::TEX_2D )
								{
									logWARNING( "required texture for sampler '{0}' has to be of type 2D in '{1}'", interface.name, path );
									return( false );
								}
								break;

							case GL_SAMPLER_CUBE:
								if( texture->Type() != CTexture::type::TEX_CUBE_MAP )
								{
									logWARNING( "required texture for sampler '{0}' has to be of type CUBEMAP in '{1}'", interface.name, path );
									return( false );
								}
								break;

							case GL_SAMPLER_2D_ARRAY:
								if( texture->Type() != CTexture::type::TEX_2D_ARRAY )
								{
									logWARNING( "required texture for sampler '{0}' has to be of type 2D_ARRAY in '{1}'", interface.name, path );
									return( false );
								}
								break;

							default:
								logERROR( "unhandled type '{0}' for sampler '{1}'", glbinding::Meta::getString( interface.type ), interface.name );
								return( false );
						}

						std::shared_ptr< const CSampler > sampler;

						if( mat_samplers != mat_root.cend() )
						{
							const auto mat_sampler = mat_samplers->find( interface.name );
							if( ( mat_sampler != mat_samplers->cend() ) && ( !mat_sampler->empty() ) )
							{
								// TODO check here, if specified sampler fits to the type of the texture
								if( !m_samplerManager.SamplerFromString( mat_sampler->get<std::string>(), sampler ) )
								{
									logDEBUG( "invalid sampler specified for texture '{0}' in '{1}'", interface.name, path );
								}
							}
						}

						// set default samplers where not already set
						if( !sampler )
						{
							switch( texture->Type() )
							{
								case CTexture::type::TEX_2D:
									sampler = m_samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
									break;

								case CTexture::type::TEX_CUBE_MAP:
									sampler = m_samplerManager.SamplerFromType( CSampler::Type::REPEAT_CUBE );
									break;

								case CTexture::type::TEX_2D_ARRAY:
									sampler = m_samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
									break;

								default:
									logWARNING( "unknown type for sampler specified for texture '{0}' in '{1}'", interface.name, path );
									return( false );
							}
						}

						mat->m_samplerData[ location ] = std::make_unique< CMaterialSamplerData >( interface.name, texture, sampler );
					}
				}
			}
		}

		// TODO not only in DEBUG-Builds, but configurable
		#ifdef INQ_DEBUG

		if( shader != m_shaderManager.GetDummyShader() )
		{
			const auto requiredSamplers = shader->RequiredSamplers();

			// check for unused textures
			if( mat_textures != mat_root.cend() )
			{
				for( const auto &textureName : json::iterator_wrapper( (*mat_textures) ) )
				{
					if( std::cend( requiredSamplers ) == std::find_if(	std::cbegin( requiredSamplers ),
																		std::cend( requiredSamplers ),
																		[&]( const auto &vt )
																		{
																			return( vt.second.name == textureName.key() );
																		} ) )
					{
						logWARNING( "unused texture '{0}' in '{1}'", textureName.key(), path );
					}
				}
			}

			// check for unused samplers
			if( mat_samplers != mat_root.cend() )
			{
				for( const auto &samplerName : json::iterator_wrapper( (*mat_samplers) ) )
				{
					if( std::cend( requiredSamplers ) == std::find_if(	std::cbegin( requiredSamplers ),
																		std::cend( requiredSamplers ),
																		[&]( const auto &vt )
																		{
																			return( vt.second.name == samplerName.key() );
																		} ) )
					{
						logWARNING( "unused sampler '{0}' in '{1}'", samplerName.key(), path );
					}
				}
			}
		}
		#endif

		if( !shader->RequiredMaterialUniforms().empty() )
		{
			const auto mat_uniforms = mat_root.find( "uniforms" );
			if(	mat_uniforms == mat_root.cend() )
			{
				logWARNING( "no required uniforms specified in '{0}'", path );
				return( false );
			}
			else
			{
				for( const auto requiredMaterialUniform : shader->RequiredMaterialUniforms() )
				{
					const auto location = requiredMaterialUniform.first;
					const auto interface = requiredMaterialUniform.second;

					const auto mat_uniform = mat_uniforms->find( interface.name );
					if( mat_uniform == mat_uniforms->cend() )
					{
						logWARNING( "required uniform '{0}' not specified in '{1}'", interface.name, path );
						return( false );
					}
					else
					{
						#pragma clang diagnostic push
						#pragma clang diagnostic ignored "-Wswitch-enum"
						switch( interface.type )
						#pragma clang diagnostic pop
						{
							case GL_UNSIGNED_INT:
								if( !mat_uniform->is_number_unsigned() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not of type {2}", interface.name, path, glbinding::Meta::getString( interface.type ) );
									return( false );
								}
								else
								{
									mat->m_materialUniforms[ location ] = std::make_unique< CMaterialUniformUINT >( interface.name, mat_uniform->get<glm::uint>() );
								}
								break;

							case GL_FLOAT:
								if( !mat_uniform->is_number_float() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not of type {2}", interface.name, path, glbinding::Meta::getString( interface.type ) );
									return( false );
								}
								else
								{
									mat->m_materialUniforms[ location ] = std::make_unique< CMaterialUniformFLOAT >( interface.name, mat_uniform->get<glm::float32>() );
								}
								break;

							case GL_FLOAT_VEC4:
								if( !mat_uniform->is_array() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not an array", interface.name, path );
									return( false );
								}
								else if( mat_uniform->size() != 4)
								{
									logWARNING( "uniform '{0}' in '{1}' has not enough oder more than needed values", interface.name, path );
									return( false );
								}
								else
								{
									const auto value0 = (*mat_uniform)[ 0 ];
									const auto value1 = (*mat_uniform)[ 1 ];
									const auto value2 = (*mat_uniform)[ 2 ];
									const auto value3 = (*mat_uniform)[ 3 ];

									if( !value0.is_number_float()
										||
										!value1.is_number_float()
										||
										!value2.is_number_float()
										||
										!value3.is_number_float() )
									{
										logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, path );
										return( false );
									}
									else
									{
										mat->m_materialUniforms[ location ] = std::make_unique< CMaterialUniformFLOATVEC4 >( interface.name, glm::vec4( value0.get<float>(), value1.get<float>(), value2.get<float>(), value3.get<float>() ) );
									}
								}
								break;

							default:
								logWARNING( "uniform '{0}' in '{1}' is of unsupported type {2}", interface.name, path, glbinding::Meta::getString( interface.type ) );
								return( false );
								break;
						}
					}
				}
			}
		}
	}

	return( true );
}

void CMaterialLoader::FromDummy( std::shared_ptr< CMaterial > mat ) const
{
	mat->Reset();

	mat->m_name = "dummy " + std::to_string( ++m_dummyCounter );

	mat->m_shader = m_shaderManager.GetDummyShader();
}
