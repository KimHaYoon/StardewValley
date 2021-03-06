#include "stdafx.h"
#include "Obj.h"
#include "TextBox.h"

CObj::CObj()
{
}

CObj::~CObj()
{
	int i = 0;
}

HRESULT CObj::Init(const _tchar * pFilePath, OBJECT_ID eID)
{
	return S_OK;
}

HRESULT CObj::Init(OBJECT_ID eID)
{
	return S_OK;
}

HRESULT CObj::Init(OBJECT_ID eID, _int iNum)
{
	return E_NOTIMPL;
}

HRESULT CObj::Init(LAYER_ID eID)
{
	return S_OK;
}

HRESULT CObj::Init(_vec3 vPos, _tchar* pName)
{
	return E_NOTIMPL;
}

void CObj::MoveFrame()
{
	m_tFrame.fFrame += m_tFrame.fMax * CTimerMgr::GetInstance()->GetDeltaTime();

	if (m_tFrame.fMax <= m_tFrame.fFrame)
	{
		m_tFrame.fFrame = 0.f;
	}
}

void CObj::MoveFrame(float num)
{
	m_tFrame.fFrame += m_tFrame.fMax * num*CTimerMgr::GetInstance()->GetDeltaTime();

	if (m_tFrame.fMax < m_tFrame.fFrame)
	{
		m_tFrame.fFrame = 0.f;
	}
}

void CObj::MoveFrameStop()
{
	if (m_tFrame.fFrame != m_tFrame.fMax - 1.f)
		m_tFrame.fFrame += m_tFrame.fMax*CTimerMgr::GetInstance()->GetDeltaTime();
	else
		return;

	if (m_tFrame.fMax < m_tFrame.fFrame)
	{
		m_tFrame.fFrame = m_tFrame.fMax - 1.f;
	}
}

