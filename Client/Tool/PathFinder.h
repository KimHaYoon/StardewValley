#pragma once
#include "afxwin.h"


// CPathFinder 대화 상자입니다.

class CPathFinder : public CDialog
{
	DECLARE_DYNAMIC(CPathFinder)

public:
	CPathFinder(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPathFinder();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHFINDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	virtual BOOL OnInitDialog();
	afx_msg void OnDropFiles(HDROP hDropInfo);
public:
	void SetHorizontalScroll();
public:
	list<IMGPATHINFO*> m_ImgInfoLst;
};
