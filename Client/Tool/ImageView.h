#pragma once



// CImageView 뷰입니다.
class CTerrain;
class CImageView : public CScrollView
{
	DECLARE_DYNCREATE(CImageView)

protected:
	CImageView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


