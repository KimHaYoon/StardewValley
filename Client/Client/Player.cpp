#include "stdafx.h"
#include "Player.h"
#include "ScrollMgr.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Init()
{
	m_bIDLE = true;
	m_tInfo.vPos = { 400.f, 300.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	m_strStateKey = L"Abigail_Forward";
	m_tFrame = { 0.f, 1.f };
	m_fSpeed = WALKSPEED;
	m_fMoveFrame = m_fSpeed / 100.f;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);
	return S_OK;
}

_int CPlayer::Update(const _float& fTimeDelta)
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

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release()
{
}