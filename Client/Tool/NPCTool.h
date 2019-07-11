#pragma once
#include "afxwin.h"


// CNPCTool ��ȭ �����Դϴ�.

class CNPCTool : public CDialog
{
	DECLARE_DYNAMIC(CNPCTool)

public:
	CNPCTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNPCTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NPCTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnBnClickedPathSave();
	afx_msg void OnBnClickedPathLoad();
	CListBox m_ListBox;
	CButton m_Radio[6];
public:
	virtual BOOL OnInitDialog();
public:
	map<CString, _int>	m_mapchar;
	CString m_strTmp = L"";
	_int	m_iIdx = 0;
	vector<TILE*>									m_vecTempTile;
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedClose();
};


