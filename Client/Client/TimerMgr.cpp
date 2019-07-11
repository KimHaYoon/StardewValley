#include "stdafx.h"
#include "TimerMgr.h"

_IMPLEMENT_SINGLETON(CTimerMgr)
CTimerMgr::CTimerMgr()
{
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}



CTimerMgr::~CTimerMgr()
{
}

void CTimerMgr::InitTime()
{
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceFrequency(&m_CpuTick);
}

void CTimerMgr::UpdateTime()
{
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceFrequency(&m_CpuTick);

	m_fDeltaTime = float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;
	m_OldTime = m_CurTime;
}
