#include "stdafx.h"
#include "QuickSlot.h"


CQuickSlot::CQuickSlot()
{
}


CQuickSlot::~CQuickSlot()
{
	Release();
}


HRESULT CQuickSlot::Init()
{
	m_tInfo.vSize = { 400.f,300.f,0.f };
	m_strObjectKey = L"UI";
	m_strStateKey = L"TextBox";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CQuickSlot::Update(const _float & fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;
	return NO_EVENT;
}

void CQuickSlot::LateUpdate(const _float & fTimeDelta)
{
}

void CQuickSlot::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, 0);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 125));


	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(), L"QuickSlot", -1, nullptr, DT_CENTER | DT_TOP, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CQuickSlot::Release()
{
}

HRESULT CQuickSlot::Init(OBJECT_ID eID)
{
	m_tInfo.vPos = { 400.f,550.f,0.f };
	m_tInfo.vSize = { 3.f,1.5f,0.f };
	m_strObjectKey = L"UI";
	m_strStateKey = L"TextBox";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

