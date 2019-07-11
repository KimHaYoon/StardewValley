#pragma once
#include "afxwin.h"


// CPathFinder ��ȭ �����Դϴ�.

class CPathFinder : public CDialog
{
	DECLARE_DYNAMIC(CPathFinder)

public:
	CPathFinder(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPathFinder();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHFINDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
