#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CButton m_Radio[5];
	afx_msg void OnLbnSelchangeList();
	CListBox m_ListBox;
	afx_msg void OnBnClickedApply();

	virtual BOOL OnInitDialog();
	map<CString, CString>	m_mapchar;
};
