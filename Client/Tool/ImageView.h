#pragma once



// CImageView ���Դϴ�.
class CTerrain;
class CImageView : public CScrollView
{
	DECLARE_DYNCREATE(CImageView)

protected:
	CImageView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CImageView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	CTerrain*	m_pTerrain = nullptr;
	POINT		m_Point;
	int			m_iNumTileMapNum = 0;
	map<_int, _vec3>	m_MapPos;
	TCHAR		ObjKey[128] = L"";
	TCHAR		StateKey[128] = L"";
	int			iIdx = 0;
	bool		Check = false;
protected:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual void OnInitialUpdate();     // ������ �� ó���Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


