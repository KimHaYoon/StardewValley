#include "stdafx.h"
#include "Item.h"
#include "Player.h"


CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::SetIndex(_int line, _int index)
{
	m_nIndexLine = line;  m_nIndex = index;
	/*if (m_nIndexLine == 0)
	{
		m_tInfo.vPos.x = ((float)(WINCX) / 5.15f) + (WINCX / 17.85f * m_nIndex);
		m_tInfo.vPos.y = (float)(WINCY)-(30.f * (float)WINCX / 1920.f * 3.f);
	}
	m_tInfo2 = m_tInfo;

	m_tInfo2.vPos.x = ((float)(WINCX) / 4.55f) + (WINCX / 19.65f * m_nIndex);

	_float fSize = (float)WINCX / 1920.f;

	if (m_nIndexLine == 0)
		m_tInfo2.vPos.y = ((float)(WINCY) / 3.75f);
	else
		m_tInfo2.vPos.y = ((float)(WINCY) / 2.85f) + (WINCY / 14.f * (m_nIndexLine - 1));*/
}

void CItem::Render()
{
	if (dynamic_cast<CPlayer*>(CObjectMgr::GetInstance()->GetPlayer())->GetInventoryState())
	{
		if (!m_bSelect)
		{
			m_tInfo.vPos.x = ((float)(WINCX) / 4.55f) + (WINCX / 19.65f * m_nIndex);

			_float fSize = (float)WINCX / 1920.f;

			if (m_nIndexLine == 0)
				m_tInfo.vPos.y = ((float)(WINCY) / 3.75f);
			else
				m_tInfo.vPos.y = ((float)(WINCY) / 2.85f) + (WINCY / 14.f * (m_nIndexLine - 1));
		}

		_matrix matTrans, matScale;
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x / 1.25f, m_tInfo.vSize.y / 1.25f, 0.f);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
		m_tInfo.matWorld = matScale * matTrans;

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
			m_strObjectKey, m_strStateKey, ITEM_ICON);
		NULL_CHECK_VOID(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		if (m_nIndexLine == 0)
		{
			if (!m_bSelect)
			{
				m_tInfo.vPos.x = ((float)(WINCX) / 5.15f) + (WINCX / 17.85f * m_nIndex);
				m_tInfo.vPos.y = (float)(WINCY)-(30.f * (float)WINCX / 1920.f * 3.f);
			}

			_matrix matTrans, matScale;
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
			m_tInfo.matWorld = matScale * matTrans;

			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_strObjectKey, m_strStateKey, ITEM_ICON);
			NULL_CHECK_VOID(pTexInfo);

			float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}
