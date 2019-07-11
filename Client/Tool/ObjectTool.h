#pragma once
#include "afxwin.h"


// CObjectTool 대화 상자입니다.

class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)

public:
	CObjectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList();
	CListBox m_ListBox;
	CButton m_Radio[5];
	afx_msg void OnBnClickedApply();
	map<CString, UNITIFNO>	m_mapchar;
	virtual BOOL OnInitDialog();
	_int m_iObjNum;
	UNITIFNO		m_tInfo;

	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedClear();
};
