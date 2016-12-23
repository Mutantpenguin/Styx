#include "CMaterialLoader.hpp"

#include <algorithm>

#include <json/json.h>

#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

#include "src/engine/renderer/GLHelper.hpp"

std::shared_ptr< CMaterial > CMaterialLoader::CreateMaterial( CTextureManager &textureManager, CShaderManager &shaderManager, const CSamplerManager &samplerManager, const std::string &identifier, const std::string &definition )
{
	Json::Reader	reader;
	Json::Value		mat_root;

	if( !reader.parse( definition, mat_root ) )
	{
		logWARNING( "failed to parse '{0}' because of {1}", identifier, reader.getFormattedErrorMessages() );
		return( nullptr );
	}

	const Json::Value mat_name = mat_root[ "name" ];

	auto newMaterial = std::make_shared< CMaterial >( mat_name.asString() );

	const Json::Value mat_cullmode = mat_root[ "cullmode" ];
	if( !mat_cullmode.empty() )
	{
		if( ( !mat_cullmode.asString().empty() ) && GLHelper::FaceModeFromString( mat_cullmode.asString(), newMaterial->m_cullfacemode ) )
		{
			newMaterial->m_bCullFace = true;
		}
	}

	const Json::Value mat_polygonmode = mat_root[ "polygonmode" ];
	if( !mat_polygonmode.empty() )
	{
		if( !GLHelper::PolygonModeFromString( mat_polygonmode.asString(), newMaterial->m_polygonmode ) )
		{
			newMaterial->m_polygonmode = GL_FILL;
		}
	}

	const Json::Value mat_blending = mat_root[ "blending" ];
	if( !mat_blending.empty() )
	{
		const Json::Value mat_blendingsrc = mat_blending[ "src" ];
		const Json::Value mat_blendingdst = mat_blending[ "dst" ];
		if( !mat_blendingsrc.empty() && GLHelper::SrcBlendFuncFromString( mat_blendingsrc.asString(), newMaterial->m_blendSrc ) && !mat_blendingdst.empty() && GLHelper::DstBlendFuncFromString( mat_blendingdst.asString(), newMaterial->m_blendDst ) )
		{
			newMaterial->m_blending = true;
		}
		else
		{
			newMaterial->m_blending = false;
		}
	}
	else
	{
		newMaterial->m_blending = false;
	}

	const Json::Value mat_shaders = mat_root[ "shaders" ];
	if( mat_shaders.empty() )
	{
		logWARNING( "no shaders specified in '{0}'", identifier );
		return( nullptr );
	}
	else
	{
		std::string shader_vs_path;
		std::string shader_fs_path;

		const Json::Value mat_shader_vs = mat_shaders[ "vs" ];
		if( mat_shader_vs.empty() )
		{
			logWARNING( "no vertex shader specified in '{0}'", identifier );
			return( nullptr );
		}
		else
		{
			shader_vs_path = mat_shader_vs.asString();
		}

		const Json::Value mat_shader_fs = mat_shaders[ "fs" ];
		if( mat_shader_fs.empty() )
		{
			logWARNING( "no fragment shader specified in '{0}'", identifier );
			return( nullptr );
		}
		else
		{
			shader_fs_path = mat_shader_fs.asString();
		}

		std::shared_ptr< CShaderProgram > shader = shaderManager.LoadProgram( shader_vs_path, shader_fs_path );

		newMaterial->m_shader = shader;

		const Json::Value mat_textures = mat_root[ "textures" ];
		const Json::Value mat_samplers = mat_root[ "samplers" ];

		if( !shader->RequiredSamplers().empty() )
		{
			if(	mat_textures.empty() )
			{
				logWARNING( "no textures specified in '{0}'", identifier );
				return( nullptr );
			}
			else
			{
				for( const auto &requiredSampler : shader->RequiredSamplers() )
				{
					const auto location = requiredSampler.first;
					const auto interface = requiredSampler.second;

					const Json::Value mat_texture = mat_textures[ interface.name ];
					if( mat_texture.empty() )
					{
						logWARNING( "required texture for sampler '{0}' not specified in '{1}'", interface.name, identifier );
						return( nullptr );
					}
					else
					{
						// check that sampler-type and type of texture match

						const std::shared_ptr< const CTexture > texture = textureManager.LoadTexture( mat_texture.asString() );

						switch( interface.type )
						{
							case GL_SAMPLER_2D:
								if( texture->Type() != CTexture::type::TEX_2D )
								{
									logWARNING( "required texture for sampler '{0}' has to be of type 2D in '{1}'", interface.name, identifier );
									return( nullptr );
								}
								break;

							case GL_SAMPLER_CUBE:
								if( texture->Type() != CTexture::type::TEX_CUBE_MAP )
								{
									logWARNING( "required texture for sampler '{0}' has to be of type CUBEMAP in '{1}'", interface.name, identifier );
									return( nullptr );
								}
								break;

							case GL_SAMPLER_2D_ARRAY:
								if( texture->Type() != CTexture::type::TEX_2D_ARRAY )
								{
									logWARNING( "required texture for sampler '{0}' has to be of type 2D_ARRAY in '{1}'", interface.name, identifier );
									return( nullptr );
								}
								break;

							default:
								logERROR( "unhandled type '{0}' for sampler '{1}'", glbinding::Meta::getString( interface.type ), interface.name );
								return( nullptr );
						}

						std::shared_ptr< CSampler > sampler;

						const Json::Value mat_sampler = mat_samplers[ interface.name ];
						if( !mat_sampler.empty() )
						{
							// TODO check here, if specified sampler fits to the type of the texture
							if( !samplerManager.SamplerFromString( mat_sampler.asString(), sampler ) )
							{
								logDEBUG( "invalid sampler specified for texture '{0}' in '{1}'", interface.name, identifier );
							}
						}

						// set default samplers where not already set
						if( !sampler )
						{
							switch( texture->Type() )
							{
								case CTexture::type::TEX_2D:
									sampler = samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
									break;

								case CTexture::type::TEX_CUBE_MAP:
									sampler = samplerManager.SamplerFromType( CSampler::Type::REPEAT_CUBE );
									break;

								case CTexture::type::TEX_2D_ARRAY:
									sampler = samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
									break;

								default:
									logWARNING( "unknown type for sampler specified for texture '{0}' in '{1}'", interface.name, identifier );
									return( nullptr );
							}
						}

						newMaterial->m_samplerData[ location ] = std::make_unique< CMaterialSamplerData >( interface.name, texture, sampler );
					}
				}
			}
		}

		// TODO not only in DEBUG-Builds, but configurable
		#ifdef INQ_DEBUG

		if( shader != shaderManager.GetDummyShader() )
		{
			const auto requiredSamplers = shader->RequiredSamplers();

			// check for unused textures
			for( const std::string &textureName : mat_textures.getMemberNames() )
			{
				if( std::end( requiredSamplers ) == std::find_if(	std::begin( requiredSamplers ),
																	std::end( requiredSamplers ),
																	[&]( const auto &vt )
																	{
																		return( vt.second.name == textureName );
																	} ) )
				{
					logWARNING( "unused texture '{0}' in '{1}'", textureName, identifier );
				}
			}

			// check for unused samplers
			for( const std::string &samplerName : mat_samplers.getMemberNames() )
			{
				if( std::end( requiredSamplers ) == std::find_if(	std::begin( requiredSamplers ),
																	std::end( requiredSamplers ),
																	[&]( const auto &vt )
																	{
																		return( vt.second.name == samplerName );
																	} ) )
				{
					logWARNING( "unused sampler '{0}' in '{1}'", samplerName, identifier );
				}
			}
		}
		#endif

		if( !shader->RequiredMaterialUniforms().empty() )
		{
			const Json::Value mat_uniforms = mat_root[ "uniforms" ];
			if(	mat_uniforms.empty() )
			{
				logWARNING( "no required uniforms specified in '{0}'", identifier );
				return( nullptr );
			}
			else
			{
				for( const auto requiredMaterialUniform : shader->RequiredMaterialUniforms() )
				{
					const auto location = requiredMaterialUniform.first;
					const auto interface = requiredMaterialUniform.second;

					const Json::Value mat_uniform = mat_uniforms[ interface.name ];
					if( mat_uniform.empty() )
					{
						logWARNING( "required uniform '{0}' not specified in '{1}'", interface.name, identifier );
						return( nullptr );
					}
					else
					{
						switch( interface.type )
						{
							case GL_UNSIGNED_INT:
								if( !mat_uniform.isUInt() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not of type {2}", interface.name, identifier, glbinding::Meta::getString( interface.type ) );
									return( nullptr );
								}
								else
								{
									newMaterial->m_materialUniforms[ location ] = std::make_unique< CMaterialUniformUINT >( interface.name, mat_uniform.asUInt() );
								}
								break;

							case GL_FLOAT:
								if( !mat_uniform.isDouble() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not of type {2}", interface.name, identifier, glbinding::Meta::getString( interface.type ) );
									return( nullptr );
								}
								else
								{
									newMaterial->m_materialUniforms[ location ] = std::make_unique< CMaterialUniformFLOAT >( interface.name, mat_uniform.asDouble() );
								}
								break;

							case GL_FLOAT_VEC4:
								if( !mat_uniform.isArray() )
								{
									logWARNING( "uniform '{0}' in '{1}' is not an array", interface.name, identifier );
									return( nullptr );
								}
								else if( mat_uniform.size() != 4)
								{
									logWARNING( "uniform '{0}' in '{1}' has not enough oder more than needed values", interface.name, identifier );
									return( nullptr );
								}
								else
								{
									const Json::Value value0 = mat_uniform[ 0 ];
									const Json::Value value1 = mat_uniform[ 1 ];
									const Json::Value value2 = mat_uniform[ 2 ];
									const Json::Value value3 = mat_uniform[ 3 ];

									if( !value0.isDouble()
										||
										!value1.isDouble()
										||
										!value2.isDouble()
										||
										!value3.isDouble() )
									{
										logWARNING( "not all values of uniform '{0}' in '{1}' are floats", interface.name, identifier );
										return( nullptr );
									}
									else
									{
										newMaterial->m_materialUniforms[ location ] = std::make_unique< CMaterialUniformFLOATVEC4 >( interface.name, glm::vec4( value0.asDouble(), value1.asDouble(), value2.asDouble(), value3.asDouble() ) );
									}
								}
								break;

							default:
								logWARNING( "uniform '{0}' in '{1}' is of unsupported type {2}", interface.name, identifier, glbinding::Meta::getString( interface.type ) );
								return( nullptr );
								break;
						}
					}
				}
			}
		}
	}

	return( newMaterial );
}

std::shared_ptr< CMaterial > CMaterialLoader::CreateDummyMaterial( CShaderManager &shaderManager )
{
	auto dummyMaterial = std::make_shared< CMaterial >( "dummy" );

	dummyMaterial->m_shader = shaderManager.GetDummyShader();

	return( dummyMaterial );
}
