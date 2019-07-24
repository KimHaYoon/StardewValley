
// ToolView.h : CToolView 클래스의 인터페이스
//

#pragma once
class CMyMap;
class CTerrain;
class CMyImage;
class CBuilding;
class CToolDoc;
class CToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:
	CTerrain*	m_pTerrain=nullptr;
	CMyMap*		m_pMap=nullptr;
	CMyImage*	m_pImage = nullptr;
	CBuilding*	m_pBuilding = nullptr;
public:
	vector<CBuilding*>								m_vecBuilding[LAYER_ID_END];
	vector<NPCInfo*>								m_vecNPCInfo;


	CString											NPCName=L"";
	_int											m_iNPCNum = 0;
	_int											m_iIdx = 0;


	vector<_vec3>									m_vecNPCOnlyPath;



	vector<TILE*>									m_vecTempTile;
	TCHAR											m_szTemp[128];
	map<_vec3, TCHAR*>								m_mapCHAR;
public:
	bool			m_bCheck = false;
	bool			m_bMouseLButtonClick = true;
	POINT			m_pt;
public:
	_bool			m_bReactionCheck = false;


public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

