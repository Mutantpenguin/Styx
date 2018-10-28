#pragma once

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "src/engine/helper/Types.hpp"

#include "CFileSystem.hpp"
#include "CSettings.hpp"
#include "CTimer.hpp"

class CInput final
{
friend class CEngine;
friend class CEngineInterface;

private:
	CInput( const CInput &rhs ) = delete;
	CInput& operator = ( const CInput &rhs ) = delete;

public:
	i32 inline MouseDeltaX() const { return( m_dX ); }
	i32 inline MouseDeltaY() const { return( m_dY ); }

	bool inline KeyDown( const u32 index ) const 			{ return( CurrentKey( index ) && !OldKey( index ) ); }
	bool inline KeyStillDown( const u32 index ) const 	{ return( CurrentKey( index ) && OldKey( index ) ); }
	bool inline KeyUp( const u32 index ) const 			{ return( !CurrentKey( index ) && OldKey( index ) ); }
	bool inline KeyStillUp( const u32 index ) const 		{ return( !CurrentKey( index ) && !OldKey( index ) ); }

	bool inline MouseDown( const u32 button ) const 		{ return( CurrentMouse( button ) && !OldMouse( button ) ); }
	bool inline MouseStillDown( const u32 button ) const 	{ return( CurrentMouse( button ) && OldMouse( button ) ); }
	bool inline MouseUp( const u32 button ) const 		{ return( !CurrentMouse( button ) && OldMouse( button ) ); }
	bool inline MouseStillUp( const u32 button ) const 	{ return( !CurrentMouse( button ) && !OldMouse( button ) ); }

private:
	CInput( const CSettings &settings, const CFileSystem &filesystem );
	~CInput();

	void Update();

private:
	i32 m_keyCount	{ 0 };

	const Uint8	* const m_keys;
	Uint8		*m_oldKeys;

	i32 m_dX { 0 };
	i32 m_dY { 0 };

	u32 m_buttons		{ 0 };
	u32 m_oldButtons	{ 0 };

private:
	bool inline CurrentKey( const u32 index ) const	{ return( m_keys[ index ] !=0 ); }
	bool inline OldKey( const u32 index ) const 		{ return( m_oldKeys[ index ] !=0 ); }

	bool inline CurrentMouse( const u32 button ) const	{ return( ( m_buttons & SDL_BUTTON( button ) ) != 0 ); }
	bool inline OldMouse( const u32 button ) const		{ return( ( m_oldButtons & SDL_BUTTON( button ) ) != 0 ); }
};
