#pragma once

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#else
	#error "unsupported platform"
#endif

#include "src/core/Types.hpp"

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
	s32 inline MouseX() const { return( m_mouseX ); }
	s32 inline MouseY() const { return( m_mouseY ); }
	
	s32 inline MouseDeltaX() const { return( m_mouseDeltaX ); }
	s32 inline MouseDeltaY() const { return( m_mouseDeltaY ); }

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
	s32 m_keyCount	{ 0 };

	const Uint8	* const m_keys;
	Uint8		*m_oldKeys;

	s32 m_mouseX { 0 };
	s32 m_mouseY { 0 };

	s32 m_mouseDeltaX { 0 };
	s32 m_mouseDeltaY { 0 };

	u32 m_buttons		{ 0 };
	u32 m_oldButtons	{ 0 };

private:
	bool inline CurrentKey( const u32 index ) const	{ return( m_keys[ index ] !=0 ); }
	bool inline OldKey( const u32 index ) const 		{ return( m_oldKeys[ index ] !=0 ); }

	bool inline CurrentMouse( const u32 button ) const	{ return( ( m_buttons & SDL_BUTTON( button ) ) != 0 ); }
	bool inline OldMouse( const u32 button ) const		{ return( ( m_oldButtons & SDL_BUTTON( button ) ) != 0 ); }
};
