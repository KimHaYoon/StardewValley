#include "stdafx.h"
#include "ReactionTerrain.h"
#include "ScrollMgr.h"

CReactionTerrain::CReactionTerrain()
{
}


CReactionTerrain::~CReactionTerrain()
{
	Release();
}

HRESULT CReactionTerrain::Init()
{
	return S_OK;
}

_int CReactionTerrain::Update(const _float & fTimeDelta)
{
	return NO_EVENT;
}

void CReactionTerrain::LateUpdate(const _float & fTimeDelta)
{
	TileCollision();
}

void CReactionTerrain::Render()
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

void CReactionTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_DESC*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

HRESULT CReactionTerrain::Init(const _tchar * pFilePath, OBJECT_ID eID)
{
	m_tInfo.vPos = { 400.f, 300.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	if (FAILED(LoadData(pFilePath)))
		return E_FAIL;
	m_fSpeed = 10.f;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_1);
	return S_OK;
}

HRESULT CReactionTerrain::LoadData(const _tchar * pFilePath)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_DESC*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	HANDLE fFile = nullptr;
	fFile = CreateFile(pFilePath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	DWORD dwByte = 0;
	TILE_DESC* pTile = nullptr;
	TILE t = {};
	
	_int	iTempFront = 0;
	_int	iTempBack = 0;
	while (true)
	{
		_int	iFrontTileCnt = 0;
		_int	iBackTileCnt = 0;
		ReadFile(fFile, &t, sizeof(TILE), &dwByte, nullptr);

		if (t.byDrawID == 2103)
		{
			iFrontTileCnt = iTempFront;
			iFrontTileCnt++;	
			iTempFront = iFrontTileCnt;
		}
		else if (t.byDrawID == 2102)
		{
			iBackTileCnt = iTempBack;
			iBackTileCnt++;
			iTempBack = iBackTileCnt;
		}
		if (0 == dwByte)
			break;

		pTile = new TILE_DESC(t);
		pTile->iFrontTileNum = iFrontTileCnt;
		pTile->iBackTileNum = iBackTileCnt;
		m_vecTile.push_back(pTile);
	}

	m_vecTile.shrink_to_fit();
	CloseHandle(fFile);

	return S_OK;
}

void CReactionTerrain::TileCollision()
{
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();
	m_pTarget = CObjectMgr::GetInstance()->GetPlayer();
	int iCullX = (int)vScroll.x / TILECX;
	int iCullY = (int)vScroll.y / TILECY;

	int iCullEndX = iCullX + WINCX / TILECX;
	int iCullEndY = iCullY + WINCY / TILECY;
	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int iIndex = j + (TILEX * i);

			if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
				continue;

			// Player
			float fMoveX = 0.f, fMoveY = 0.f;
			if (CheckRect_Player(m_vecTile[iIndex], m_pTarget, &fMoveX, &fMoveY))
			{
				if (m_vecTile[iIndex]->byDrawID== 2101)
				{
					if (fMoveX > fMoveY)
					{
						if (m_vecTile[iIndex]->vPos.y - vScroll.y >= m_pTarget->GetInfo().vPos.y)
							fMoveY *= -1.f;

						CScrollMgr::SetScroll(D3DXVECTOR3{ 0.f, fMoveY, 0.f });
					}
					else
					{
						if (m_vecTile[iIndex]->vPos.x - vScroll.x >= m_pTarget->GetInfo().vPos.x)
							fMoveX *= -1.f;

						CScrollMgr::SetScroll(D3DXVECTOR3{ fMoveX, 0.f, 0.f });
					}
				}
				if (m_vecTile[iIndex]->byDrawID == 2102)
				{

				}
				if (m_vecTile[iIndex]->byDrawID == 2103)
				{
					CSceneMgr::GetInstance()->SetPass_ID(PASS_ID_FRONT);
				}
			}

			// NPC
			fMoveX = 0.f, fMoveY = 0.f;
			auto& iter = CObjectMgr::GetInstance()->GetNPCList().begin();
			for (; iter != CObjectMgr::GetInstance()->GetNPCList().end(); iter++)
			{
				if (CheckRect_NonePlayer(m_vecTile[iIndex], (*iter), &fMoveX, &fMoveY))
				{
					if (m_vecTile[iIndex]->byDrawID == 2101)
					{
						if (fMoveX > fMoveY)
						{
							if ((*iter)->GetInfo().vPos.y <= m_vecTile[iIndex]->vPos.y)
								fMoveY *= -1.f;

							(*iter)->SetPos((*iter)->GetInfo().vPos.x, (*iter)->GetInfo().vPos.y + fMoveY);
						}
						else
						{
							if ((*iter)->GetInfo().vPos.x <= m_vecTile[iIndex]->vPos.x)
								fMoveX *= -1.f;
							(*iter)->SetPos((*iter)->GetInfo().vPos.x + fMoveX, (*iter)->GetInfo().vPos.y);
						}
					}
				}
			}

			// Monster
			fMoveX = 0.f, fMoveY = 0.f;
			iter = CObjectMgr::GetInstance()->GetMonsterList().begin();
			for (; iter != CObjectMgr::GetInstance()->GetMonsterList().end(); iter++)
			{
				if (CheckRect_NonePlayer(m_vecTile[iIndex], (*iter), &fMoveX, &fMoveY))
				{
					if (m_vecTile[iIndex]->byDrawID == 2101)
					{
						if (fMoveX > fMoveY)
						{
							if ((*iter)->GetInfo().vPos.y <= m_vecTile[iIndex]->vPos.y)
								fMoveY *= -1.f;

							(*iter)->SetPos((*iter)->GetInfo().vPos.x, (*iter)->GetInfo().vPos.y + fMoveY);
						}
						else
						{
							if ((*iter)->GetInfo().vPos.x <= m_vecTile[iIndex]->vPos.x)
								fMoveX *= -1.f;
							(*iter)->SetPos((*iter)->GetInfo().vPos.x + fMoveX, (*iter)->GetInfo().vPos.y);
						}
					}
				}
			}
		}
	}
}

bool CReactionTerrain::CheckRect_NonePlayer(TILE * pDst, CObj *& pSrc, float * pMoveX, float * pMoveY)
{
	float fSumRadX = (pDst->vSize.x + pSrc->GetCollSize().x)*0.5f;	//pSrc.x=30, y=40
	float fSumRadY = (pDst->vSize.y + pSrc->GetCollSize().y)* 0.5f;


	float fDistX = fabs(pDst->vPos.x - pSrc->GetInfo().vPos.x);
	float fDistY = fabs(pDst->vPos.y - pSrc->GetInfo().vPos.y);


	if (fSumRadX >= fDistX && fSumRadY >= fDistY)
	{
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}
bool CReactionTerrain::CheckRect_Player(TILE * pDst, CObj *& pSrc, float * pMoveX, float * pMoveY)
{
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();

	float fSumRadX = (pDst->vSize.x + pSrc->GetCollSize().x)*0.5f;
	float fSumRadY = (pDst->vSize.y + pSrc->GetCollSize().y)* 0.5f;


	float fDistX = fabs(pDst->vPos.x - pSrc->GetInfo().vPos.x - vScroll.x);
	float fDistY = fabs(pDst->vPos.y - pSrc->GetInfo().vPos.y - vScroll.y);


	if (fSumRadX >= fDistX && fSumRadY >= fDistY)
	{
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}
	return false;
}
