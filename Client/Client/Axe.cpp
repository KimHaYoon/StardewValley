#include "stdafx.h"
#include "Axe.h"

CAxe::CAxe()
{
}


CAxe::~CAxe()
{
	Release();
}

HRESULT CAxe::Init()
{
	return S_OK;
}


HRESULT CAxe::Init(OBJECT_ID eID)
{
	m_pName = L"Axe";

	_float fSize = (float)WINCX / 1920.f * 4.f;
	m_tInfo.vPos = { (float)(WINCX) / 19.f, (float)(WINCY)-(30.f * fSize), 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"Axe";

	SetState(STONE);

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	m_eType = ITEM_TOOL;
	m_eState = ITEM_IDLE;
	m_nCount = 1;

	m_nIndex = 1;
	m_nIndexLine = 0;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

void CAxe::SetState(ITEM_GRADE eGrade)
{
	if (eGrade == STONE)
	{
		m_strStateKey = L"Stone_Axe";
	}
	else if (eGrade == BRONZE)
	{
		m_strStateKey = L"Bronze_Axe";
	}
	else if (eGrade == IRON)
	{
		m_strStateKey = L"Iron_Axe";
	}
	else if (eGrade == GOLD)
	{
		m_strStateKey = L"Gold_Axe";
	}
	else if (eGrade == PURPLE)
	{
		m_strStateKey = L"Purple_Axe";
	}
}

_int CAxe::Update(const _float & fTimeDelta)
{
	if (m_bActive)
	{

	}
	return NO_EVENT;
}

void CAxe::LateUpdate(const _float & fTimeDelta)
{
	if (m_bActive)
	{
		if (m_eState == ITEM_BACKWARD)
			CObj::MoveFrame(2.f / 5.f * 1.5f);
		else if (m_eState == ITEM_FORWARD)
			CObj::MoveFrame(1.5f);
		else
			CObj::MoveFrame(2.f / 3.f * 1.5f);

		if (m_tFrame.fFrame == 0.f)
		{
			m_bActive = false;
		}
	}
}

void CAxe::Render()
{
	_float fSize = (float)WINCX / 1920.f * 4.f;
	m_tInfo.vSize = { fSize, fSize, 0.f };
	CItem::Render();

	if (m_bActive)
	{
		m_tInfo.vPos = CObjectMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
		m_tInfo.vSize = { 1.f, 1.f, 0.f };

		_matrix matTrans, matScale, matRotate;
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		if (m_eState == ITEM_LEFT)
			D3DXMatrixRotationY(&matRotate, 180.f);
		else
			D3DXMatrixRotationY(&matRotate, 0.f);
		m_tInfo.matWorld = matScale * matRotate * matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
			m_strObjectKey, m_strStateKey, (_int)m_tFrame.fFrame);
		NULL_CHECK_VOID(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CAxe::Release()
{
}

void CAxe::Active(const _float& x, const _float& y)
{
	D3DXVECTOR3 vPos = CObjectMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
	vPos -= D3DXVECTOR3(x, y, 0.f);
	m_bActive = true;
	if (fabsf(vPos.x) < fabsf(vPos.y))
	{
		if (vPos.y < 0) // 아래
		{
			m_eState = ITEM_FORWARD;
			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 2.f;
			dynamic_cast<CPlayer*>(CObjectMgr::GetInstance()->GetPlayer())->SetDir(3);
		}
		else // 위
		{
			m_eState = ITEM_BACKWARD;
			m_tFrame.fFrame = 3.f;
			m_tFrame.fMax = 5.f;
			dynamic_cast<CPlayer*>(CObjectMgr::GetInstance()->GetPlayer())->SetDir(2);
		}
	}
	else
	{
		if (vPos.x < 0) // 오른쪽
		{
			m_eState = ITEM_RIGHT;
			m_tFrame.fFrame = 2.f;
			m_tFrame.fMax = 3.f;
			dynamic_cast<CPlayer*>(CObjectMgr::GetInstance()->GetPlayer())->SetDir(1);
		}
		else // 왼쪽
		{
			m_eState = ITEM_LEFT;
			m_tFrame.fFrame = 2.f;
			m_tFrame.fMax = 3.f;
			dynamic_cast<CPlayer*>(CObjectMgr::GetInstance()->GetPlayer())->SetDir(0);
		}
	}
}