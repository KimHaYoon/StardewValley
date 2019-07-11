
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "ImageView.h"
#include "Terrain.h"
#include "MyMap.h"
#include "MyImage.h"
#include "Building.h"
#include "MyForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()

// 전역변수
HWND g_hWnd;

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
	SafeDelete(m_pTerrain);
	SafeDelete(m_pMap);
	SafeDelete(m_pImage);
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{


	return CScrollView::PreCreateWindow(cs);
}

void CToolView::OnDraw(CDC* pDC)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::GetInstance()->Render_Begin();

	if (nullptr != m_pMap)
		m_pMap->Render();
	if (nullptr != m_pTerrain)
		m_pTerrain->Render(false);

	for (int i = 0; i < LAYER_ID_END; ++i)
	{
		for (auto& iter : m_vecBuilding[i])
		{
			if (iter->m_tUintInfo.Check)
				iter->AlphaRender(m_pt);
			else
			{

				iter->Render();
			}
		}
	}


	CDevice::GetInstance()->Render_End();
}
BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}


#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWnd = m_hWnd;
	CScrollView::SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

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

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"InitDevice Failed");
		return;
	}


	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
		L"../Texture/Stage/TERRAIN/tile/tile%d.png", L"Terrain", L"Tile", 9)))
	{
		AfxMessageBox(L"TERRAIN Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
		L"../Texture/MapImage/Map/Map%d.png", L"Map", L"Map", 9)))
	{
		AfxMessageBox(L"Map Image Insert Failed");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
		L"../Texture/Season/Fall/Fall%d.png", L"Season", L"Fall", 3)))
	{
		AfxMessageBox(L"Fall Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
		L"../Texture/Season/Summer/Summer%d.png", L"Season", L"Summer", 3)))
	{
		AfxMessageBox(L"Summer Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
		L"../Texture/Season/Spring/Spring%d.png", L"Season", L"Spring", 3)))
	{
		AfxMessageBox(L"Spring Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
		L"../Texture/Season/Winter/Winter%d.png", L"Season", L"Winter", 3)))
	{
		AfxMessageBox(L"Winter Image Insert Failed");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
		L"../Texture/Season/Path/Path%d.png", L"Season", L"Path", 3)))
	{
		AfxMessageBox(L"Winter Image Insert Failed");
		return;
	}


	{
		//Spring_Tile
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Spring/Beach_Tile/Beach_Tile%d.png", L"Spring", L"Beach_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Spring/OutDoor_Tile/OutDoor_Tile%d.png", L"Spring", L"OutDoor_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Spring/Town_Tile/Town_Tile%d.png", L"Spring", L"Town_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}


		//Summer_TIle
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Summer/Beach_Tile/Beach_Tile%d.png", L"Summer", L"Beach_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Summer/OutDoor_Tile/OutDoor_Tile%d.png", L"Summer", L"OutDoor_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Summer/Town_Tile/Town_Tile%d.png", L"Summer", L"Town_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}


		//Fall_Tile
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Fall/Beach_Tile/Beach_Tile%d.png", L"Fall", L"Beach_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Fall/OutDoor_Tile/OutDoor_Tile%d.png", L"Fall", L"OutDoor_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Fall/Town_Tile/Town_Tile%d.png", L"Fall", L"Town_Tile", 2101)))
		{
			AfxMessageBox(L"Spring Beach_Tile Image Insert Failed");
			return;
		}

		//Winter_Tile
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Winter/Beach_Tile/Beach_Tile%d.png", L"Winter", L"Beach_Tile", 2101)))
		{
			AfxMessageBox(L"Winter Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Winter/OutDoor_Tile/OutDoor_Tile%d.png", L"Winter", L"OutDoor_Tile", 2101)))
		{
			AfxMessageBox(L"Winter Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Winter/Town_Tile/Town_Tile%d.png", L"Winter", L"Town_Tile", 2101)))
		{
			AfxMessageBox(L"Winter Beach_Tile Image Insert Failed");
			return;
		}

		// Path_Tile
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Path/Beach_Tile/Beach_Tile%d.png", L"Path", L"Beach_Tile", 2101)))
		{
			AfxMessageBox(L"Path Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Path/OutDoor_Tile/OutDoor_Tile%d.png", L"Path", L"OutDoor_Tile", 2101)))
		{
			AfxMessageBox(L"Path Beach_Tile Image Insert Failed");
			return;
		}
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Path/Town_Tile/Town_Tile%d.png", L"Path", L"Town_Tile", 2101)))
		{
			AfxMessageBox(L"Path Beach_Tile Image Insert Failed");
			return;
		}
	}

	{
		//Spring Building
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Spring/Building/Building%d.png", L"Spring", L"Building", 26)))
		{
			AfxMessageBox(L"Spring Building Image Insert Failed");
			return;
		}


		//Summer Building

		//Fall Building
		if (FAILED(CTextureMgr::GetInstance()->InsertTexture(CTextureMgr::TEX_MULTI,
			L"../Texture/Season/Fall/Building/Building%d.png", L"Fall", L"Building", 26)))
		{
			AfxMessageBox(L"Fall Building Image Insert Failed");
			return;
		}

		//Winter Building

	}

	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain;

		if (FAILED(m_pTerrain->Initialize()))
		{
			SafeDelete(m_pTerrain);
			AfxMessageBox(L"Terrain Object Create Failed!!");
			return;
		}

		m_pTerrain->SetViewWnd(this);
	}
	if (nullptr == m_pMap)
	{
		m_pMap = new CMyMap;
		if (FAILED(m_pMap->Initialize()))
		{
			SafeDelete(m_pMap);
			return;
		}
		m_pMap->SetViewWnd(this);
	}
	if (nullptr == m_pImage)
	{
		m_pImage = new CMyImage;
		if (FAILED(m_pImage->Initialize()))
		{
			SafeDelete(m_pImage);
			return;
		}
		m_pImage->SetViewWnd(this);
	}

}
void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);



	point.x += CScrollView::GetScrollPos(0);
	point.y += CScrollView::GetScrollPos(1);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CImageView* pView = dynamic_cast<CImageView*>(pMainFrm->m_MainSplt.GetPane(0, 2));
	CTerrain* pTerrain = pView->m_pTerrain;

	if (m_bMouseLButtonClick)
	{
		if (!pView->Check)
		{
			return;
		}
		m_pTerrain->TileChange(pView->ObjKey, pView->StateKey, D3DXVECTOR3(float(point.x), float(point.y), 0.f), pView->iIdx);
	}
	else
	{
		_vec3	tempv = { (float)point.x, (float)point.y, 0.f };
		_vec3   vecResult = {};
		_int	least = 100;
		for (auto& iter : pTerrain->GetTile())
		{
			_vec3 v = iter->vPos - tempv;
			float f = D3DXVec3Length(&v);

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
		m_vecNPCOnlyPath.push_back(vecResult);	

		_vec3 vt = _vec3(float(point.x), float(point.y), 0.f);

		m_pTerrain->fAlphaCheck(vt);
	}
	Invalidate(FALSE);

}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);
	m_pt = point;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		point.x += CScrollView::GetScrollPos(0);
		point.y += CScrollView::GetScrollPos(1);


		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CImageView* pView = dynamic_cast<CImageView*>(pMainFrm->m_MainSplt.GetPane(0, 2));

		CTerrain* pTerrain = pView->m_pTerrain;

		if (!pView->Check)
		{
			return;
		}
		m_pTerrain->TileChange(pView->ObjKey, pView->StateKey, D3DXVECTOR3(float(point.x), float(point.y), 0.f), pView->iIdx);

	}

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CImageView* pImageView = dynamic_cast<CImageView*>(pMainFrm->m_MainSplt.GetPane(0, 2));
	pImageView->Invalidate(FALSE);

	CMyForm*	pFormView = dynamic_cast<CMyForm*>(pMainFrm->m_MainSplt.GetPane(0, 0));



	if (m_bCheck)
	{
		m_pBuilding = new CBuilding;

		if (FAILED(m_pBuilding->Initialize()))
		{
			SafeDelete(m_pImage);
			return;
		}
		m_pBuilding->m_tUintInfo = pFormView->m_ObjTool.m_tInfo;;
		m_pBuilding->SetViewWnd(this);
		if (m_pBuilding->m_tUintInfo.eID == LAYER_ID_1)
			m_vecBuilding[LAYER_ID_1].push_back(m_pBuilding);
		else if (m_pBuilding->m_tUintInfo.eID == LAYER_ID_2)
			m_vecBuilding[LAYER_ID_2].push_back(m_pBuilding);
		else if (m_pBuilding->m_tUintInfo.eID == LAYER_ID_3)
			m_vecBuilding[LAYER_ID_3].push_back(m_pBuilding);
		else if (m_pBuilding->m_tUintInfo.eID == LAYER_ID_4)
			m_vecBuilding[LAYER_ID_4].push_back(m_pBuilding);
		else if (m_pBuilding->m_tUintInfo.eID == LAYER_ID_5)
			m_vecBuilding[LAYER_ID_5].push_back(m_pBuilding);

		m_bCheck = false;
	}

	Invalidate(FALSE);
}


void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	for (int i = 0; i < LAYER_ID_END; ++i)
	{
		for (auto& iter : m_vecBuilding[i])
		{
			iter->m_bLastest = false;
		}
	}
	for (int i = 0; i < LAYER_ID_END; ++i)
	{
		for (auto& iter : m_vecBuilding[i])
		{
			
			if (iter->m_tUintInfo.Check)
			{
				iter->m_tUintInfo.vPos = _vec3((float)point.x, (float)point.y, 0.f);
				iter->m_bLastest = true;
			}
			iter->m_tUintInfo.Check = false;
		}
	}

	CScrollView::OnRButtonDown(nFlags, point);
}


BOOL CToolView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


void CToolView::OnMButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMyForm* pView = dynamic_cast<CMyForm*>(pMainFrm->m_MainSplt.GetPane(0, 0));
	
	if (pView->m_Radio[0].GetCheck() == TRUE)
	{
		_vec3 tempv = { (float)point.x, (float)point.y, 0.f };
		_vec3   vecResult = {};
		_int	least = 100;



		for (auto& iter : m_pTerrain->GetTile())
		{
			_vec3 v = iter->vPos - tempv;
			float f = D3DXVec3Length(&v);

			for (auto& iter : m_pTerrain->GetTile())
			{
				_vec3 v = iter->vPos - tempv;
				float f = D3DXVec3Length(&v);

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


			for (auto& iter : m_pTerrain->GetTile())
			{
				if (iter->vPos == vecResult)
				{
					iter->byDrawID = 2100;
				}
			}

		}

	}
	else if (pView->m_Radio[1].GetCheck() == TRUE)
	{

		_vec3 tempv = { (float)point.x, (float)point.y, 0.f };
		_vec3   vecResult = {};
		_int	least = 100;

		for (int i = 0; i < LAYER_ID_END; ++i)
		{
			for (auto& iter : m_vecBuilding[i])
			{
				_vec3 v = iter->m_tUintInfo.vPos - tempv;
				float f = D3DXVec3Length(&v);

				if (f > least)
				{
					continue;
				}
				else
				{
					least = f;
					vecResult = iter->m_tUintInfo.vPos;
				}
			}

		}
		for (int i = 0; i < LAYER_ID_END; ++i)
		{
			auto& iter = m_vecBuilding[i].begin();
			for (; iter != m_vecBuilding[i].end();)
			{
				if (iter[0]->m_tUintInfo.vPos == vecResult)
				{
					iter = m_vecBuilding[i].erase(iter);
				}
				else
					++iter;
			}

		}
	}
		CScrollView::OnMButtonDown(nFlags, point);
}