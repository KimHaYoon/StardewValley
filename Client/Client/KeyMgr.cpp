#include "stdafx.h"
#include "KeyMgr.h"

_IMPLEMENT_SINGLETON(CKeyMgr)
CKeyMgr::CKeyMgr()
{
}


CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Update()
{
	m_dwKey = 0;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwKey |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwKey |= KEY_RBUTTON;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwKey |= KEY_RETURN;
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_dwKey |= KEY_SHIFT;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT;

	if (GetAsyncKeyState('W') & 0x8000)
		m_dwKey |= KEY_W;
	if (GetAsyncKeyState('A') & 0x8000)
		m_dwKey |= KEY_A;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwKey |= KEY_S;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwKey |= KEY_D;

	if (GetAsyncKeyState('1') & 0x8000)
		m_dwKey |= KEY_ONE;
	if (GetAsyncKeyState('2') & 0x8000)
		m_dwKey |= KEY_TWO;
	if (GetAsyncKeyState('3') & 0x8000)
		m_dwKey |= KEY_THREE;
	if (GetAsyncKeyState('4') & 0x8000)
		m_dwKey |= KEY_FOUR;
	if (GetAsyncKeyState('5') & 0x8000)
		m_dwKey |= KEY_FIVE;
	if (GetAsyncKeyState('6') & 0x8000)
		m_dwKey |= KEY_SIX;
	if (GetAsyncKeyState('7') & 0x8000)
		m_dwKey |= KEY_SEVEEN;
	if (GetAsyncKeyState('8') & 0x8000)
		m_dwKey |= KEY_EIGHT;
	if (GetAsyncKeyState('9') & 0x8000)
		m_dwKey |= KEY_NINE;
	if (GetAsyncKeyState('0') & 0x8000)
		m_dwKey |= KEY_ZERO;
	if (GetAsyncKeyState(VK_OEM_MINUS) & 0x8000)
		m_dwKey |= KEY_OEM_MINUS;
	if (GetAsyncKeyState(VK_OEM_PLUS) & 0x8000)
		m_dwKey |= KEY_OEM_PLUS;

	if (GetAsyncKeyState('I') & 0x8000)
		m_dwKey |= KEY_I;
	if (GetAsyncKeyState('E') & 0x8000)
		m_dwKey |= KEY_E;
	if (GetAsyncKeyState('M') & 0x8000)
		m_dwKey |= KEY_M;

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		m_dwKey |= KEY_ESCAPE;

	if ( GetAsyncKeyState( VK_PRIOR ) & 0x8000 )
		m_dwKey |= KEY_PAGEUP;
	if ( GetAsyncKeyState( VK_NEXT ) & 0x8000 )
		m_dwKey |= KEY_PAGEDOWN;
}

bool CKeyMgr::KeyUp(DWORD dwKey)
{
	if (m_dwKey & dwKey)
	{
		m_dwKeyPressed |= dwKey;
		return false;
	}
	else if (m_dwKeyPressed & dwKey)
	{
		m_dwKeyPressed ^= dwKey;
		return true;
	}

	return false;
}

bool CKeyMgr::KeyDown(DWORD dwKey)
{
	if (!(m_dwKeyDown & dwKey) && (m_dwKey & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	else if (!(m_dwKey & dwKey) && (m_dwKeyDown & dwKey))
	{
		m_dwKeyDown ^= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPressing(DWORD dwKey)
{
	if (m_dwKey & dwKey)
		return true;

	return false;
}

bool CKeyMgr::KeyCombine(DWORD dwFirstKey, DWORD dwSecondKey)
{
	if (KeyDown(dwSecondKey) && (m_dwKey & dwFirstKey))
		return true;

	return false;
}
