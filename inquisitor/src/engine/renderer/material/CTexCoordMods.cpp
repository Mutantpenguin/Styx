#include "CTexCoordMods.hpp"

const glm::mat3 &CTexCoordMod::Update( const float )
{
	return( m_mat );
}

// ROTATION
CTexCoordModRotate::CTexCoordModRotate( float deg ) :
	m_rad { glm::radians( deg ) }
{
}

const glm::mat3 &CTexCoordModRotate::Update( const float delta )
{
	m_radCurrent += m_rad * delta;

	const float radCurrentCos = glm::cos( m_radCurrent );
	const float radCurrentSin = glm::sin( m_radCurrent );

	m_mat = glm::mat3(	radCurrentCos,		radCurrentSin,	0.0f,
						-1 * radCurrentSin,	radCurrentCos,	0.0f,
						0.0f,				0.0f,			1.0f  );

	return( m_mat );
}

// SCALE
CTexCoordModScale::CTexCoordModScale( float uscale, float vscale )
{
	m_mat = glm::mat3(	1.0f / uscale,	0.0f,			0.0f,
						0.0f,			1.0f / vscale,	0.0f,
						0.0f,			0.0f,			1.0f );
}

// SCROLL
CTexCoordModScroll::CTexCoordModScroll( float uspeed, float vspeed ) :
	m_speed { { uspeed, vspeed } }
{
}

const glm::mat3 &CTexCoordModScroll::Update( const float delta )
{
	m_currentscroll[ 0 ] += m_speed[ 0 ] * delta;
	m_currentscroll[ 1 ] += m_speed[ 1 ] * delta;

	// clamp, so coordinates don't continuously get larger, causing problems with hardware limits
	m_currentscroll[ 0 ] = m_currentscroll[ 0 ] - glm::floor( m_currentscroll[ 0 ] );
	m_currentscroll[ 1 ] = m_currentscroll[ 1 ] - glm::floor( m_currentscroll[ 1 ] );

	m_mat = glm::mat3(	1.0f,						0.0f,						0.0f,
						0.0f,						1.0f,						0.0f,
						m_currentscroll[ 0 ],		m_currentscroll[ 1 ],		1.0f );

	return( m_mat );
}

// MOVE
CTexCoordModMove::CTexCoordModMove( float umove, float vmove )
{
	m_mat = glm::mat3(	1.0f,	0.0f,	0.0f,
						0.0f,	1.0f,	0.0f,
						umove,	vmove,	1.0f );
}
