#include "stdafx.h"
#include "GameTime.h"

CGameTime::CGameTime()
{
	m_fTime = 0.f;
	m_iHour = 6;
	m_iMin = 0;

	m_iMonth = 1;
	m_iDate = 1;
	m_bChangeDay = false;
}


CGameTime::~CGameTime()
{
}

void CGameTime::Update( const _float & fDeltaTime )
{
	if ( m_bChangeDay )
	{
		m_fTime = 0.f;
		m_iHour = 6;
		m_iMin = 0;
		m_bChangeDay = false;
	}

	m_fTime += fDeltaTime;	

	if ( m_fTime >= 7.f)
	{
		m_iMin += 1;
		m_fTime = 0.f;
	}

	if ( m_iMin == 6 )
	{
		m_iHour += 1;
		m_iMin = 0;
	}

	if ( m_iHour == 24 )
	{
		m_iHour = 0;
		m_iDate += 1;
		m_bChangeDay = true;
	}

	if ( m_iDate == 29 )
	{
		m_iMonth += 1;
		m_iDate = 1;
	}

	char			m_szStr[MIN_STR];
	sprintf_s( m_szStr, "%d, %d  %d:%d0", m_iMonth, m_iDate, m_iHour, m_iMin );

	//swprintf_s( m_szStr, L"%d\t:\t%d", m_iHour, m_iMin);
	//TextOut( NULL, 100, 100, m_szStr, lstrlen( m_szStr ) );
	SetWindowTextA( g_hWnd, m_szStr);
}

void CGameTime::Input()
{
	if ( CKeyMgr::GetInstance()->KeyDown( KEY_PAGEUP ) )
	{
		m_iDate += 1;
		m_bChangeDay = true;
	}
}
