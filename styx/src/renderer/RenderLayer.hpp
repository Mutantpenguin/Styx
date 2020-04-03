#pragma once

#include <vector>

#include "src/renderer/model/CMesh.hpp"

struct RenderLayer final
{
	struct
	{
		glm::vec3 Position;
		glm::vec3 Direction;
		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ViewProjectionMatrix;
	} View;
	
	struct DrawCommand
	{
		DrawCommand( bool p_blending, const CMesh * p_mesh, const CMaterial * p_material, const CShaderProgram * p_shaderProgram, const glm::mat4 &p_modelMatrix, f16 p_viewDepth ) :
			blending{ p_blending },
			mesh{ p_mesh },
			material{ p_material },
			shaderProgram{ p_shaderProgram },
			modelMatrix{ p_modelMatrix },
			viewDepth{ p_viewDepth }
		{}

		bool blending;
		const CMesh * mesh;
		const CMaterial * material;
		const CShaderProgram * shaderProgram;
		glm::mat4 modelMatrix;
		f16 viewDepth;
	};

	std::vector<RenderLayer::DrawCommand> drawCommands;
	
	void SortDrawCommands();
};

