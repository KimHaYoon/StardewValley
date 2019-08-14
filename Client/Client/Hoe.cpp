#include "stdafx.h"
#include "Hoe.h"
#include "Terrain.h"
#include "BackTerrain.h"

CHoe::CHoe()
{
}


CHoe::~CHoe()
{
	Release();
}

HRESULT CHoe::Init()
{
	return S_OK;
}


HRESULT CHoe::Init(OBJECT_ID eID)
{
	m_pName = L"Hoe";

	_float fSize = (float)WINCX / 1920.f * 5.f;
	m_tInfo.vPos = { (float)(WINCX) / 19.f, (float)(WINCY)-(30.f * fSize), 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"Hoe";
	SetState(STONE);

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	m_eType = ITEM_TOOL;
	m_eState = ITEM_IDLE;
	m_nCount = 1;
	m_fAngle = 0.f;

	m_nIndex = 3;
	m_nIndexLine = 0;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

void CHoe::SetState(ITEM_GRADE eGrade)
{
	if (eGrade == STONE)
	{
		m_strStateKey = L"Stone_Hoe";
	}
	else if (eGrade == BRONZE)
	{
		m_strStateKey = L"Bronze_Hoe";
	}
	else if (eGrade == IRON)
	{
		m_strStateKey = L"Iron_Hoe";
	}
	else if (eGrade == GOLD)
	{
		m_strStateKey = L"Gold_Hoe";
	}
	else if (eGrade == PURPLE)
	{
		m_strStateKey = L"Purple_Hoe";
	}
}

_int CHoe::Update(const _float & fTimeDelta)
{
	if (m_bActive)
	{

	}
	return NO_EVENT;
}

void CHoe::LateUpdate(const _float & fTimeDelta)
{
	if (m_bActive)
	{
		if (m_eState == ITEM_BACKWARD)
			CObj::MoveFrame(2.f / 5.f * 1.5f);
		else if (m_eState == ITEM_FORWARD)
			CObj::MoveFrame(1.5f);
		else {
			m_fAngle += 2.f;
			CObj::MoveFrame(2.f / 3.f * 1.5f);
		}

		if (m_tFrame.fFrame == 0.f)
		{
			m_bActive = false;
			m_fAngle = 0.f;
		}
	}
}

void CHoe::Render()
{
	_float fSize = (float)WINCX / 1920.f * 5.f;
	m_tInfo.vSize = { fSize, fSize, 0.f };
	CItem::Render();

	if (m_bActive)
	{
		m_tInfo.vPos = CObjectMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
		m_tInfo.vSize = { 1.25f, 1.25f, 0.f };

		_matrix matTrans, matScale, matRotate;
		if (m_eState == ITEM_RIGHT)
			m_tInfo.vPos.x += 8.f;
		else if (m_eState == ITEM_LEFT)
			m_tInfo.vPos.x -= 8.f;
		else if (m_eState == ITEM_BACKWARD)
			m_tInfo.vPos.y -= 8.f;
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		D3DXMatrixRotationZ(&matRotate, m_fAngle / 180.f * 3.141592f);
		if (m_eState == ITEM_LEFT)
			D3DXMatrixRotationY(&matRotate, 180.f / 180.f * 3.141592f);
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

void CHoe::Release()
{
}

void CHoe::Active(const _float& x, const _float& y)
{
	D3DXVECTOR3 vPos = CObjectMgr::GetInstance()->GetPlayer()->GetInfo().vPos;
	vPos -= D3DXVECTOR3(x, y, 0.f);
	m_fAngle = 0.f;
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

	_float length = D3DXVec3Length(&vPos);
	if (length < 60.f) // 땅 개간
	{
		for (auto& iter : CObjectMgr::GetInstance()->GetTerrain())
		{
			if ((iter)->GetFront() == 100)
			{
				vector<TILE*> vTile = dynamic_cast<CTerrain*>(iter)->GetTile();
				for (auto& tile : vTile)
				{
					D3DXVECTOR3 ScrollPos = CScrollMgr::GetScroll();

					if (tile->vPos.x - 8.f - ScrollPos.x < x && tile->vPos.x + 8.f - ScrollPos.x > x
						&& tile->vPos.y - 8.f - ScrollPos.y < y && tile->vPos.y + 8.f - ScrollPos.y > y)
					{
						//cout << tile->byDrawID << endl;
						if (tile->byDrawID >= 668 && tile->byDrawID <= 820)
						{
							tile->byDrawID = 2104;
							m_bActive = true;
						}
						break;
					}
				}
			}
		}
	}

}