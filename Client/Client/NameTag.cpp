#include "stdafx.h"
#include "NameTag.h"


CNameTag::CNameTag()
{
}


CNameTag::~CNameTag()
{
	Release();
}

HRESULT CNameTag::Init()
{
	return S_OK;
}

_int CNameTag::Update(const _float & fTimeDelta)
{

	return NO_EVENT;
}

void CNameTag::LateUpdate(const _float & fTimeDelta)
{
}

void CNameTag::Render()
{
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();
	m_tInfo.vPos.x = CObjectMgr::GetInstance()->GetNPC(m_pName)->GetInfo().vPos.x;
	m_tInfo.vPos.y = CObjectMgr::GetInstance()->GetNPC(m_pName)->GetInfo().vPos.y - 20.f;

	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x-vScroll.x, m_tInfo.vPos.y-vScroll.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, 6);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rt = {0, 0, 800, 600};

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(), m_pName, -1, &rt, DT_LEFT, D3DCOLOR_ARGB(255, 0, 0, 0));
}


void CNameTag::Release()
{
}

HRESULT CNameTag::Init(_vec3 vPos, _tchar* pName)
{
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_fSpeed = 10.f;

	m_pName = pName;

	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_3);
	return S_OK;
}
