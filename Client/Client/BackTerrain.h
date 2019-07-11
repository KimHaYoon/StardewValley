#pragma once
#include "Obj.h"
class CBackTerrain :
	public CObj
{
public:
	CBackTerrain();
	~CBackTerrain();
public:
	virtual HRESULT Init();
	virtual _int	Update(const _float& fTimeDelta);
	virtual void	LateUpdate(const _float& fTimeDelta);
	virtual void	Render();
	virtual void	Release();
public:
	virtual HRESULT	Init(const _tchar* pFilePath);
public:
	HRESULT LoadData(const _tchar* pFilePath);
private:
	_int			m_iIdx = 2100;
private:
	vector<TILE*>	m_vecTile;
	TILE*			m_pTile = nullptr;
public:
	vector<TILE*>&  GetTile() { return m_vecTile; }
};

