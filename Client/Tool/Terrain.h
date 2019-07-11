#pragma once

class CToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	void SetViewWnd(CToolView* pView) { m_pViewWnd = pView; }

public:
	HRESULT Initialize();
	HRESULT Initialize(bool b);
	void Update();
	void Render();
	void Render(bool b);
	void MiniRender(float fRatio);
	void Release();

public:
	void TileChange(const D3DXVECTOR3& vPos, _int dwDrawID, BYTE dwOption = 0);
	void TileChange(TCHAR* pObjState, TCHAR* pState, const D3DXVECTOR3& vPos, _int dwDrawID, BYTE dwOption = 0);
	void fAlphaCheck(const D3DXVECTOR3& vPos);
private:
	int GetTileIndex(const D3DXVECTOR3& vPos);
	bool IsPicking(const D3DXVECTOR3& vPos, int iIndex);
	void SetRatio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

public:
	TCHAR*			m_pObjKey = L"Fall";
	TCHAR*			m_pStateKey = L"Beach_Tile";
	_int			m_iIdx = 2100;
private:
	vector<TILE*>	m_vecTile;
	CToolView*		m_pViewWnd;
	TILE*			m_pTile = nullptr;
public:
	vector<TILE*>&  GetTile() { return m_vecTile;}
};

