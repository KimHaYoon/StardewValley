// ImageDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ImageDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "MyImage.h"
#include "Terrain.h"
#include "ImageView.h"


// CImageDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageDialog, CDialog)

CImageDialog::CImageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_IMAGEDIALOG, pParent)
{

}

CImageDialog::~CImageDialog()
{
}

void CImageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageDialog, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CImageDialog 메시지 처리기입니다.


BOOL CImageDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));

	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain;

		if (FAILED(m_pTerrain->Initialize(false)))
		{
			SafeDelete(m_pTerrain);
			AfxMessageBox(L"Terrain Object Create Failed!!");
			return FALSE;
		}

		m_pTerrain->SetViewWnd(pView);
	}


	for (int i = 0; i < m_pTerrain->GetTile().size(); ++i)
		m_MapPos.insert({ i, m_pTerrain->GetTile()[i]->vPos });


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CImageDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_Point = point;

	Check = true;
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CImageView* pImageView = dynamic_cast<CImageView*>(pMainFrm->m_MainSplt.GetPane(0, 2));
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CTerrain* pTerrain = this->m_pTerrain;


	CTerrain* pterrain = pView->m_pTerrain;
	CMyImage* pImage = pView->m_pImage;
	pTerrain->GetTile();




	_vec3 tempv = { (float)point.x, (float)point.y, 0.f };
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

	for (auto& iter : m_MapPos)
	{
		if (iter.second == vecResult)
		{
			iIdx = iter.first;
			break;
		}
	}

	iIdx;//이미지 인덱스 구함

	if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(pImageView->ObjKey, L"Spring");
		wcscpy_s(pImageView->StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(pImageView->ObjKey, L"Spring");
		wcscpy_s(pImageView->StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(pImageView->ObjKey, L"Spring");
		wcscpy_s(pImageView->StateKey, L"Town_Tile");
	}

	else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(pImageView->ObjKey, L"Summer");
		wcscpy_s(pImageView->StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(pImageView->ObjKey, L"Summer");
		wcscpy_s(pImageView->StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(pImageView->ObjKey, L"Summer");
		wcscpy_s(pImageView->StateKey, L"Town_Tile");
	}

	else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(pImageView->ObjKey, L"Fall");
		wcscpy_s(pImageView->StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(pImageView->ObjKey, L"Fall");
		wcscpy_s(pImageView->StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(pImageView->ObjKey, L"Fall");
		wcscpy_s(pImageView->StateKey, L"Town_Tile");
	}

	else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 0)
	{
		wcscpy_s(pImageView->ObjKey, L"Winter");
		wcscpy_s(pImageView->StateKey, L"Beach_Tile");
	}
	else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 1)
	{
		wcscpy_s(pImageView->ObjKey, L"Winter");
		wcscpy_s(pImageView->StateKey, L"OutDoor_Tile");
	}
	else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 2)
	{
		wcscpy_s(pImageView->ObjKey, L"Winter");
		wcscpy_s(pImageView->StateKey, L"Town_Tile");
	}
	pImageView->iIdx = iIdx;
	pImageView->Check = true;
	CDialog::OnLButtonDown(nFlags, point);
}


void CImageDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CImageDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CMyImage* pImage = pView->m_pImage;

	CDevice::GetInstance()->Render_Begin();

	pImage->Render();
	if (nullptr != m_pTerrain)
		m_pTerrain->Render();

	CDevice::GetInstance()->Render_End(m_hWnd);

	CDialog::OnMouseMove(nFlags, point);
}
