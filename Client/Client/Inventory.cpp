#include "stdafx.h"
#include "Inventory.h"


CInventory::CInventory()
{
}


CInventory::~CInventory()
{
	Release();
}

HRESULT CInventory::Init()
{
	m_nSelect = -1;

	m_tInfo.vSize = { 200.f,250.f,0.f };

	m_tQuickSlot.vSize = { 400.f, 550.f, 0.f };

	m_strObjectKey = L"UI";
	m_strStateKey = L"TextBox";
	m_strSlotObjectKey = L"UI";
	m_strSlotStateKey = L"TextBox";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CInventory::Update(const _float & fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	D3DXMatrixScaling(&matScale, m_tQuickSlot.vSize.x, m_tQuickSlot.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tQuickSlot.vPos.x, m_tQuickSlot.vPos.y, 0.f);
	m_tQuickSlot.matWorld = matScale * matTrans;
	return NO_EVENT;
}

void CInventory::LateUpdate(const _float & fTimeDelta)
{
}

void CInventory::Render()
{
	{
		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
			m_strObjectKey, m_strStateKey, 0);
		NULL_CHECK_VOID(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tQuickSlot.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 125));


		CDevice::GetInstance()->GetFont()->DrawTextW(
			CDevice::GetInstance()->GetSprite(), L"QuickSlot", -1, nullptr, DT_CENTER | DT_TOP, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	if (m_bActive)
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
			CDevice::GetInstance()->GetSprite(), L"Inventory", -1, nullptr, DT_CENTER | DT_TOP, D3DCOLOR_ARGB(255, 0, 0, 0));
	}
}

void CInventory::Release()
{
}

HRESULT CInventory::Init(OBJECT_ID eID)
{
	m_nSelect = -1;

	m_tInfo.vPos = { 200.f,250.f,0.f };
	m_tInfo.vSize = { 2.f,1.5f,0.f };

	m_tQuickSlot.vPos = { 400.f, 550.f, 0.f };
	m_tQuickSlot.vSize = { 3.f, 1.5f, 0.f };

	m_strObjectKey = L"UI";
	m_strStateKey = L"TextBox";
	m_strSlotObjectKey = L"UI";
	m_strSlotStateKey = L"TextBox";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}
