// ImageView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ImageView.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "MyImage.h"
#include "Terrain.h"

// CImageView

IMPLEMENT_DYNCREATE(CImageView, CScrollView)

CImageView::CImageView()
{

}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CScrollView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CImageView 그리기입니다.

void CImageView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CScrollView::SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 4));

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));


	RECT rcMainFrm = {};
	pMainFrm->GetWindowRect(&rcMainFrm);
	SetRect(&rcMainFrm, 0, 0,
		rcMainFrm.right - rcMainFrm.left, rcMainFrm.bottom - rcMainFrm.top);

	RECT rcView = {};
	GetClientRect(&rcView);
	int iRowFrm = rcMainFrm.right - rcView.right;
	int iColFrm = rcMainFrm.bottom - rcView.bottom;

	pMainFrm->SetWindowPos(nullptr, 0, 0,
		WINCX + iRowFrm, WINCY + iColFrm, SWP_NOZORDER);


	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain;

		if (FAILED(m_pTerrain->Initialize(false)))
		{
			SafeDelete(m_pTerrain);
			AfxMessageBox(L"Terrain Object Create Failed!!");
			return;
		}

		m_pTerrain->SetViewWnd(pView);
	}


	for (size_t i = 0; i < m_pTerrain->GetTile().size(); ++i)
		m_MapPos.insert({i, m_pTerrain->GetTile()[i]->vPos});

}

void CImageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CMyImage* pImage = pView->m_pImage;

	CDevice::GetInstance()->Render_Begin();

	pImage->Render();
	if (nullptr != m_pTerrain)
		m_pTerrain->Render();

	CDevice::GetInstance()->Render_End(m_hWnd);
}

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif

void CImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);
	m_Point = point;

	Check = true;
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CImageView* pImageView = dynamic_cast<CImageView*>(pMainFrm->m_MainSplt.GetPane(0, 2));
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CTerrain* pTerrain = pImageView->m_pTerrain;


	CTerrain* pterrain = pView->m_pTerrain;
	CMyImage* pImage = pView->m_pImage;
	pTerrain->GetTile();


	_vec3 tempv = { (float)point.x, (float)point.y, 0.f };
	_vec3   vecResult = {};
	_float	least = 100;
	for (auto& iter : pTerrain->GetTile())
	{
		_vec3 v = iter->vPos - tempv;
		_float f = D3DXVec3Length(&v);

		if (f > least)
		{
			continue;
		}
		else
		{
			least = f;
			vecResult = iter->vPos;
		}
	}

	for (auto& iter : m_MapPos)
	{
		if (iter.second == vecResult)
		{
			iIdx = iter.first;
			break;
		}
	}

	if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(ObjKey, L"Spring");
		wcscpy_s(StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(ObjKey, L"Spring");
		wcscpy_s(StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(ObjKey, L"Spring");
		wcscpy_s(StateKey, L"Town_Tile");
	}

	else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(ObjKey, L"Summer");
		wcscpy_s(StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(ObjKey, L"Summer");
		wcscpy_s(StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(ObjKey, L"Summer");
		wcscpy_s(StateKey, L"Town_Tile");
	}

	else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(ObjKey, L"Fall");
		wcscpy_s(StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(ObjKey, L"Fall");
		wcscpy_s(StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(ObjKey, L"Fall");
		wcscpy_s(StateKey, L"Town_Tile");
	}

	else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(ObjKey, L"Winter");
		wcscpy_s(StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(ObjKey, L"Winter");
		wcscpy_s(StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(ObjKey, L"Winter");
		wcscpy_s(StateKey, L"Town_Tile");
	}


	else if (pImage->m_pStateKey == L"Path"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(ObjKey, L"Path");
		wcscpy_s(StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Path"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(ObjKey, L"Path");
		wcscpy_s(StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Path"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(ObjKey, L"Path");
		wcscpy_s(StateKey, L"Town_Tile");
	}
}
