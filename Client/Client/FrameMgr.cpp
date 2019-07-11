#include "stdafx.h"
#include "FrameMgr.h"

_IMPLEMENT_SINGLETON(CFrameMgr)
CFrameMgr::CFrameMgr()
{
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}


CFrameMgr::~CFrameMgr()
{
}

void CFrameMgr::InitFrame(float framePersec)
{
	m_fSpf = 1.f / framePersec;

	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceFrequency(&m_CpuTick);
}

bool CFrameMgr::LockFrame()
{
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceFrequency(&m_CpuTick);

	m_fDeltaTime = float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;
	m_OldTime = m_CurTime;

	m_fSpfTime += m_fDeltaTime;

	if (m_fSpf <= m_fSpfTime)
	{
		m_fSpfTime = 0.f;
		++m_iFps;
		return true;
	}

	return false;
}

void CFrameMgr::RenderFrame()
{
	m_fFpsTime += CTimerMgr::GetInstance()->GetDeltaTime();

	if (1.f <= m_fFpsTime)
	{
		swprintf_s(m_szFps, L"FPS: %d", m_iFps);
		m_iFps = 0;
		m_fFpsTime = 0.f;
	}

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 600.f, 100.f, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		m_szFps, lstrlen(m_szFps), nullptr, 0, D3DCOLOR_ARGB(255, 0, 255, 0));
}
