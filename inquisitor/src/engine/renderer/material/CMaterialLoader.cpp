#include "CMaterialLoader.hpp"

#include <algorithm>

#include "src/ext/json/json.hpp"
using json = nlohmann::json;

#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/GLHelper.hpp"

std::uint16_t CMaterialLoader::m_dummyCounter { 0 };

CMaterialLoader::CMaterialLoader( const CFileSystem &filesystem, CShaderManager &shaderManager ) :
	m_filesystem { filesystem },
	m_shaderManager { shaderManager }
{
	logINFO( "material loader was initialized" );
}

CMaterialLoader::~CMaterialLoader( void )
{
	logINFO( "material loader is shutting down" );

	#ifdef INQ_DEBUG
	if( m_dummyCounter > 0 )
	{
		logWARNING( "{0} dummy materials were being created", m_dummyCounter );
	}
	#endif
}

void CMaterialLoader::FromFile( const std::string &path, const std::shared_ptr< CMaterial > &material ) const
{
	if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "material file '{0}' does not exist", path );
		FromDummy( material );
	}
	else
	{
		const std::string fileExtension = path.substr( path.find_last_of( "." ) + 1 );

		if( std::string( "mat" ) == fileExtension )
		{
			try
			{
				if( !FromMatFile( path, material ) )
				{
					FromDummy( material );
				}
			}
			catch( std::exception &e )
			{
				logWARNING( "error loading material '{0}': {1}", path, e.what() );
				FromDummy( material );
			}
		}
		else
		{
			logWARNING( "file is not a material: '{0}'", path );
			FromDummy( material );
		}
	}
}

bool CMaterialLoader::FromMatFile( const std::string &path, const std::shared_ptr< CMaterial > &material ) const
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

	material->Name( mat_name.get<std::string>() );

	const auto mat_cullmode = mat_root.find( "cullmode" );
	if( mat_cullmode != mat_root.cend() )
	{
		GLenum cullfaceMode;

		if( ( !mat_cullmode->get<std::string>().empty() ) && GLHelper::FaceModeFromString( mat_cullmode->get<std::string>(), cullfaceMode ) )
		{
			material->EnableCulling( cullfaceMode );
		}
	}
	else
	{
		material->DisableCulling();
	}

	const auto mat_polygonmode = mat_root.find( "polygonmode" );
	if( mat_polygonmode != mat_root.cend() )
	{
		GLenum polygonmode;

		if( !GLHelper::PolygonModeFromString( mat_polygonmode->get<std::string>(), polygonmode ) )
		{
			material->PolygonMode( polygonmode );
		}
	}

	const auto mat_blending = mat_root.find( "blending" );
	if( mat_blending != mat_root.cend() )
	{
		const auto mat_blendingsrc = mat_blending->find( "src" );
		const auto mat_blendingdst = mat_blending->find( "dst" );

		GLenum	blendSrc;
		GLenum	blendDst;

		if( ( mat_blendingsrc != mat_blending->cend() ) && GLHelper::SrcBlendFuncFromString( mat_blendingsrc->get<std::string>(), blendSrc ) && ( mat_blendingdst != mat_blending->cend() ) && GLHelper::DstBlendFuncFromString( mat_blendingdst->get<std::string>(), blendDst ) )
		{
			material->EnableBlending( blendSrc, blendDst );
		}
		else
		{
			material->DisableBlending();
		}
	}
	else
	{
		material->DisableBlending();
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

		material->Shader( shader );

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
				for( const auto & [ location, interface ] : shader->RequiredMaterialUniforms() )
				{
					const auto mat_uniform = mat_uniforms->find( interface.name );
					if( mat_uniform == mat_uniforms->cend() )
					{
						logWARNING( "required uniform '{0}' not specified in '{1}'", interface.name, path );
						return( false );
					}
					else
					{
						switch( interface.type )
						{
							case GL_UNSIGNED_INT:
								if( !mat_uniform->is_number_unsigned() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not of type {2}", interface.name, path, glbinding::Meta::getString( interface.type ) );
									return( false );
								}
								else
								{
									material->MaterialUniforms().emplace_back( std::make_pair( location, std::make_unique< CMaterialUniformUINT >( interface.name, mat_uniform->get<glm::uint>() ) ) );
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
									material->MaterialUniforms().emplace_back( std::make_pair( location, std::make_unique< CMaterialUniformFLOAT >( interface.name, mat_uniform->get<glm::float32>() ) ) );
								}
								break;

							case GL_FLOAT_VEC2:
							case GL_FLOAT_VEC3:
							case GL_FLOAT_VEC4:
								if( !mat_uniform->is_array() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not an array", interface.name, path );
									return( false );
								}
								else
								{
									const auto &type = interface.type;

									const std::uint8_t requiredAmountOfValues = [&type]
									{
										switch( type )
										{
											case GL_FLOAT_VEC2:
												return( 2 );
											case GL_FLOAT_VEC3:
												return( 3 );
											case GL_FLOAT_VEC4:
												return( 4 );
											default:
												return( 0 );
										}
									}();

									if( mat_uniform->size() != requiredAmountOfValues )
									{
										logWARNING( "uniform '{0}' in '{1}' requires {2} values but got {3}", interface.name, path, requiredAmountOfValues, mat_uniform->size() );
										return( false );
									}
									else
									{
										switch( requiredAmountOfValues )
										{
											case 2:
												{
													const auto value0 = (*mat_uniform)[ 0 ];
													const auto value1 = (*mat_uniform)[ 1 ];

													if( value0.is_number_float()
														&&
														value1.is_number_float() )
													{
														material->MaterialUniforms().emplace_back( std::make_pair( location, std::make_unique< CMaterialUniformFLOATVEC2 >( interface.name, glm::vec2( value0.get<float>(), value1.get<float>() ) ) ) );
													}
													else
													{
														logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, path );
														return( false );
													}
												}
												break;

											case 3:
												{
													const auto value0 = (*mat_uniform)[ 0 ];
													const auto value1 = (*mat_uniform)[ 1 ];
													const auto value2 = (*mat_uniform)[ 2 ];

													if( value0.is_number_float()
														&&
														value1.is_number_float()
														&&
														value2.is_number_float() )
													{
														material->MaterialUniforms().emplace_back( std::make_pair( location, std::make_unique< CMaterialUniformFLOATVEC3 >( interface.name, glm::vec3( value0.get<float>(), value1.get<float>(), value2.get<float>() ) ) ) );
													}
													else
													{
														logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, path );
														return( false );
													}
												}
												break;

											case 4:
												{
													const auto value0 = (*mat_uniform)[ 0 ];
													const auto value1 = (*mat_uniform)[ 1 ];
													const auto value2 = (*mat_uniform)[ 2 ];
													const auto value3 = (*mat_uniform)[ 3 ];

													if( value0.is_number_float()
														&&
														value1.is_number_float()
														&&
														value2.is_number_float()
														&&
														value3.is_number_float() )
													{
														material->MaterialUniforms().emplace_back( std::make_pair( location, std::make_unique< CMaterialUniformFLOATVEC4 >( interface.name, glm::vec4( value0.get<float>(), value1.get<float>(), value2.get<float>(), value3.get<float>() ) ) ) );
													}
													else
													{
														logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, path );
														return( false );
													}
												}
												break;

											default:
												logWARNING( "unhandled amount of values ('{0}') for uniform {1} in {2}", requiredAmountOfValues, interface.name, path );
												return( false );
										}
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

void CMaterialLoader::FromDummy( const std::shared_ptr< CMaterial > &material ) const
{
	material->Reset();

	material->Name( "dummy " + std::to_string( ++m_dummyCounter ) );

	material->Shader( m_shaderManager.GetDummyShader() );
}
