#include <vector>

#include "src/renderer/model/CMesh.hpp"

struct DrawCommand
{
	DrawCommand( const CMesh * p_mesh, const CMaterial * p_material, const CShaderProgram * p_shaderProgram, const glm::mat4 &p_modelMatrix, f16 p_viewDepth ) :
		mesh{ p_mesh },
		material{ p_material },
		shaderProgram{ p_shaderProgram },
		modelMatrix { p_modelMatrix },
		viewDepth{ p_viewDepth }
	{}

	const CMesh * mesh;
	const CMaterial * material;
	const CShaderProgram * shaderProgram;
	glm::mat4 modelMatrix;
	f16 viewDepth;
};

using DrawCommandList = std::vector<DrawCommand>;