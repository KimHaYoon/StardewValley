#include "stdafx.h"
#include "Inventory.h"
#include "Define.h"

#include "ItemList.h"

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

	m_tQuickSlot.vSize = { 100.f, 100.f, 0.f };

	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}


HRESULT CInventory::Init(OBJECT_ID eID)
{
	m_nSelect = -1;

	m_tInfo.vPos = { 200.f,250.f,0.f };
	m_tInfo.vSize = { 2.f,1.5f,0.f };

	_float fSize = (float)WINCX / 1920.f;
	m_tQuickSlot.vPos = { (float)WINCX / 2.f, (float)(WINCY)-(100.f * fSize), 0.f };
	m_tQuickSlot.vSize = { fSize, fSize, 0.f };

	m_tSelectSlot.vPos = { (float)(WINCX) / 19.f, (float)(WINCY)-(100.f * fSize), 0.f };
	m_tSelectSlot.vSize = { fSize, fSize, 0.f };
	//1366 x 768
	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	D3DXMatrixScaling(&matScale, m_tQuickSlot.vSize.x, m_tQuickSlot.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tQuickSlot.vPos.x, m_tQuickSlot.vPos.y, 0.f);
	m_tQuickSlot.matWorld = matScale * matTrans;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);


	m_pItem[0][0] = CAbstractFactory<CAxe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[0][0] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[0][0], OBJECT_ID_UI);
	dynamic_cast<CAxe*>(m_pItem[0][0])->SetIndex(0);

	m_pItem[0][5] = CAbstractFactory<CPickaxe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[0][5] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[0][5], OBJECT_ID_UI);
	dynamic_cast<CPickaxe*>(m_pItem[0][5])->SetIndex(5);

	m_pItem[0][8] = CAbstractFactory<CHoe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[0][8] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[0][8], OBJECT_ID_UI);
	dynamic_cast<CHoe*>(m_pItem[0][8])->SetIndex(8);


	return S_OK;
}

_int CInventory::Update(const _float & fTimeDelta)
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_ONE))
	{
		if (m_nSelect != 0)
			m_nSelect = 0;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_TWO))
	{
		if (m_nSelect != 1)
			m_nSelect = 1;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_THREE))
	{
		if (m_nSelect != 2)
			m_nSelect = 2;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_FOUR))
	{
		if (m_nSelect != 3)
			m_nSelect = 3;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_FIVE))
	{
		if (m_nSelect != 4)
			m_nSelect = 4;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_SIX))
	{
		if (m_nSelect != 5)
			m_nSelect = 5;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_SEVEEN))
	{
		if (m_nSelect != 6)
			m_nSelect = 6;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_EIGHT))
	{
		if (m_nSelect != 7)
			m_nSelect = 7;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_NINE))
	{
		if (m_nSelect != 8)
			m_nSelect = 8;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_ZERO))
	{
		if (m_nSelect != 9)
			m_nSelect = 9;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_OEM_MINUS))
	{
		if (m_nSelect != 10)
			m_nSelect = 10;
		else
			m_nSelect = -1;
		m_bInput = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_OEM_PLUS))
	{
		if (m_nSelect != 11)
			m_nSelect = 11;
		else
			m_nSelect = -1;
		m_bInput = true;
	}

	if (m_bInput)
	{
		m_tSelectSlot.vPos.x = ((float)(WINCX) / 19.f * ((float)m_nSelect + 1.f)) +
			((float)WINCX / 300.f * (float)m_nSelect);
		_matrix matTrans, matScale;
		D3DXMatrixScaling(&matScale, m_tSelectSlot.vSize.x, m_tSelectSlot.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tSelectSlot.vPos.x, m_tSelectSlot.vPos.y, 0.f);
		m_tSelectSlot.matWorld = matScale * matTrans;
		m_bInput = false;
	}

	return NO_EVENT;
}

void CInventory::LateUpdate(const _float & fTimeDelta)
{
}

void CInventory::Render()
{
	{
		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
			m_strObjectKey, m_strStateKey, QUICKSLOT);
		NULL_CHECK_VOID(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tQuickSlot.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		// =========================================================
		if (m_nSelect != -1)
		{
			pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, SELECTSLOT);
			NULL_CHECK_VOID(pTexInfo);

			fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
			fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tSelectSlot.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		// ==========================================================
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
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		CDevice::GetInstance()->GetFont()->DrawTextW(
			CDevice::GetInstance()->GetSprite(), L"Inventory", -1, nullptr, DT_CENTER | DT_TOP, D3DCOLOR_ARGB(255, 0, 0, 0));
	}
}

void CInventory::Release()
{
}

