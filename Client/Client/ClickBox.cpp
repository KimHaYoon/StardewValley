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
	m_tInfo.vSize = { 2.f,2.f,0.f };
	m_strObjectKey = L"Menu";
	m_strStateKey = L"UnClickedMenu";
	m_eObjID = eID;
	m_iNumOfTitle = iNum;
	if (iNum == 0)
	{
		m_tInfo.vPos = { 175.f, 500.f,0.f };
	}
	else if (iNum == 1)
	{
		m_tInfo.vPos = { 325.f, 500.f,0.f };
	}
	else if (iNum == 2)
	{
		m_tInfo.vPos = { 475.f, 500.f,0.f };
	}
	else if (iNum == 3)
	{
		m_tInfo.vPos = { 625.f, 500.f,0.f };
	}
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}
