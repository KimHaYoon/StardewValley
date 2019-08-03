#include "stdafx.h"
#include "ClickBox.h"


CClickBox::CClickBox()
{
}


CClickBox::~CClickBox()
{
}

HRESULT CClickBox::Init()
{
	return S_OK;
}

_int CClickBox::Update(const _float & fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;


	return NO_EVENT;
}

void CClickBox::LateUpdate(const _float & fTimeDelta)
{
}

void CClickBox::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, m_iNumOfTitle);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CClickBox::Release()
{
}

HRESULT CClickBox::Init(OBJECT_ID eID, _int iNum)
{
	m_tInfo.vPos = { 100.f, 100.f,0.f };
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_strObjectKey = L"Menu";
	m_strStateKey = L"ClickedMenu";
	m_eObjID = eID;
	m_iNumOfTitle = iNum;
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}
