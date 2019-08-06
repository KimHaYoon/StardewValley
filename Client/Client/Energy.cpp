#include "stdafx.h"
#include "Energy.h"
#include "Define.h"

CEnergy::CEnergy()
{
}


CEnergy::~CEnergy()
{
	Release();
}

HRESULT CEnergy::Init()
{
	return S_OK;
}


HRESULT CEnergy::Init(OBJECT_ID eID)
{
	_float fSize = (float)WINCX / 1920.f * 1.8f;
	m_fMaxEnergyScale = fSize * 1.2f;
	m_fEnergy = 1000.f;
	m_tInfo.vPos = { WINCX - (35.f * fSize), WINCY - (20.5f * fSize), 0.f };
	m_tInfo.vSize = { fSize, m_fMaxEnergyScale, 0.f };

	//1366 x 768
	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CEnergy::Update(const _float & fTimeDelta)
{
	m_tInfo.vSize.y = m_fMaxEnergyScale / 1000.f * m_fEnergy;
	m_fEnergy -= 1.f;
	if (m_fEnergy <= 0.f)
	{
		m_tInfo.vSize.y = m_fMaxEnergyScale;
		m_fEnergy = 1000.f;
	}
	return NO_EVENT;
}

void CEnergy::LateUpdate(const _float & fTimeDelta)
{
}

void CEnergy::Render()
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, ENERGY);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = (float)pTexInfo->tImgInfo.Height;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CEnergy::Release()
{
}

