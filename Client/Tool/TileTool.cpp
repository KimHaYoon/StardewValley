// TileTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TileTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"
#include "MyMap.h"
#include "Building.h"
#include "MainFrm.h"
#include "MyForm.h"


// CTileTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTileTool, CDialog)

CTileTool::CTileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TILETOOL, pParent)
{

}

CTileTool::~CTileTool()
{
}

void CTileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_RadioMap[0]);
	DDX_Control(pDX, IDC_RADIO2, m_RadioMap[1]);
	DDX_Control(pDX, IDC_RADIO7, m_RadioMap[2]);
	DDX_Control(pDX, IDC_RADIO8, m_RadioMap[3]);
	DDX_Control(pDX, IDC_RADIO9, m_RadioMap[4]);
	DDX_Control(pDX, IDC_RADIO10, m_RadioMap[5]);
	DDX_Control(pDX, IDC_RADIO11, m_RadioMap[6]);
	DDX_Control(pDX, IDC_RADIO12, m_RadioMap[7]);
	DDX_Control(pDX, IDC_RADIO13, m_RadioMap[8]);
	DDX_Control(pDX, IDC_RADIO14, m_RadioMap[9]);
	DDX_Control(pDX, IDC_RADIO3, m_RadioSeason[0]);
	DDX_Control(pDX, IDC_RADIO4, m_RadioSeason[1]);
	DDX_Control(pDX, IDC_RADIO5, m_RadioSeason[2]);
	DDX_Control(pDX, IDC_RADIO6, m_RadioSeason[3]);
	DDX_Control(pDX, IDC_RADIO16, m_RadioReaction[0]);
	DDX_Control(pDX, IDC_RADIO17, m_RadioReaction[1]);
}


BEGIN_MESSAGE_MAP(CTileTool, CDialog)
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON6, &CTileTool::OnBnClickedTileSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CTileTool::OnBnClickedTileLoad)
	ON_BN_CLICKED(IDC_BUTTON10, &CTileTool::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON13, &CTileTool::OnBnClickedClear)
END_MESSAGE_MAP()

BOOL CTileTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_RadioMap[0].SetCheck(true);
	m_RadioSeason[0].SetCheck(true);
	for (int i = 1; i < 10; ++i)
		m_RadioMap[i].SetCheck(false);
	for (int i = 1; i < 4; ++i)
		m_RadioSeason[i].SetCheck(false);
	for (int i = 0; i < 2; ++i)
		m_RadioReaction[i].SetCheck(false);
	return TRUE;
}


void CTileTool::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView*	pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0,1));

	if (m_RadioReaction[0].GetCheck() == true)
		pView->m_bReactionCheck = true;
	else if (m_RadioReaction[1].GetCheck() == true)
		pView->m_bReactionCheck = false;
}


void CTileTool::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}



void CTileTool::OnBnClickedTileSave()
{
	CFileDialog Dlg(FALSE, L"dat", L"제목없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szCurPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szCurPath);
	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (IDOK == Dlg.DoModal())
	{
		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));

		m_pTile = pToolView->m_pTerrain;
		m_pTile->GetTile();

		CString FilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(FilePath.GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		int i = 0;
		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Tile Save Failed!!");
			return;
		}

		DWORD dwByte = 0;



		auto& iter = m_pTile->GetTile().begin();
		for (; iter != m_pTile->GetTile().end(); iter++)
		{
			WriteFile(hFile, *iter, sizeof(TILE), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}


void CTileTool::OnBnClickedTileLoad()
{
	CFileDialog Dlg(TRUE, L"dat", L"제목없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szCurPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szCurPath);

	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;

	if (IDOK == Dlg.DoModal())
	{
		CString FilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(FilePath.GetString(), GENERIC_READ, 0, 0,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
		m_pTile = pToolView->m_pTerrain;

		m_pTile->Release();

		if (INVALID_HANDLE_VALUE == hFile)
			return;
		
		DWORD dwByte = 0;

		TILE* ppTile = nullptr;
		TILE pT = {};

		while (1)
		{
			ReadFile(hFile, &pT, sizeof(TILE), &dwByte, nullptr);

			int j = m_pTile->GetTile().size();

			if (0 == dwByte)
				break;

			ppTile = new TILE(pT);
			ppTile->AlphaCheck = true;
			m_pTile->GetTile().push_back(ppTile);
		}
		pToolView->Invalidate(FALSE);
		CloseHandle(hFile);
	}



}


void CTileTool::OnBnClickedApply()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CMyMap* Map = pView->m_pMap;
	CTerrain* pTerrain = pView->m_pTerrain;

	
	for (int i = 0; i < 9; ++i)
	{
		if (m_RadioMap[i].GetCheck() == TRUE)
		{
			Map->m_iMapNum = i;		
			break;
		}
	}

	for (int i = 0; i < 4; ++i)
	{
 		if (i == 0)
		{
			if (m_RadioSeason[i].GetCheck() == TRUE)
			{
				for (auto& iter : pTerrain->GetTile())
					wcscpy_s(iter->ObjKey, L"Spring");
				for (int i = 0; i < LAYER_ID_END; ++i)
					for (auto& iter : pView->m_vecBuilding[i])
						wcscpy_s(iter->m_tUintInfo.ObjKey, L"Spring");
			}

		}
		else if (i ==1)
		{
			if (m_RadioSeason[i].GetCheck() == TRUE)
			{
				for (auto& iter : pTerrain->GetTile())
					wcscpy_s(iter->ObjKey, L"Summer");
				for(int i=0;i<LAYER_ID_END;++i)
					for (auto& iter : pView->m_vecBuilding[i])
						wcscpy_s(iter->m_tUintInfo.ObjKey, L"Summer");
			}
		}
		else if (i == 2)
		{
			if (m_RadioSeason[i].GetCheck() == TRUE)
			{
				for (auto& iter : pTerrain->GetTile())
					wcscpy_s(iter->ObjKey, L"Fall");
				for (int i = 0; i < LAYER_ID_END; ++i)
					for (auto& iter : pView->m_vecBuilding[i])
						wcscpy_s(iter->m_tUintInfo.ObjKey, L"Fall");
			}
		}
		else if (i == 3)
		{
			if (m_RadioSeason[i].GetCheck() == TRUE)
			{
				for (auto& iter : pTerrain->GetTile())
					wcscpy_s(iter->ObjKey, L"Winter");
				for (int i = 0; i < LAYER_ID_END; ++i)
					for (auto& iter : pView->m_vecBuilding[i])
						wcscpy_s(iter->m_tUintInfo.ObjKey, L"Winter");
			}
		}
	}
	pView->Invalidate(FALSE);
}


void CTileTool::OnBnClickedClear()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CTerrain* pTerrain = pView->m_pTerrain;


	for (auto& iter : pTerrain->GetTile())
	{
		iter->byDrawID = 2100;
	}
	pView->Invalidate(FALSE);
}
