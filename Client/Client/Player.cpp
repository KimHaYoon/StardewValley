#include "stdafx.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Clock.h"
#include "EnergyGauge.h"
CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Init()
{
	m_bIDLE = true;
	m_tInfo.vPos = { WINCX / 2.f, WINCY / 2.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	m_strStateKey = L"Abigail_Forward";
	m_tFrame = { 0.f, 1.f };
	m_fSpeed = WALKSPEED;
	m_fMoveFrame = m_fSpeed / 100.f;
	m_bDrag = false;
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	m_pEquip = CAbstractFactory<CEquipment>::CreateObj(OBJECT_ID_UI);
	if (nullptr == m_pEquip)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pEquip, OBJECT_ID_NPC);

	m_pClock = CAbstractFactory<CClock>::CreateObj(OBJECT_ID_UI);
	if (m_pClock == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pClock, OBJECT_ID_UI);

	m_pEnergyGauge = CAbstractFactory<CEnergyGauge>::CreateObj(OBJECT_ID_UI);
	if (m_pEnergyGauge == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pEnergyGauge, OBJECT_ID_UI);

	m_pInven = CAbstractFactory<CInventory>::CreateObj(OBJECT_ID_UI);
	if (m_pInven == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pInven, OBJECT_ID_UI);

	return S_OK;
}


HRESULT CPlayer::Init(OBJECT_ID eID)
{
	m_bIDLE = true;
	m_tInfo.vPos = { WINCX / 2.f, WINCY / 2.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	m_strStateKey = L"Abigail_Forward";
	m_tFrame = { 0.f, 1.f };
	m_fSpeed = WALKSPEED;
	m_fMoveFrame = m_fSpeed / 100.f;
	m_eObjID = eID;
	m_ObjCollSize = { 16.f, 32.f, 0.f };
	m_bDrag = false;
	m_bPause = false;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	m_pEquip = CAbstractFactory<CEquipment>::CreateObj(OBJECT_ID_UI);
	if (nullptr == m_pEquip)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pEquip, OBJECT_ID_NPC);

	m_pClock = CAbstractFactory<CClock>::CreateObj(OBJECT_ID_UI);
	if (m_pClock == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pClock, OBJECT_ID_UI);

	m_pEnergyGauge = CAbstractFactory<CEnergyGauge>::CreateObj(OBJECT_ID_UI);
	if (m_pEnergyGauge == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pEnergyGauge, OBJECT_ID_UI);

	m_pInven = CAbstractFactory<CInventory>::CreateObj(OBJECT_ID_UI);
	if (m_pInven == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pInven, OBJECT_ID_UI);

	return S_OK;
}

_int CPlayer::Update(const _float& fTimeDelta)
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_LBUTTON))
	{
		if (m_pEquip && m_bPause)
			dynamic_cast<CEquipment*>(m_pEquip)->SetActive();
		m_bDrag = true;
		Click();
	}
	if (CKeyMgr::GetInstance()->KeyUp(KEY_LBUTTON))
	{
		m_bDrag = false;
		EndClick();
	}
	if (m_bDrag)
		Drag();


	if (CKeyMgr::GetInstance()->KeyDown(KEY_I))
	{
		dynamic_cast<CInventory*>(m_pInven)->Active();
		m_bPause = !m_bPause;
	}

	if (!m_bPause)
	{
		m_fTime += fTimeDelta;

		/*if (CKeyMgr::GetInstance()->KeyDown(KEY_W) || CKeyMgr::GetInstance()->KeyDown(KEY_A)
			|| CKeyMgr::GetInstance()->KeyDown(KEY_S) || CKeyMgr::GetInstance()->KeyDown(KEY_D))
		{
			m_bIDLE = false;
			m_tFrame.fMax = 4.f;
		}*/
		if (CKeyMgr::GetInstance()->KeyUp(KEY_W) || CKeyMgr::GetInstance()->KeyUp(KEY_A)
			|| CKeyMgr::GetInstance()->KeyUp(KEY_S) || CKeyMgr::GetInstance()->KeyUp(KEY_D))
		{
			m_fTime = 0.f;
			m_tFrame.fMax = 1.f;
			m_bIDLE = true;
		}

		if (CKeyMgr::GetInstance()->KeyDown(KEY_SHIFT))
		{
			m_fSpeed = RUNSPEED;
			m_fMoveFrame = m_fSpeed / 100.f;
		}
		if (CKeyMgr::GetInstance()->KeyUp(KEY_SHIFT))
		{
			m_fSpeed = WALKSPEED;
			m_fMoveFrame = m_fSpeed / 100.f;
		}

		if (CKeyMgr::GetInstance()->KeyPressing(KEY_W))
		{
			//m_tInfo.vPos.y -= m_fSpeed * fTimeDelta;
			m_bIDLE = false;
			m_tFrame.fMax = 4.f;
			D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
			vPos.y -= m_fSpeed * fTimeDelta;
			CScrollMgr::SetScroll(vPos);
			m_strStateKey = L"Abigail_Back";

		}
		if (CKeyMgr::GetInstance()->KeyPressing(KEY_S))
		{
			//m_tInfo.vPos.y += m_fSpeed * fTimeDelta;
			m_bIDLE = false;
			m_tFrame.fMax = 4.f;
			D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
			vPos.y += m_fSpeed * fTimeDelta;
			CScrollMgr::SetScroll(vPos);
			m_strStateKey = L"Abigail_Forward";
		}
		if (CKeyMgr::GetInstance()->KeyPressing(KEY_A))
		{
			//m_tInfo.vPos.x -= m_fSpeed * fTimeDelta;
			m_bIDLE = false;
			m_tFrame.fMax = 4.f;
			D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
			vPos.x -= m_fSpeed * fTimeDelta;
			CScrollMgr::SetScroll(vPos);
			m_strStateKey = L"Abigail_Left";

		}
		if (CKeyMgr::GetInstance()->KeyPressing(KEY_D))
		{
			//m_tInfo.vPos.x += m_fSpeed * fTimeDelta;
			m_bIDLE = false;
			m_tFrame.fMax = 4.f;
			D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
			vPos.x += m_fSpeed * fTimeDelta;
			CScrollMgr::SetScroll(vPos);
			m_strStateKey = L"Abigail_Right";
		}


		if (m_bIDLE && m_fTime > 5.f && m_strStateKey == L"Abigail_Forward")
		{
			m_strStateKey = L"Abigail_IDLE";
			m_tFrame.fMax = 4.f;
		}
		if (m_bIDLE && m_fTime > 7.f)
		{
			m_strStateKey = L"Abigail_Forward";
			m_tFrame.fMax = 1.f;
			m_fTime = 0.f;
		}
	}

	return NO_ERROR;
}

void CPlayer::LateUpdate(const _float& fTimeDelta)
{
	CObj::MoveFrame(m_fMoveFrame);
}

void CPlayer::Render()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f);
	m_tInfo.matWorld = matScale * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		L"Abigail", m_strStateKey, (_int)m_tFrame.fFrame);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release()
{
	SafeDelete(m_pEquip);
}

bool CPlayer::GetInventoryState()
{
	return dynamic_cast<CInventory*>(m_pInven)->GetActive();
}


void CPlayer::Drag()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	dynamic_cast<CInventory*>(m_pInven)->Drag((float)pt.x, (float)pt.y);
}

void CPlayer::Click()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	dynamic_cast<CInventory*>(m_pInven)->Click((float)pt.x, (float)pt.y);
}

void CPlayer::EndClick()
{
	dynamic_cast<CInventory*>(m_pInven)->EndClick();
}