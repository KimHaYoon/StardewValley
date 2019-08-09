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
	_float fSize = (float)WINCX / 1920.f;

	m_tInfo.vPos = { WINCX / 2.f,WINCY / 2.f,0.f };
	m_tInfo.vSize = { fSize * 1.8f, fSize * 1.8f, 0.f };

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

	m_pItem[0][1] = CAbstractFactory<CAxe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[0][1] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[0][1], OBJECT_ID_UI);
	dynamic_cast<CItem*>(m_pItem[0][1])->SetIndex(0, 1);

	m_pItem[1][5] = CAbstractFactory<CPickaxe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[1][5] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[1][5], OBJECT_ID_UI);
	dynamic_cast<CItem*>(m_pItem[1][5])->SetIndex(1, 5);

	m_pItem[2][8] = CAbstractFactory<CHoe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[2][8] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[2][8], OBJECT_ID_UI);
	dynamic_cast<CItem*>(m_pItem[2][8])->SetIndex(2, 8);

	m_pItem[0][4] = CAbstractFactory<CHoe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[0][4] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[0][4], OBJECT_ID_UI);
	dynamic_cast<CItem*>(m_pItem[0][4])->SetIndex(0, 4);

	m_pItem[0][7] = CAbstractFactory<CHoe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[0][7] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[0][7], OBJECT_ID_UI);
	dynamic_cast<CItem*>(m_pItem[0][7])->SetIndex(0, 7);

	m_pItem[0][10] = CAbstractFactory<CHoe>::CreateObj(OBJECT_ID_UI);
	if (m_pItem[0][10] == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pItem[0][10], OBJECT_ID_UI);
	dynamic_cast<CItem*>(m_pItem[0][10])->SetIndex(0, 10);


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
	if (m_bActive)
	{
		{ // BACKGROUND
			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, BACKGROUND);
			NULL_CHECK_VOID(pTexInfo);

			UNITIFNO tInfo = m_tInfo;
			tInfo.vPos = { (float)WINCX / 2.f, (float)WINCY / 2.f, 0.f };
			tInfo.vSize = { 2.f, 2.f, 0.f };

			_matrix matTrans, matScale;
			D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
			tInfo.matWorld = matScale * matTrans;

			float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(125, 255, 255, 255));
		}

		{ // INVENTORY
			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, INVENTORY);
			NULL_CHECK_VOID(pTexInfo);

			float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		for (int i = 0; i < 6; ++i) // TAB
		{
			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, ITEMTAB + i);
			NULL_CHECK_VOID(pTexInfo);

			UNITIFNO tInfo = m_tInfo;
			float fSize = (float)WINCX / 1920.f;
			if (i == 0)
				tInfo.vPos = { (m_tInfo.vPos.x - (600.f * fSize)) + (90.f * fSize * (i + 1)), (m_tInfo.vPos.y - (361.f * fSize)) - (108.f * fSize), 0.f };
			else
				tInfo.vPos = { (m_tInfo.vPos.x - (600.f * fSize)) + (90.f * fSize * (i + 1)), (m_tInfo.vPos.y - (361.f * fSize)) - (128.f * fSize), 0.f };
			_matrix matTrans, matScale;
			D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
			tInfo.matWorld = matScale * matTrans;

			float CenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float CenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(CenterX, CenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		// CANCEL
		{
			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, CANCEL);
			NULL_CHECK_VOID(pTexInfo);

			UNITIFNO tInfo = m_tInfo;

			float fSize = (float)WINCX / 1920.f;
			tInfo.vPos = { m_tInfo.vPos.x + (650.f * fSize), m_tInfo.vPos.y - (540.f * fSize), 0.f };

			_matrix matTrans, matScale;
			D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
			tInfo.matWorld = matScale * matTrans;

			float CenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float CenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(CenterX, CenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		// UNKNOWN
		{
			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, UNKNOWN);
			NULL_CHECK_VOID(pTexInfo);

			UNITIFNO tInfo = m_tInfo;

			float fSize = (float)WINCX / 1920.f;
			tInfo.vPos = { m_tInfo.vPos.x + (710.f * fSize), m_tInfo.vPos.y - (250.f * fSize), 0.f };

			_matrix matTrans, matScale;
			D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
			tInfo.matWorld = matScale * matTrans;

			float CenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float CenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(CenterX, CenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		//TRASH
		{
			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, TRASH);
			NULL_CHECK_VOID(pTexInfo);

			UNITIFNO tInfo = m_tInfo;

			float fSize = (float)WINCX / 1920.f;
			tInfo.vPos = { m_tInfo.vPos.x + (720.f * fSize), m_tInfo.vPos.y + (100.f * fSize), 0.f };

			_matrix matTrans, matScale;
			D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
			tInfo.matWorld = matScale * matTrans;

			float CenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float CenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(CenterX, CenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	else
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
}

void CInventory::Release()
{
}

void CInventory::Drag(const _float& x, const _float& y)
{
	if (m_bSelect)
		m_pItem[m_nItemIndexLine][m_nItemIndex]->SetPos(x, y);
}

void CInventory::Click(const _float& x, const _float& y)
{
	_float fSize = (float)WINCX / 1920.f;
	if (m_bActive) // 인벤창이 켜져있을 때
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 12; ++j)
			{
				if (m_pItem[i][j])
				{
					_float fx = ((float)(WINCX) / 4.55f) + (WINCX / 19.65f * j);
					_float fy;

					if (i == 0)
						fy = ((float)(WINCY) / 3.75f);
					else
						fy = ((float)(WINCY) / 2.85f) + (WINCY / 14.f * (i - 1));
					D3DXVECTOR3 vPos = { fx, fy, 0.f };

					if (vPos.x - (20.f) < x && vPos.x + (20.f) > x && vPos.y - (20.f) < y && vPos.y + (20.f) > y)
					{
						m_bSelect = true;
						dynamic_cast<CItem*>(m_pItem[i][j])->SelectOn();
						m_nItemIndex = j;
						m_nItemIndexLine = i;
						break;
					}
				}
			}
		}
	}
	else // 퀵슬릇에서만
	{
		for (int i = 0; i < 12; ++i)
		{
			if (m_pItem[0][i])
			{
				//D3DXVECTOR3 vPos = m_pItem[0][i]->GetInfo().vPos;
				D3DXVECTOR3 vPos = { ((float)(WINCX) / 5.15f) + (WINCX / 17.85f * i),
						(float)(WINCY)-(30.f * (float)WINCX / 1920.f * 3.f), 0.f };
				if (vPos.x - (20.f) < x && vPos.x + (20.f) > x && vPos.y - (20.f) < y && vPos.y + (20.f) > y)
				{
					m_bSelect = true;
					dynamic_cast<CItem*>(m_pItem[0][i])->SelectOn();
					m_nItemIndex = i;
					m_nItemIndexLine = 0;
					break;
				}
			}
		}
	}
}

void CInventory::EndClick(const _float& x, const _float& y)
{
	if (m_pItem[m_nItemIndexLine][m_nItemIndex])
	{
		if (m_bActive) // 인벤창이 켜져있을 때
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 12; ++j)
				{
					if (i == m_nItemIndexLine && j == m_nItemIndex)
						continue;
					_float fx = ((float)(WINCX) / 4.55f) + (WINCX / 19.65f * j);
					_float fy;

					if (i == 0)
						fy = ((float)(WINCY) / 3.75f);
					else
						fy = ((float)(WINCY) / 2.85f) + (WINCY / 14.f * (i - 1));
					D3DXVECTOR3 vPos = { fx, fy, 0.f };

					if (vPos.x - (20.f / 1.25f) < x && vPos.x + (20.f / 1.25f) > x && vPos.y - (20.f / 1.25f) < y && vPos.y + (20.f / 1.25f) > y)
					{
						CObj* tTempItem = m_pItem[i][j];
						m_pItem[i][j] = m_pItem[m_nItemIndexLine][m_nItemIndex];
						m_pItem[m_nItemIndexLine][m_nItemIndex] = tTempItem;
						if (m_pItem[m_nItemIndexLine][m_nItemIndex])
							dynamic_cast<CItem*>(m_pItem[m_nItemIndexLine][m_nItemIndex])->SetIndex(m_nItemIndexLine, m_nItemIndex);
						if (m_pItem[i][j])
							dynamic_cast<CItem*>(m_pItem[i][j])->SetIndex(i, j);
						m_nItemIndex = j;
						m_nItemIndexLine = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 12; ++i)
			{
				if (i == m_nItemIndex)
					continue;
				D3DXVECTOR3 vPos = { ((float)(WINCX) / 5.15f) + (WINCX / 17.85f * i),
						(float)(WINCY)-(30.f * (float)WINCX / 1920.f * 3.f), 0.f };

				if (vPos.x - (20.f) < x && vPos.x + (20.f) > x && vPos.y - (20.f) < y && vPos.y + (20.f) > y)
				{
					CObj* tTempItem = m_pItem[0][i];
					m_pItem[0][i] = m_pItem[m_nItemIndexLine][m_nItemIndex];
					m_pItem[m_nItemIndexLine][m_nItemIndex] = tTempItem;
					if (m_pItem[m_nItemIndexLine][m_nItemIndex])
						dynamic_cast<CItem*>(m_pItem[m_nItemIndexLine][m_nItemIndex])->SetIndex(m_nItemIndexLine, m_nItemIndex);
					if (m_pItem[0][i])
						dynamic_cast<CItem*>(m_pItem[0][i])->SetIndex(0, i);
					m_nItemIndex = i;
					m_nItemIndexLine = 0;
					break;
				}
			}
		}
		//CItem* pItem = dynamic_cast<CItem*>(m_pItem[m_nItemIndexLine][m_nItemIndex]);
		//pItem->SetIndex(m_nOrginIndexLine, m_nOrginIndex);
		dynamic_cast<CItem*>(m_pItem[m_nItemIndexLine][m_nItemIndex])->SelectOff();
		m_nItemIndex = -1;
		m_nItemIndexLine = -1;
	}
	m_bSelect = false;
}

void CInventory::ActiveItem(const _float& x, const _float& y)
{
	if (m_pItem[0][m_nSelect])
		dynamic_cast<CItem*>(m_pItem[0][m_nSelect])->Active(x, y);
}