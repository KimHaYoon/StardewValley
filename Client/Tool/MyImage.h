#pragma once
class CToolView;
class CMyImage
{
public:
	CMyImage();
	~CMyImage();
public:
	void SetViewWnd(CToolView* pView) { m_pViewWnd = pView; }
public:
	HRESULT Initialize();
	void	Update();
	void	Render();
	void	MiniRender(float fRatio);
	void	Release();

public:
	void	SetRatio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

private:
	CToolView*		m_pViewWnd;
public:
	_int			m_iImageNum = 0;
	TCHAR*			m_pObjKey=L"";
	TCHAR*			m_pStateKey=L"";
};

