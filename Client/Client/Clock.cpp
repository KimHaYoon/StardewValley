#include "stdafx.h"
#include "Clock.h"
#include "ClockHand.h"
#include "Define.h"

CClock::CClock()
{
}


CClock::~CClock()
{
	Release();
}

HRESULT CClock::Init()
{
	return S_OK;
}


HRESULT CClock::Init(OBJECT_ID eID)
{
	_float fSize = (float)WINCX / 1920.f * 1.8f;

	m_tInfo.vPos = { WINCX - (153.f * fSize) ,153.f * fSize, 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);

	m_pClockHand = CAbstractFactory<CClockHand>::CreateObj(OBJECT_ID_UI);
	if (m_pClockHand == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pClockHand, OBJECT_ID_UI);
	return S_OK;
}

_int CClock::Update(const _float & fTimeDelta)
{
	return NO_EVENT;
}

void CClock::LateUpdate(const _float & fTimeDelta)
{
}

void CClock::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, INFOCLOCK);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(), L"Clock", -1, nullptr, DT_CENTER | DT_TOP, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CClock::Release()
{
}

