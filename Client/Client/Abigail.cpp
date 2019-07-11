#include "stdafx.h"
#include "Abigail.h"


CAbigail::CAbigail()
{
}


CAbigail::~CAbigail()
{
}

HRESULT CAbigail::Init()
{
	return S_OK;
}

_int CAbigail::Update(const _float & fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CAbigail::LateUpdate(const _float & fTimeDelta)
{

}

void CAbigail::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(L"Abigail", m_strStateKey,
		(int)m_tFrame.fFrame);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255 , 255, 255, 255));
}

void CAbigail::Release()
{
}
