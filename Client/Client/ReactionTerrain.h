#pragma once
#include "Obj.h"
class CReactionTerrain :
	public CObj
{
public:
	CReactionTerrain();
	virtual ~CReactionTerrain();
public:
	virtual HRESULT Init();
	virtual _int	Update(const _float& fTimeDelta);
	virtual void	LateUpdate(const _float& fTimeDelta);
	virtual void	Render();
	virtual void	Release();
public:
	virtual HRESULT	Init(const _tchar* pFilePath, OBJECT_ID eID = OBJECT_ID_TERRAIN);
public:
	HRESULT LoadData(const _tchar* pFilePath);
	void	TileCollision();
	bool	CheckRect_NonePlayer(TILE* pDst, CObj*& pSrc, float* pMoveX, float* pMoveY);
	bool	CheckRect_Player(TILE* pDst, CObj*& pSrc, float* pMoveX, float* pMoveY);
private:
	_int			m_iIdx = 2100;
private:
	vector<TILE_DESC*>	m_vecTile;
	TILE*			m_pTile = nullptr;
	CObj*			m_pTarget;
public:
	vector<TILE_DESC*>&  GetTile() { return m_vecTile; }
};

