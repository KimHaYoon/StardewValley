#include "stdafx.h"
#include "BackTerrain.h"
#include "ScrollMgr.h"

CBackTerrain::CBackTerrain()
{
}


CBackTerrain::~CBackTerrain()
{
	Release();
}

HRESULT CBackTerrain::Init()
{

	return S_OK;
}
HRESULT CBackTerrain::Init(const _tchar * pFilePath, OBJECT_ID eID)
{
	m_tInfo.vPos = { 400.f, 300.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	if (FAILED(LoadData(pFilePath)))
		return E_FAIL;
	m_fSpeed = 10.f;
	for (auto& iter : m_vecTile)
		wcscpy_s(iter->ObjKey, L"Fall");
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_1);
	return S_OK;
}
_int CBackTerrain::Update(const _float & fTimeDelta)
{
// 	if (CKeyMgr::GetInstance()->KeyPressing(KEY_LEFT))
// 	{
// 		CScrollMgr::SetScroll(D3DXVECTOR3{ 3 * m_fSpeed * -fTimeDelta, 0.f, 0.f });
// 		m_tInfo.vPos.x -= fTimeDelta;
// 	}
// 	if (CKeyMgr::GetInstance()->KeyPressing(KEY_RIGHT))
// 	{
// 		CScrollMgr::SetScroll(D3DXVECTOR3{ 3 * m_fSpeed * fTimeDelta, 0.f, 0.f });
// 		m_tInfo.vPos.x += fTimeDelta;
// 
// 	}
// 	if (CKeyMgr::GetInstance()->KeyPressing(KEY_UP))
// 	{
// 		CScrollMgr::SetScroll(D3DXVECTOR3{ 0.f,  -3 * m_fSpeed * fTimeDelta , 0.f });
// 		m_tInfo.vPos.y -= fTimeDelta;
// 	}
// 	if (CKeyMgr::GetInstance()->KeyPressing(KEY_DOWN))
// 	{
// 		CScrollMgr::SetScroll(D3DXVECTOR3{ 0.f,  3 * m_fSpeed * fTimeDelta , 0.f });
// 		m_tInfo.vPos.y += fTimeDelta;
// 	}


	return NO_ERROR;
}

void CBackTerrain::LateUpdate(const _float & fTimeDelta)
{
}

void CBackTerrain::Render()
{
	D3DXMATRIX matScale, matTrans;
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();
	int iCullX = (int)vScroll.x / TILECX;
	int iCullY = (int)vScroll.y / TILECY;

	int iCullEndX = iCullX + WINCX / TILECX + 1;
	int iCullEndY = iCullY + WINCY / TILECY + 1;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int iIndex = j + (TILEX * i);

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, m_tInfo.vSize.z);
			D3DXMatrixTranslation(
				&matTrans,
				m_vecTile[iIndex]->vPos.x - vScroll.x,
				m_vecTile[iIndex]->vPos.y - vScroll.y,
				0.f);

			m_tInfo.matWorld = matScale * matTrans;

			const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
				m_vecTile[iIndex]->ObjKey,
				m_vecTile[iIndex]->StateKey,
				m_vecTile[iIndex]->byDrawID);
			NULL_CHECK_VOID(pTexInfo);

			float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
			float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CBackTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}



HRESULT CBackTerrain::LoadData(const _tchar * pFilePath)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	HANDLE fFile = nullptr;
	fFile = CreateFile(pFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	DWORD dwByte = 0;
	TILE* pTile = nullptr;
	TILE t = {};

	while (true)
	{
		ReadFile(fFile, &t, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		pTile = new TILE(t);
		m_vecTile.push_back(pTile);
	}

	m_vecTile.shrink_to_fit();
	CloseHandle(fFile);

	return S_OK;
}
