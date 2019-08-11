#pragma once
#include "Obj.h"
class CTerrain : public CObj
{
public:
	CTerrain();
	~CTerrain();
public:
	virtual HRESULT Init();
	virtual _int	Update(const _float& fTimeDelta);
	virtual void	LateUpdate(const _float& fTimeDelta);
	virtual void	Render();
	virtual void	Release();
public:
	virtual HRESULT	Init(const _tchar* pFilePath, OBJECT_ID eID = OBJECT_ID_TERRAIN);
	HRESULT LoadData(const _tchar* pFilePath);
public:
	_int			GetFront() { return m_iCheckFront; }
private:
	_int			m_iIdx = 2100;
	vector<TILE*>	m_vecTile;
	TILE*			m_pTile = nullptr;
	_int			m_iCheckFront = 100;
public:
	vector<TILE*>&  GetTile() { return m_vecTile; }
};