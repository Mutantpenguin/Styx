#pragma once

#include <vector>
#include <tuple>

#include "src/core/Types.hpp"

class CGlyphRange
{
public:
	CGlyphRange() {}

	CGlyphRange( const u32 from, const u32 to );
	
	void Add( const u32 from, const u32 to );
	
	void AddDefault();
	
	std::vector<s32> ToVector() const;

	u32 Count() const;

	static CGlyphRange Default();

private:
	std::vector<std::tuple<s32,s32>> m_ranges;
};
