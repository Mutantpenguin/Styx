#pragma once

#include <vector>
#include <tuple>

#include "src/core/Types.hpp"

class CGlyphRange
{
public:
	CGlyphRange() {}
	
	void Add( const u32 from, const u32 to );
	
	void AddDefault();
	
	std::vector<i32> ToVector() const;

	u16 Count() const;

private:
	std::vector<std::tuple<i32,i32>> m_ranges;
};
