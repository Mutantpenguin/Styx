#pragma once

#include "src/core/Types.hpp"

class CColor final
{
public:
	inline CColor()
	{}

	inline CColor& operator= ( const CColor &c )
	{
		m_r = c.m_r;
		m_g = c.m_g;
		m_b = c.m_b;
		m_a = c.m_a;

		return( *this );
	}

	inline CColor( const f16 r, const f16 g, const f16 b, const f16 a ) :
		m_r( r ),
		m_g( g ),
		m_b( b ),
		m_a( a )
	{
		clamp();
	}

	inline CColor( const f16 r, const f16 g, const f16 b ) :
		m_r( r ),
		m_g( g ),
		m_b( b ),
		m_a( 1.0f )
	{
		clamp();
	}

	inline CColor( const CColor &c ) :
		m_r( c.m_r ),
		m_g( c.m_g ),
		m_b( c.m_b ),
		m_a( c.m_a )
	{
	}

	inline f16 r() const
	{
		return( m_r );
	}

	inline f16 g() const
	{
		return( m_g );
	}

	inline f16 b() const
	{
		return( m_b );
	}

	inline f16 a() const
	{
		return( m_a );
	}

protected:
	inline void clamp()
	{
		if( m_r > 1.0f )
		{
			m_r = 1.0f;
		}
		else if( m_r < 0.0f )
		{
			m_r = 0.0f;
		}

		if( m_g > 1.0f )
		{
			m_g = 1.0f;
		}
		else if( m_g < 0.0f )
		{
			m_g = 0.0f;
		}

		if( m_b > 1.0f )
		{
			m_b = 1.0f;
		}
		else if( m_b < 0.0f )
		{
			m_b = 0.0f;
		}

		if( m_a > 1.0f )
		{
			m_a = 1.0f;
		}
		else if( m_a < 0.0f )
		{
			m_a = 0.0f;
		}
	}

	// range 0.0 - 1.0
	f16	m_r { 0.0f };
	f16	m_g { 0.0f };
	f16	m_b { 0.0f };
	f16	m_a { 0.0f };
};
