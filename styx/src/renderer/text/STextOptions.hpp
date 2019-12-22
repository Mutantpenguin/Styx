#pragma once

#include "src/core/Types.hpp"

#include "src/helper/CColor.hpp"

enum class EHorizontalAnchor : u8
{
	LEFT,
	CENTER,
	RIGHT
};

enum class EVerticalAnchor : u8
{
	TOP,
	CENTER,
	BOTTOM
};

enum class EHorizontalAlign : u8
{
	LEFT,
	CENTER,
	RIGHT
};

struct STextOptions final
{
	u16 LineSpacing = 0;

	CColor Color = Colors::Black();

	EHorizontalAnchor HorizontalAnchor = EHorizontalAnchor::LEFT;
	EVerticalAnchor VerticalAnchor = EVerticalAnchor::TOP;

	EHorizontalAlign HorizontalAlign = EHorizontalAlign::LEFT;

	// TODO MaxWidth
	u16 MaxWidth;

	bool RichText = true;
};