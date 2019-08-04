#pragma once
class CToolView;
class CMyMap
{
public:
	CMyMap();
	~CMyMap();
public:
	void SetViewWnd(CToolView* pView) { m_pViewWnd = pView; }
public:
	HRESULT Initialize();
	void	Update();
	void	Render();
	void	MiniRender(float fRatio);
	void	Release();

public:
	_int&	GetMapNum() { return m_iMapNum; }
	void	SetMapNum(int iMapNum) { m_iMapNum = iMapNum; }
	void	SetRatio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

	_int			m_iMapNum = 0;
public:
	_float			m_fX = 0.f;
	_float			m_fY = 0.f;
private:
	CToolView*		m_pViewWnd;

};

