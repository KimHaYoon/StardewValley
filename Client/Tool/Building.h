#pragma once
class CToolView;
class CBuilding
{
public:
	CBuilding();
	~CBuilding();
public:
	void SetViewWnd(CToolView* pView) { m_pViewWnd = pView; }
public:
	HRESULT Initialize();
	void	Update();
	void	Render();
	void	MiniRender(float fRatio);
	void	AlphaRender(POINT pt);
	void	Release();

public:
	_int&	GetMapNum() { return m_iMapNum; }
	void	SetMapNum(int iMapNum) { m_iMapNum = iMapNum; }
	void	SetRatio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

	_int			m_iMapNum = 0;
public:
	_int			m_iImageNum = 0;
	TCHAR*			m_pObjKey = L"";
	TCHAR*			m_pStateKey = L"";
	bool			m_bCheck = false;
	bool			m_bLastest = false;
	
public:
	CToolView*		m_pViewWnd;
	UNITIFNO		m_tUintInfo;
};

