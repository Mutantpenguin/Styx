#include "CShaderProgramCache.hpp"

void CShaderProgramCache::Load( const std::shared_ptr< CShaderProgram > &resource, const CShaderProgram::ResourceIdType &id ) const
{
	const auto vertexShader = m_resourceCacheManager.Get<CShader>( id.vertexShader );
	const auto fragmentShader = m_resourceCacheManager.Get<CShader>( id.fragmentShader );

	if( ( nullptr == vertexShader )
		||
		( nullptr == fragmentShader ) )
	{
		logWARNING( "using dummy shader instead of vertex shader '{0}' and fragment shader '{1}'", id.vertexShader, id.fragmentShader );

		m_shaderProgramCompiler.Compile( resource, m_shaderCompiler.DummyVertexShader(), m_shaderCompiler.DummyFragmentShader() );
	}
	else
	{
		if( !m_shaderProgramCompiler.Compile( resource, vertexShader, fragmentShader ) )
		{
			logWARNING( "program object from vertex shader '{0}' and fragment shader '{1}' is not valid", id.vertexShader, id.fragmentShader );

			m_shaderProgramCompiler.Compile( resource, m_shaderCompiler.DummyVertexShader(), m_shaderCompiler.DummyFragmentShader() );
		}
	}
}
