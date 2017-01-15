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
	std::int32_t inline MouseDeltaX( void ) const { return( m_dX ); }
	std::int32_t inline MouseDeltaY( void ) const { return( m_dY ); }

	bool inline KeyDown( std::uint32_t index ) const 			{ return( CurrentKey( index ) && !OldKey( index ) ); }
	bool inline KeyStillDown( std::uint32_t index ) const 	{ return( CurrentKey( index ) && OldKey( index ) ); }
	bool inline KeyUp( std::uint32_t index ) const 			{ return( !CurrentKey( index ) && OldKey( index ) ); }
	bool inline KeyStillUp( std::uint32_t index ) const 		{ return( !CurrentKey( index ) && !OldKey( index ) ); }

	bool inline MouseDown( std::uint32_t button ) const 		{ return( CurrentMouse( button ) && !OldMouse( button ) ); }
	bool inline MouseStillDown( std::uint32_t button ) const 	{ return( CurrentMouse( button ) && OldMouse( button ) ); }
	bool inline MouseUp( std::uint32_t button ) const 		{ return( !CurrentMouse( button ) && OldMouse( button ) ); }
	bool inline MouseStillUp( std::uint32_t button ) const 	{ return( !CurrentMouse( button ) && !OldMouse( button ) ); }

private:
	CInput( const CSettings &settings, const CFileSystem &filesystem );
	~CInput();

	void Update( void );

private:
	std::int32_t m_keyCount	{ 0 };

	const Uint8	* const m_keys	{ nullptr };
	Uint8		*m_oldKeys		{ nullptr };

	std::int32_t m_dX { 0 };
	std::int32_t m_dY { 0 };

	std::uint32_t m_buttons		{ 0 };
	std::uint32_t m_oldButtons	{ 0 };

private:
	bool inline CurrentKey( std::uint32_t index ) const		{ return( m_keys[ index ] !=0 ); }
	bool inline OldKey( std::uint32_t index ) const 		{ return( m_oldKeys[ index ] !=0 ); }

	bool inline CurrentMouse( std::uint32_t button ) const	{ return( ( m_buttons & SDL_BUTTON( button ) ) != 0 ); }
	bool inline OldMouse( std::uint32_t button ) const		{ return( ( m_oldButtons & SDL_BUTTON( button ) ) != 0 ); }
};

#endif // CINPUT_HPP
