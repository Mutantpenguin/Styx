#include "CMaterialLoader.hpp"

#include <algorithm>

#include "external/json/json.hpp"
using json = nlohmann::json;

#include <glbinding-aux/Meta.h>

#include "src/logger/CLogger.hpp"

#include "src/core/FileExtension.hpp"

#include "src/renderer/GLHelper.hpp"

u16 CMaterialLoader::m_dummyCounter { 0 };

CMaterialLoader::CMaterialLoader( const CFileSystem &filesystem, CResources &resources, const CShaderProgramCompiler &shaderProgramCompiler ) :
	m_filesystem { filesystem },
	m_resources{ resources },
	m_shaderProgramCompiler{ shaderProgramCompiler }
{
	logINFO( "material loader was initialized" );
}

CMaterialLoader::~CMaterialLoader()
{
	logINFO( "material loader is shutting down" );

	#ifdef STYX_DEBUG
	if( m_dummyCounter > 0 )
	{
		logWARNING( "{0} dummy materials were being created", m_dummyCounter );
	}
	#endif
}

void CMaterialLoader::FromFile( const std::shared_ptr<CMaterial> &material, const fs::path &path ) const
{
	if( !path.has_filename() )
	{
		logWARNING( "path '{0}' does not containt a filename", path.generic_string() );
		FromDummy( material );
	}

	const std::string fileExtensionString = path.extension().generic_string();

	if( fileExtensionString != FileExtension::Material::mat )
	{
		logWARNING( "file type '{0}' of material file '{1}' is not supported", fileExtensionString, path.generic_string() );
		FromDummy( material );
	}
	else if( !m_filesystem.Exists( path ) )
	{
		logWARNING( "material file '{0}' does not exist", path.generic_string() );
		FromDummy( material );
	}
	else
	{
		try
		{
			if( !FromMatFile( material, path ) )
			{
				FromDummy( material );
			}
		}
		catch( std::exception &e )
		{
			logWARNING( "error loading material '{0}': {1}", path.generic_string(), e.what() );
			FromDummy( material );
		}
	}
}

bool CMaterialLoader::FromMatFile( const std::shared_ptr<CMaterial> &material, const fs::path &path ) const
{
	json mat_root;

	try
	{
		mat_root = json::parse( m_filesystem.LoadFileToString( path ) );
	}
	catch( json::parse_error &e )
	{
		logWARNING( "failed to parse '{0}' because of {1}", path.generic_string(), e.what() );
		return( false );
	}

	const auto mat_name = mat_root[ "name" ];

	material->Name( mat_name.get<std::string>() );

	const auto mat_cullmode = mat_root.find( "cullmode" );
	if( mat_cullmode != mat_root.end() )
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
	if( mat_polygonmode != mat_root.end() )
	{
		GLenum polygonmode;

		if( !GLHelper::PolygonModeFromString( mat_polygonmode->get<std::string>(), polygonmode ) )
		{
			material->PolygonMode( polygonmode );
		}
	}

	const auto mat_blending = mat_root.find( "blending" );
	if( mat_blending != mat_root.end() )
	{
		const auto mat_blendingsrc = mat_blending->find( "src" );
		const auto mat_blendingdst = mat_blending->find( "dst" );

		GLenum	blendSrc;
		GLenum	blendDst;

		if( ( mat_blendingsrc != mat_blending->end() ) && GLHelper::SrcBlendFuncFromString( mat_blendingsrc->get<std::string>(), blendSrc ) && ( mat_blendingdst != mat_blending->end() ) && GLHelper::DstBlendFuncFromString( mat_blendingdst->get<std::string>(), blendDst ) )
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

	const auto mat_depthmask = mat_root.find( "depthmask" );
	if( mat_depthmask != mat_root.end() )
	{
		if( mat_depthmask->get<bool>() )
		{
			material->EnableDepthMask();
		}
		else
		{
			material->DisableDepthMask();
		}
	}
	else
	{
		material->EnableDepthMask();
	}

	const auto mat_shader = mat_root.find( "shader" );
	if( mat_shader == mat_root.end() )
	{
		logWARNING( "no shader specified in '{0}'", path.generic_string() );
		return( false );
	}
	else
	{
		const auto shaderProgram = m_resources.Get<CShaderProgram>( mat_shader->get<std::string>() );

		material->ShaderProgram( shaderProgram );

		const auto mat_uniforms = mat_root.find( "uniforms" );

		if( !shaderProgram->RequiredMaterialUniforms().empty() )
		{
			if( mat_uniforms == mat_root.end() )
			{
				logWARNING( "no required uniforms specified in '{0}'", path.generic_string() );
				return( false );
			}
			else
			{
				for( const auto & [ location, interface ] : shaderProgram->RequiredMaterialUniforms() )
				{
					const auto mat_uniform = mat_uniforms->find( interface.name );
					if( mat_uniform == mat_uniforms->end() )
					{
						logWARNING( "required uniform '{0}' not specified in '{1}'", interface.name, path.generic_string() );
						return( false );
					}
					else
					{
						switch( interface.type )
						{
							case GL_UNSIGNED_INT:
								if( !mat_uniform->is_number_unsigned() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not of type {2}", interface.name, path.generic_string(), glbinding::aux::Meta::getString( interface.type ) );
									return( false );
								}
								else
								{
									material->AddMaterialUniform<CMaterialUniformUINT>( location, interface.name, mat_uniform->get<glm::uint>() );
								}
								break;

							case GL_FLOAT:
								if( !mat_uniform->is_number_float() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not of type {2}", interface.name, path.generic_string(), glbinding::aux::Meta::getString( interface.type ) );
									return( false );
								}
								else
								{
									material->AddMaterialUniform<CMaterialUniformFLOAT>( location, interface.name, mat_uniform->get<glm::float32>() );
								}
								break;

							case GL_FLOAT_VEC2:
							case GL_FLOAT_VEC3:
							case GL_FLOAT_VEC4:
								if( !mat_uniform->is_array() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not an array", interface.name, path.generic_string() );
									return( false );
								}
								else
								{
									const auto &type = interface.type;

									const u8 requiredAmountOfValues = [&type]
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
										logWARNING( "uniform '{0}' in '{1}' requires {2} values but got {3}", interface.name, path.generic_string(), requiredAmountOfValues, mat_uniform->size() );
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
														material->AddMaterialUniform<CMaterialUniformFLOATVEC2>( location, interface.name, glm::vec2( value0.get<f16>(), value1.get<f16>() ) );
													}
													else
													{
														logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, path.generic_string() );
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
														material->AddMaterialUniform<CMaterialUniformFLOATVEC3>( location, interface.name, glm::vec3( value0.get<f16>(), value1.get<f16>(), value2.get<f16>() ) );
													}
													else
													{
														logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, path.generic_string() );
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
														material->AddMaterialUniform<CMaterialUniformFLOATVEC4>( location, interface.name, glm::vec4( value0.get<f16>(), value1.get<f16>(), value2.get<f16>(), value3.get<f16>() ) );
													}
													else
													{
														logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, path.generic_string() );
														return( false );
													}
												}
												break;

											default:
												logWARNING( "unhandled amount of values ('{0}') for uniform {1} in {2}", requiredAmountOfValues, interface.name, path.generic_string() );
												return( false );
										}
									}
								}
								break;

							default:
								logWARNING( "uniform '{0}' in '{1}' is of unsupported type {2}", interface.name, path.generic_string(), glbinding::aux::Meta::getString( interface.type ) );
								return( false );
								break;
						}
					}
				}
			}
		}
		else
		{
			if( mat_uniforms != mat_root.end() )
			{
				logWARNING( "shaderprogram requires no uniforms but material '{0}' has some specified", path.generic_string() );
			}
		}
	}

	return( true );
}

void CMaterialLoader::FromDummy( const std::shared_ptr<CMaterial> &material ) const
{
	material->Reset();

	material->Name( "dummy " + std::to_string( ++m_dummyCounter ) );
	
	material->ShaderProgram( m_shaderProgramCompiler.DummyShaderProgram() );
}
