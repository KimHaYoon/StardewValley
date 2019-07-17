#pragma once



// CMyForm �� ���Դϴ�.

#include "ImageViewTool.h"
#include "TileTool.h"
#include "ObjectTool.h"
#include "PathFinder.h"
#include "NPCTool.h"

#include "afxwin.h"
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImageViewTool();
public:

	CImageViewTool	m_ImageViewTool;
	CTileTool		m_TileTool;
	CObjectTool		m_ObjTool;
	CPathFinder		m_PathFinder;
	CNPCTool		m_NPCTool;

	afx_msg void OnBnClickedTileTool();
	afx_msg void OnBnClickedObjTool();
	afx_msg void OnBnClickedPathFinder();
	CButton m_Radio[2];
	afx_msg void OnBnClickedNPCTool();

};


