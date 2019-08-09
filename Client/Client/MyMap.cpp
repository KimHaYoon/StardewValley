#include "stdafx.h"
#include "MyMap.h"

CMyMap::CMyMap()
{

}
CMyMap::~CMyMap()
{

}
HRESULT CMyMap::Init()
{
	m_tInfo.vPos = { 400.f, 300.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	m_strStateKey = L"Forward_Idle";
	m_tFrame = { 0.f, 10.f };
	return S_OK;
}

_int CMyMap::Update(const _float& fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - vScroll.x, m_tInfo.vPos.y - vScroll.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;
	return NO_EVENT;
}
void CMyMap::LateUpdate(const _float& fTimeDelta)
{
}
void CMyMap::Render()
{

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		L"MapImage", L"Map", m_iMapNum);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CMyMap::Release()
{
	
}

HRESULT CMyMap::Init(OBJECT_ID eID, _int iNum)
{
	m_iMapNum = iNum;
	if (iNum == 0)
	{
		m_tInfo.vPos = { 400.f,300.f,0.f };
		m_tInfo.vSize = { 1.f,1.f,0.f };
	}
	else if (iNum == 6)
	{
		m_tInfo.vPos = { 283.f,237.f,0.f };
		m_tInfo.vSize = { 1.f,1.f,0.f };
	}
	else if (iNum == 10)
	{
		m_tInfo.vPos = {0.f,0.f,0.f};
		m_tInfo.vSize = { 3.f,3.f,0.f };
	}
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_1);
	return S_OK;
}
