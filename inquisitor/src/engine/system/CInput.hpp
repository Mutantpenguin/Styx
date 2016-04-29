#ifndef CINPUT_HPP
#define CINPUT_HPP

#include <SDL2/SDL.h>

#include "CFileSystem.hpp"
#include "CSettings.hpp"
#include "CTimer.hpp"

class CInput final
{
friend class CEngine;

private:
	CInput( const CInput &rhs ) = delete;
	CInput& operator = ( const CInput &rhs ) = delete;

public:
	int inline MouseDeltaX( void ) const { return( m_dX ); }
	int inline MouseDeltaY( void ) const { return( m_dY ); }

	bool inline KeyDown( int index ) const 			{ return( CurrentKey( index ) && !OldKey( index ) ); }
	bool inline KeyStillDown( int index ) const 	{ return( CurrentKey( index ) && OldKey( index ) ); }
	bool inline KeyUp( int index ) const 			{ return( !CurrentKey( index ) && OldKey( index ) ); }
	bool inline KeyStillUp( int index ) const 		{ return( !CurrentKey( index ) && !OldKey( index ) ); }

	bool inline MouseDown( int button ) const 		{ return( CurrentMouse( button ) && !OldMouse( button ) ); }
	bool inline MouseStillDown( int button ) const 	{ return( CurrentMouse( button ) && OldMouse( button ) ); }
	bool inline MouseUp( int button ) const 		{ return( !CurrentMouse( button ) && OldMouse( button ) ); }
	bool inline MouseStillUp( int button ) const 	{ return( !CurrentMouse( button ) && !OldMouse( button ) ); }

private:
	CInput( const CSettings &settings, const CFileSystem &filesystem );
	~CInput();

	void Update( void );

private:
	int m_keyCount	{ 0 };

	const Uint8	*m_keys		{ nullptr };
	Uint8		*m_oldKeys	{ nullptr };

	int m_dX { 0 };
	int m_dY { 0 };

	unsigned int m_buttons		{ 0 };
	unsigned int m_oldButtons	{ 0 };

private:
	bool inline CurrentKey( int index ) const		{ return( m_keys[ index ] !=0 ); }
	bool inline OldKey( int index ) const 			{ return( m_oldKeys[ index ] !=0 ); }

	bool inline CurrentMouse( int button ) const	{ return( ( m_buttons & SDL_BUTTON( button ) ) != 0 ); }
	bool inline OldMouse( int button ) const		{ return( ( m_oldButtons & SDL_BUTTON( button ) ) != 0 ); }
};

#endif // CINPUT_HPP
