#pragma once

#include "src/resource/CResources.hpp"

#include "src/system/CInput.hpp"
#include "src/system/CEngineStats.hpp"

#include "src/audio/CAudio.hpp"

#include "src/renderer/sampler/CSamplerManager.hpp"
#include "src/renderer/font/CFontBuilder.hpp"
#include "src/renderer/text/CTextMeshBuilder.hpp"

class CEngineInterface final
{
public:
	CEngineInterface(	CResources			&resources,
						CInput				&input,
						CAudio				&audio,
						CSamplerManager 	&samplerManager,
						CFontBuilder		&fontBuilder,
						CTextMeshBuilder	&textMeshBuilder,
						const CEngineStats	&stats ) :
		Resources { resources },
		Input { input },
		Audio { audio },
		SamplerManager { samplerManager },
		FontBuilder { fontBuilder },
		TextMeshBuilder { textMeshBuilder },
		Stats { stats }
	{}

	CResources &Resources;

	CInput				&Input;
	CAudio				&Audio;
	CSamplerManager 	&SamplerManager;
	CFontBuilder		&FontBuilder;
	CTextMeshBuilder	&TextMeshBuilder;
	
	const CEngineStats	&Stats;

private:
	CEngineInterface( const CEngineInterface &rhs ) = delete;
	CEngineInterface& operator = ( const CEngineInterface &rhs ) = delete;
};
