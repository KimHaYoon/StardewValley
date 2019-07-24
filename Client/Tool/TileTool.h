#pragma once
#include "afxwin.h"


// CTileTool 대화 상자입니다.
#include "Terrain.h"
class CTileTool : public CDialog
{
	DECLARE_DYNAMIC(CTileTool)

public:
	CTileTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTileTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedTileSave();
	afx_msg void OnBnClickedTileLoad();
	afx_msg void OnBnClickedApply();

public:
	CButton m_RadioMap[10];
public:
	CTerrain*			  m_pTile;
	CButton m_RadioSeason[4];
	afx_msg void OnBnClickedClear();
	CButton m_RadioReaction[2];
public:
	_bool		m_bReactionCheck = false;
};
