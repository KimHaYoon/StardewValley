#pragma once
#include "afxwin.h"


// CImageViewTool ��ȭ �����Դϴ�.

class CImageViewTool : public CDialog
{
	DECLARE_DYNAMIC(CImageViewTool)

public:
	CImageViewTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageViewTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLbnSelchangeList();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_Radio[5];
	CListBox m_ListBox;

public:					// User
	CString				m_strMapName = L"";
	map<CString, CString>	m_mapchar;

	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedCapture();
public:
	void DrawClip(HDC hDC, CImage* pImage, POINT Start, POINT End, int pos1=1, int pos2=0, int pos3=0);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
