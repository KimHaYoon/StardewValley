#include "stdafx.h"
#include "ClockHand.h"
#include "Define.h"
#include "GameTime.h"

CClockHand::CClockHand()
{
}


CClockHand::~CClockHand()
{
	Release();
}

HRESULT CClockHand::Init()
{
	return S_OK;
}


HRESULT CClockHand::Init(OBJECT_ID eID)
{
	_float fSize = (float)WINCX / 1920.f * 1.8f;

	m_tInfo.vPos = { WINCX - (215.f * fSize), 92.f * fSize, 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	m_fAngle = 0.f;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CClockHand::Update(const _float & fTimeDelta)
{
	_int iHour = CGameTime::GetInstance()->GetCurrentHour();
	_int iMin = CGameTime::GetInstance()->GetCurrentMin();
	m_fAngle = 180.f / 24.f * (float)iHour;
	m_fAngle += 180.f / 24.f / 6.f * (float)iMin;
	return NO_EVENT;
}

void CClockHand::LateUpdate(const _float & fTimeDelta)
{
}

void CClockHand::Render()
{
	_matrix matTrans, matScale, matRotate;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRotate, m_fAngle / 180.f * 3.141592f);
	m_tInfo.matWorld = matScale * matRotate * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, CLOCKHANDLE);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, 12.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CClockHand::Release()
{
}

