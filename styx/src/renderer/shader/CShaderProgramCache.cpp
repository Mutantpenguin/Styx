#include "CShaderProgramCache.hpp"

void CShaderProgramCache::Load( const std::shared_ptr< CShaderProgram > &resource, const CShaderProgram::ResourceIdType &id ) const
{
	resource->VertexShader = m_resources.Get<CShader>( id.vertexShader );

	if( !std::empty( id.geometryShader ) )
	{
		resource->GeometryShader = m_resources.Get<CShader>( id.geometryShader );
	}

	resource->FragmentShader = m_resources.Get<CShader>( id.fragmentShader );

	if( !m_shaderProgramCompiler.Compile( resource ) )
	{
		logWARNING( "program object from '{0}' is not valid", CShaderProgram::IdToString( id ) );

		resource->VertexShader = m_shaderCompiler.DummyVertexShader();
		
		resource->GeometryShader = nullptr;

		resource->FragmentShader = m_shaderCompiler.DummyFragmentShader();
		
		m_shaderProgramCompiler.Compile( resource );
	}
}
