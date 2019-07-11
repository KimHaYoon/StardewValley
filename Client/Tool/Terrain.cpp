#include "stdafx.h"
#include "Terrain.h"
#include "ToolView.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Initialize()
{
	m_vecTile.reserve(TILEX*TILEY);
	float fX = 0.f, fY = 0.f;
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			m_pTile = new TILE;
			 
			fX = ((_float)TILECX * j);
			fY = ((_float)TILECY * i);

			m_pTile->vPos = { fX+(float)TILECX * 0.5f,  fY+(float)TILECY * 0.5f, 0.f };
			m_pTile->vSize = { (float)TILECX, (float)TILECY, 0.f };
			wcscpy_s(m_pTile->ObjKey, L"Spring");
			wcscpy_s(m_pTile->StateKey, L"Beach_Tile");
			m_pTile->byDrawID = 2100;
			m_pTile->byOption = 0;

			m_vecTile.push_back(m_pTile);
		}

	}
	return S_OK;
}

HRESULT CTerrain::Initialize(bool b)
{
	m_vecTile.reserve(30*TILEY);
	float fX = 0.f, fY = 0.f;
	for (int i = 0; i < 70; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			m_pTile = new TILE;

			fX = ((_float)TILECX * j);
			fY = ((_float)TILECY * i);

			m_pTile->vPos = { fX + (float)TILECX * 0.5f,  fY + (float)TILECY * 0.5f, 0.f };
			m_pTile->vSize = { (float)TILECX, (float)TILECY, 0.f };
			wcscpy_s(m_pTile->ObjKey, L"Spring");
			wcscpy_s(m_pTile->StateKey, L"Beach_Tile");
			m_pTile->byDrawID = 2100;
			m_pTile->byOption = 0;

			m_vecTile.push_back(m_pTile);
		}

	}
	return S_OK;
}

void CTerrain::Update()
{
}

void CTerrain::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;

	RECT rc = {};
	m_pViewWnd->GetClientRect(&rc);

	float fCurWinCX = float(rc.right - rc.left);
	float fCurWinCY = float(rc.bottom - rc.top);

	float fRatioX = WINCX / fCurWinCX;
	float fRatioY = WINCY / fCurWinCY;
	TCHAR szBuf[MIN_STR] = L"";

	for (size_t iIndex = 0; iIndex < m_vecTile.size(); ++iIndex)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[iIndex]->vPos.x ,
			m_vecTile[iIndex]->vPos.y ,
			0.f);

		matWorld = matScale * matTrans;

		SetRatio(&matWorld, fRatioX, fRatioY);
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo
		(
			m_vecTile[iIndex]->ObjKey, 
			m_vecTile[iIndex]->StateKey, 
			m_vecTile[iIndex]->byDrawID
		);
		NULL_CHECK_VOID(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		if (m_vecTile[iIndex]->AlphaCheck)
		{
			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
				nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
				nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(150, 255, 255, 255));
		}
		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
			szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTerrain::Render(bool b)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	RECT rc = {};
	m_pViewWnd->GetClientRect(&rc);

	float fCurWinCX = float(rc.right - rc.left);
	float fCurWinCY = float(rc.bottom - rc.top);

	float fRatioX = WINCX / fCurWinCX;
	float fRatioY = WINCY / fCurWinCY;
	TCHAR szBuf[MIN_STR] = L"";

	for (size_t iIndex = 0; iIndex < m_vecTile.size(); ++iIndex)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[iIndex]->vPos.x - m_pViewWnd->GetScrollPos(0),
			m_vecTile[iIndex]->vPos.y - m_pViewWnd->GetScrollPos(1),
			0.f);

		matWorld = matScale * matTrans;

		SetRatio(&matWorld, fRatioX, fRatioY);
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo
		(
			m_vecTile[iIndex]->ObjKey, 
			m_vecTile[iIndex]->StateKey, 
			m_vecTile[iIndex]->byDrawID
		);
		NULL_CHECK_VOID(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
		if (m_vecTile[iIndex]->AlphaCheck)
		{

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
				nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
				nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(150, 255, 255, 255));
		}


		CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
			szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTerrain::MiniRender(float fRatio)
{
	D3DXMATRIX matScale, matTrans, matWorld;

	RECT rc = {};
	m_pViewWnd->GetClientRect(&rc);

	float fCurWinCX = float(rc.right - rc.left);
	float fCurWinCY = float(rc.bottom - rc.top);

	float fRatioX = WINCX / fCurWinCX;
	float fRatioY = WINCY / fCurWinCY;
	TCHAR szBuf[MIN_STR] = L"";

	for (size_t iIndex = 0; iIndex < m_vecTile.size(); ++iIndex)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[iIndex]->vPos.x - m_pViewWnd->GetScrollPos(0),
			m_vecTile[iIndex]->vPos.y - m_pViewWnd->GetScrollPos(1),
			0.f);

		matWorld = matScale * matTrans;

		SetRatio(&matWorld, fRatio, fRatio);
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
			L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);
		NULL_CHECK_VOID(pTexInfo);

		float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
			nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::TileChange(const D3DXVECTOR3& vPos, _int dwDrawID, BYTE dwOption)
{
	int iIndex = GetTileIndex(vPos);

	if (0 > iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = dwDrawID;
	m_vecTile[iIndex]->byOption = dwOption;
}

void CTerrain::TileChange(TCHAR * pObjState, TCHAR * pState, const D3DXVECTOR3 & vPos, _int dwDrawID, BYTE dwOption)
{
	int iIndex = GetTileIndex(vPos);

	if (0 > iIndex)
		return;

	wcscpy_s(m_vecTile[iIndex]->ObjKey, pObjState);
	wcscpy_s(m_vecTile[iIndex]->StateKey, pState);
	m_vecTile[iIndex]->byDrawID = dwDrawID;
	m_vecTile[iIndex]->byOption = dwOption;
}

int CTerrain::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	for (size_t iIndex = 0; iIndex < m_vecTile.size(); ++iIndex)
	{
		if (IsPicking(vPos, iIndex))
			return iIndex;
	}
	return -1;
}

bool CTerrain::IsPicking(const D3DXVECTOR3& vPos, int iIndex)
{
	D3DXVECTOR3 vPoint[4] =
	{
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY / 2, 0.f },
		{ m_vecTile[iIndex]->vPos.x + TILECX / 2, m_vecTile[iIndex]->vPos.y, 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY / 2, 0.f },
		{ m_vecTile[iIndex]->vPos.x - TILECX / 2, m_vecTile[iIndex]->vPos.y, 0.f },
	};
	D3DXVECTOR3 vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};
	D3DXVECTOR3 vNormal[4] =
	{
		{ -vDir[0].y, vDir[0].x, 0.f },
		{ -vDir[1].y, vDir[1].x, 0.f },
		{ -vDir[2].y, vDir[2].x, 0.f },
		{ -vDir[3].y, vDir[3].x, 0.f }
	};
	D3DXVECTOR3 vMouseDir[4] = 
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};
	for (int i = 0; i < 4; ++i)
	{
		if (0.f <= D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}

	return true;
}

void CTerrain::SetRatio(D3DXMATRIX* pOut, float fRatioX, float fRatioY)
{
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;
}

void CTerrain::fAlphaCheck(const D3DXVECTOR3 & vPos)
{
	int iIndex = GetTileIndex(vPos);

	if (0 > iIndex)
		return;
	m_vecTile[iIndex]->AlphaCheck = false;
}
