#include "CMaterialLoader.hpp"

#include <algorithm>

#include <json/json.h>

#include <glbinding/Meta.h>

#include "src/engine/logger/CLogger.hpp"

#include "../GLHelper.hpp"

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

	std::shared_ptr< CMaterial > newMaterial = std::make_shared< CMaterial >( mat_name.asString() );

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

	const Json::Value mat_layers = mat_root[ "layers" ];
	if(	mat_layers.empty() )
	{
		logWARNING( "no layers specified in '{0}'", identifier );
		return( nullptr );
	}
	else
	{
		newMaterial->m_layers.reserve( mat_layers.size() );

		unsigned int layer_index = 0;
		for( const Json::Value &mat_layer : mat_layers )
		{
			++layer_index;

			std::shared_ptr< CMaterialLayer > newLayer = newMaterial->CreateLayer();

			const Json::Value mat_shaders = mat_layer[ "shaders" ];
			if( mat_shaders.empty() )
			{
				logWARNING( "no shader specified in layer '{0}' of '{1}'", layer_index, identifier );
				return( nullptr );
			}
			else
			{
				std::string shader_vs_path;
				std::string shader_fs_path;

				const Json::Value mat_shader_vs = mat_shaders[ "vs" ];
				if( mat_shader_vs.empty() )
				{
					logWARNING( "no vertex shader specified in layer '{0}' of '{1}'", layer_index, identifier );
					return( nullptr );
				}
				else
				{
					shader_vs_path = mat_shader_vs.asString();
				}

				const Json::Value mat_shader_fs = mat_shaders[ "fs" ];
				if( mat_shader_fs.empty() )
				{
					logWARNING( "no fragment shader specified in layer '{0}' of '{1}'", layer_index, identifier );
					return( nullptr );
				}
				else
				{
					shader_fs_path = mat_shader_fs.asString();
				}

				std::shared_ptr< CShaderProgram > shader = shaderManager.LoadProgram( shader_vs_path, shader_fs_path );

				newLayer->m_shader = shader;

				const Json::Value mat_textures = mat_layer[ "textures" ];
				const Json::Value mat_samplers = mat_layer[ "samplers" ];

				if( !shader->m_requiredSamplers.empty() )
				{
					if(	mat_textures.empty() )
					{
						logWARNING( "no textures specified in layer '{0}' of '{1}'", layer_index, identifier );
						return( nullptr );
					}
					else
					{
						for( const auto &requiredSampler : shader->m_requiredSamplers )
						{
							const Json::Value mat_texture = mat_textures[ requiredSampler.second.name ];
							if( mat_texture.empty() )
							{
								logWARNING( "required texture for sampler '{0}' not specified in layer '{1}' of '{2}'", requiredSampler.second.name, layer_index, identifier );
								return( nullptr );
							}
							else
							{
								// check that sampler-type and type of texture match

								const std::shared_ptr< CTexture > texture = textureManager.LoadTexture( mat_texture.asString() );

								switch( requiredSampler.second.type )
								{
									case GL_SAMPLER_2D:
										if( texture->Type() != CTexture::type::TEX_2D )
										{
											logWARNING( "required texture for sampler '{0}' has to be of type 2D in layer '{1}' of '{2}'", requiredSampler.second.name, layer_index, identifier );
											return( nullptr );
										}
										break;

									case GL_SAMPLER_CUBE:
										if( texture->Type() != CTexture::type::TEX_CUBE_MAP )
										{
											logWARNING( "required texture for sampler '{0}' has to be of type CUBEMAP in layer '{1}' of '{2}'", requiredSampler.second.name, layer_index, identifier );
											return( nullptr );
										}
										break;

									case GL_SAMPLER_2D_ARRAY:
										if( texture->Type() != CTexture::type::TEX_2D_ARRAY )
										{
											logWARNING( "required texture for sampler '{0}' has to be of type 2D_ARRAY in layer '{1}' of '{2}'", requiredSampler.second.name, layer_index, identifier );
											return( nullptr );
										}
										break;
								}

								auto &samplerData = newLayer->m_samplerData[ requiredSampler.first ];

								samplerData.first = texture;

								const Json::Value mat_sampler = mat_samplers[ requiredSampler.second.name ];
								if( !mat_sampler.empty() )
								{
									// TODO check here, if specified sampler fits to the type of the texture
									if( !samplerManager.SamplerFromString( mat_sampler.asString(), samplerData.second ) )
									{
										logDEBUG( "invalid sampler specified for texture '{0}' in layer '{1}' of '{2}'", requiredSampler.second.name, layer_index, identifier );
									}
								}

								// set default samplers where not already set
								if( !samplerData.second )
								{
									switch( samplerData.first->Type() )
									{
										case CTexture::type::TEX_2D:
											samplerData.second = samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
											break;

										case CTexture::type::TEX_CUBE_MAP:
											samplerData.second = samplerManager.SamplerFromType( CSampler::Type::REPEAT_CUBE );
											break;

										case CTexture::type::TEX_2D_ARRAY:
											samplerData.second = samplerManager.SamplerFromType( CSampler::Type::REPEAT_2D );
											break;
									}
								}
							}
						}
					}
				}

				// TODO not only in DEBUG-Builds, but configurable
				#ifdef INQ_DEBUG

				// check for unused textures
				for( const std::string &textureName : mat_textures.getMemberNames() )
				{
					if( std::end( shader->m_requiredSamplers ) == std::find_if( std::begin( shader->m_requiredSamplers ),
																				std::end( shader->m_requiredSamplers ),
																				[&]( const auto &vt )
																				{
																					return( vt.second.name == textureName );
																				} ) )
					{
						logWARNING( "unused texture '{0}' in layer '{1}' of '{2}'", textureName, layer_index, identifier );
					}
				}

				// check for unused samplers
				for( const std::string &samplerName : mat_samplers.getMemberNames() )
				{
					if( std::end( shader->m_requiredSamplers ) == std::find_if( std::begin( shader->m_requiredSamplers ),
																				std::end( shader->m_requiredSamplers ),
																				[&]( const auto &vt )
																				{
																					return( vt.second.name == samplerName );
																				} ) )
					{
						logWARNING( "unused sampler '{0}' in layer '{1}' of '{2}'", samplerName, layer_index, identifier );
					}
				}
				#endif

				if( !shader->m_requiredInstanceUniforms.empty() )
				{
					const Json::Value mat_uniforms = mat_layer[ "uniforms" ];
					if(	mat_uniforms.empty() )
					{
						logWARNING( "no required uniforms specified in layer '{0}' of '{1}'", layer_index, identifier );
						return( nullptr );
					}
					else
					{
						for( const auto instanceUniform : shader->m_requiredInstanceUniforms )
						{
							const Json::Value mat_uniform = mat_uniforms[ instanceUniform.second.name ];
							if( mat_uniform.empty() )
							{
								logWARNING( "required uniform '{0}' not specified in layer '{1}' of '{2}'", instanceUniform.second.name, layer_index, identifier );
								return( nullptr );
							}
							else
							{
								switch( instanceUniform.second.type )
								{
									case GL_UNSIGNED_INT:
										if( !mat_uniform.isUInt() )
										{
											logWARNING( "uniform '{0}' in layer '{1}' of '{2}' is not of type {3}", instanceUniform.second.name, layer_index, identifier, glbinding::Meta::getString( instanceUniform.second.type ) );
											return( nullptr );
										}
										else
										{
											newLayer->m_instanceUniforms[ instanceUniform.first ] = std::make_unique< CInstanceUniformUINT >( mat_uniform.asUInt() );
										}
										break;

									case GL_FLOAT_VEC4:
										if( !mat_uniform.isArray() )
										{
											logWARNING( "uniform '{0}' in layer '{1}' of '{2}' is not an array", instanceUniform.second.name, layer_index, identifier );
											return( nullptr );
										}
										else if( mat_uniform.size() != 4)
										{
											logWARNING( "uniform '{0}' in layer '{1}' of '{2}' has not enough oder more than needed values", instanceUniform.second.name, layer_index, identifier );
											return( nullptr );
										}
										else
										{
											Json::Value value0 = mat_uniform[ 0 ];
											Json::Value value1 = mat_uniform[ 1 ];
											Json::Value value2 = mat_uniform[ 2 ];
											Json::Value value3 = mat_uniform[ 3 ];

											if( !value0.isDouble()
												||
												!value1.isDouble()
												||
												!value2.isDouble()
												||
												!value3.isDouble() )
											{
												logWARNING( "not all values of uniform '{0}' in layer '{1}' of '{2}' are floats", instanceUniform.second.name, layer_index, identifier );
												return( nullptr );
											}
											else
											{
												newLayer->m_instanceUniforms[ instanceUniform.first ] = std::make_unique< CInstanceUniformFLOATVEC4 >( glm::vec4( value0.asDouble(), value1.asDouble(), value2.asDouble(), value3.asDouble() ) );
											}
										}
										break;

									default:
										logWARNING( "uniform '{0}' in layer '{1}' of '{2}' is of unsupported type {3}", instanceUniform.second.name, layer_index, identifier, glbinding::Meta::getString( instanceUniform.second.type ) );
										return( nullptr );
										break;
								}
							}
						}
					}
				}
			}

			const Json::Value mat_tcmods = mat_layer[ "tcmods" ];
			if( !mat_tcmods.empty() )
			{
				newLayer->m_texcoordmods.reserve( mat_tcmods.size() );

				for( const Json::Value &mat_tcmod : mat_tcmods )
				{
					if( !mat_tcmod.empty() )
					{
						const std::string mode = mat_tcmod[ "mode" ].asString();

						if( std::string( "SCALE" ) == mode )
						{
							const float uscale = mat_tcmod.get( "uscale", 0.0f ).asDouble();
							const float vscale = mat_tcmod.get( "vscale", 0.0f ).asDouble();
							newLayer->m_texcoordmods.emplace_back( std::make_shared< CTexCoordModScale >( uscale, vscale ) );
						}
						else if( std::string( "SCROLL" ) == mode )
						{
							const float uspeed = mat_tcmod.get( "uspeed", 0.0f ).asDouble();
							const float vspeed = mat_tcmod.get( "vspeed", 0.0f ).asDouble();
							newLayer->m_texcoordmods.emplace_back( std::make_shared< CTexCoordModScroll >( uspeed, vspeed ) );
						}
						else if( std::string( "ROTATE" ) == mode )
						{
							const float deg = mat_tcmod.get( "deg", 0.0f ).asDouble();
							newLayer->m_texcoordmods.emplace_back( std::make_shared< CTexCoordModRotate >( deg ) );
						}
						else if( std::string( "MOVE" ) == mode )
						{
							const float umove = mat_tcmod.get( "umove", 0.0f ).asDouble();
							const float vmove = mat_tcmod.get( "vmove", 0.0f ).asDouble();
							newLayer->m_texcoordmods.emplace_back( std::make_shared< CTexCoordModMove >( umove, vmove ) );
						}
						else
						{
							logWARNING( "unknown tcmod '{0}' in layer '{1}' of '{2}'", mode, layer_index, identifier );
						}
					}
				}
			}
		}
    }

	return( newMaterial );
}
