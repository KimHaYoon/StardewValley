#include "stdafx.h"
#include "GameTime.h"

_IMPLEMENT_SINGLETON(CGameTime)

CGameTime::CGameTime()
{
	m_fTime = 0.f;
	m_iHour = 6;
	m_iMin = 0;

	m_iMonth = 1;
	m_iDate = 1;
	m_iYear = 1;
	m_bChangeDay = false;
	m_eDay = MONDAY;
}


CGameTime::~CGameTime()
{
}

void CGameTime::Update(const _float & fDeltaTime)
{
	if (m_bChangeDay)
	{
		m_fTime = 0.f;
		m_iHour = 6;
		m_iMin = 0;
		m_bChangeDay = false;

		m_eDay = static_cast<DAY>(static_cast<int>(m_eDay) + 1);
		if (m_eDay > SATURDAY)
			m_eDay = SUNDAY;
	}

	m_fTime += fDeltaTime;

	if (m_fTime >= 7.f)
	{
		m_iMin += 1;
		m_fTime = 0.f;
	}

	if (m_iMin == 6)
	{
		m_iHour += 1;
		m_iMin = 0;
	}

	if (m_iHour == 24)
	{
		m_iHour = 0;
		m_iDate += 1;
		m_bChangeDay = true;
	}

	if (m_iDate == 29)
	{
		m_iMonth += 1;
		m_iDate = 1;
	}

	if (m_iMonth == 13)
	{
		m_iMonth = 1;
		m_iYear++;
	}

	char			m_szStr[MIN_STR];
	sprintf_s(m_szStr, "%d, %d  %d:%d0", m_iMonth, m_iDate, m_iHour, m_iMin);

	//swprintf_s( m_szStr, L"%d\t:\t%d", m_iHour, m_iMin);
	//TextOut( NULL, 100, 100, m_szStr, lstrlen( m_szStr ) );
	SetWindowTextA(g_hWnd, m_szStr);
}

void CGameTime::Input()
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_PAGEUP))
	{
		m_iDate += 1;
		m_bChangeDay = true;
	}
}

int CGameTime::GetCurrentDate() const
{
	return m_iDate;
}

_int CGameTime::GetCurrentMin() const
{
	return m_iMin;
}

_int CGameTime::GetCurrentHour() const
{
	return m_iHour;
}

_int CGameTime::GetCurrentMonth() const
{
	return m_iMonth;
}

_int CGameTime::GetCurrentYear() const
{
	return m_iYear;
}

DAY CGameTime::GetCurrentDay() const
{
	return m_eDay;
}

