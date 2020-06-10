#pragma once

#include "src/resource/CResources.hpp"

#include "src/system/CInput.hpp"
#include "src/system/CEngineStats.hpp"

#include "src/system/CTracer.hpp"

#include "src/audio/CAudio.hpp"

#include "src/renderer/sampler/CSamplerManager.hpp"
#include "src/renderer/font/CFontBuilder.hpp"
#include "src/renderer/text/CTextBuilder.hpp"

class CEngineInterface final
{
public:
	CEngineInterface(	CResources			&resources,
						CInput				&input,
						CAudio				&audio,
						const CSamplerManager 	&samplerManager,
						const CFontBuilder		&fontBuilder,
						const CTextBuilder		&textBuilder,
						const CEngineStats		&stats ) :
		Resources { resources },
		Input { input },
		Audio { audio },
		SamplerManager { samplerManager },
		FontBuilder { fontBuilder },
		TextBuilder { textBuilder },
		Stats { stats }
	{}

	CResources &Resources;

	CInput				&Input;

	CAudio				&Audio;
	
	const CSamplerManager	&SamplerManager;
	
	const CFontBuilder		&FontBuilder;
	
	const CTextBuilder		&TextBuilder;
	
	const CEngineStats		&Stats;

	CTracer Trace;

private:
	CEngineInterface( const CEngineInterface &rhs ) = delete;
	CEngineInterface& operator = ( const CEngineInterface &rhs ) = delete;
};
