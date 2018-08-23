#ifndef CCOLOR_HPP
#define CCOLOR_HPP

class CColor
{
public:
	inline CColor( void )
	{
	}

	inline CColor& operator= ( const CColor &c )
	{
		m_r = c.m_r;
		m_g = c.m_g;
		m_b = c.m_b;
		m_a = c.m_a;

		return( *this );
	}

	inline CColor( float pr, float pg, float pb, float pa ) :
		m_r( pr ),
		m_g( pg ),
		m_b( pb ),
		m_a( pa )
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

	inline float r( void ) const
	{
		return( m_r );
	}

	inline float g( void ) const
	{
		return( m_g );
	}

	inline float b( void ) const
	{
		return( m_b );
	}

	inline float a( void ) const
	{
		return( m_a );
	}

protected:
	inline void clamp( void )
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
	float	m_r { 0.0f };
	float	m_g { 0.0f };
	float	m_b { 0.0f };
	float	m_a { 0.0f };
};

#endif // CCOLOR_HPP
