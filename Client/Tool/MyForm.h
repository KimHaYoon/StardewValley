#pragma once



// CMyForm 폼 뷰입니다.

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
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


