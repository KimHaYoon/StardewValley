// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm::OnBnClickedImageViewTool)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm::OnBnClickedTileTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnBnClickedObjTool)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyForm::OnBnClickedPathFinder)
	ON_BN_CLICKED(IDC_BUTTON14, &CMyForm::OnBnClickedNPCTool)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.



void CMyForm::OnBnClickedImageViewTool()
{
	if (m_ImageViewTool.GetSafeHwnd() == nullptr)
	{
		m_ImageViewTool.Create(IDD_IMAGEVIEW);
	}
	m_ImageViewTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedTileTool()
{
	if (m_TileTool.GetSafeHwnd() == nullptr)
	{
		m_TileTool.Create(IDD_TILETOOL);
	}
	m_TileTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedObjTool()
{
	if (m_ObjTool.GetSafeHwnd() == nullptr)
	{
		m_ObjTool.Create(IDD_OBJECTTOOL);
	}
	m_ObjTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedPathFinder()
{
	if (m_PathFinder.GetSafeHwnd() == nullptr)
	{
		m_PathFinder.Create(IDD_PATHFINDER);
	}
	m_PathFinder.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedNPCTool()
{
	if (m_NPCTool.GetSafeHwnd() == nullptr)
	{
		m_NPCTool.Create(IDD_NPCTOOL);
	}
	m_NPCTool.ShowWindow(SW_SHOW);
}

