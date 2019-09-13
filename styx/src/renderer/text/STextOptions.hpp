#pragma once

#include "src/core/Types.hpp"

#include "src/helper/CColor.hpp"

enum class EAnchoringHorizontal : u8
{
	LEFT,
	CENTER,
	RIGHT
};

enum class EAnchoringVertical : u8
{
	TOP,
	CENTER,
	BOTTOM
};

enum class EAlignment : u8
{
	LEFT,
	CENTER,
	RIGHT
};

struct STextOptions final
{
	u16 LineSpacing;

	CColor Color;

	EAnchoringHorizontal HorizontalAnchoring = EAnchoringHorizontal::LEFT;
	EAnchoringVertical VerticalAnchoring = EAnchoringVertical::TOP;

	// TODO Alignment
	EAlignment Alignment = EAlignment::LEFT;

	// TODO MaxWidth
	u16 MaxWidth;

	bool RichText = true;
};