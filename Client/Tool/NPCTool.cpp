// NPCTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "NPCTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Terrain.h"
#include "ImageView.h"

// CNPCTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CNPCTool, CDialog)

CNPCTool::CNPCTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_NPCTOOL, pParent)
{

}

CNPCTool::~CNPCTool()
{
}

void CNPCTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO7, m_Radio[2]);
	DDX_Control(pDX, IDC_RADIO8, m_Radio[3]);
	DDX_Control(pDX, IDC_RADIO9, m_Radio[4]);
	DDX_Control(pDX, IDC_RADIO10, m_Radio[5]);
}


BEGIN_MESSAGE_MAP(CNPCTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CNPCTool::OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON1, &CNPCTool::OnBnClickedPathSave)
	ON_BN_CLICKED(IDC_BUTTON11, &CNPCTool::OnBnClickedPathLoad)
	ON_BN_CLICKED(IDC_BUTTON6, &CNPCTool::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON8, &CNPCTool::OnBnClickedClose)
END_MESSAGE_MAP()



BOOL CNPCTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));

	TCHAR strName[MIN_STR] = L"";
	auto& iter_find = m_mapchar.find(strName);
	CString str = L"";

	if (iter_find == m_mapchar.end())
	{
		for (int i = 0; i < 29; ++i)
		{
			if (i == 0)
				str = L"Abigail";
			else if (i == 1)
				str = L"Alex";
			else if (i == 2)
				str = L"Caroline";
			else if (i == 3)
				str = L"Demetrius";
			else if (i == 4)
				str = L"Elliott";
			else if (i == 5)
				str = L"Emily";
			else if (i == 6)
				str = L"Evelyn";
			else if (i == 7)
				str = L"George";
			else if (i == 8)
				str = L"Haley";
			else if (i == 9)
				str = L"Harvey";
			else if (i == 10)
				str = L"Jas";
			else if (i == 11)
				str = L"Jodi";
			else if (i == 12)
				str = L"Kent";
			else if (i == 13)
				str = L"Leah";
			else if (i == 14)
				str = L"Lewis";
			else if (i == 15)
				str = L"Linus";
			else if (i == 16)
				str = L"Marcello";
			else if (i == 17)
				str = L"Marlon";
			else if (i == 18)
				str = L"Marnie";
			else if (i == 19)
				str = L"Maru";
			else if (i == 20)
				str = L"Maru_Hospital";
			else if (i == 21)
				str = L"Morris";
			else if (i == 22)
				str = L"Penny";
			else if (i == 23)
				str = L"Pierre";
			else if (i == 24)
				str = L"Robin";
			else if (i == 25)
				str = L"Sam";
			else if (i == 26)
				str = L"Sandy";
			else if (i == 27)
				str = L"Sebastian";
			else if (i == 28)
				str = L"Vincent";
			m_mapchar.insert({ str,i });
			m_ListBox.AddString(str);
		}
	}
	int i = 0;

	for (int i = 0; i < 6; ++i)
		m_Radio[i].SetCheck(false);
	return TRUE;
}


void CNPCTool::OnLbnSelchangeList()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CTerrain* pTerrain = pView->m_pTerrain;


	int Select = m_ListBox.GetCurSel();

	if (Select == -1)
	{
		return;
	}

	pView->m_bMouseLButtonClick = false;
	pView->NPCName = m_strTmp;
	
	auto& iter_find = m_mapchar.find(m_strTmp);
	if (iter_find == m_mapchar.end())
		return;

	pView->m_iNPCNum = iter_find->second;
}


void CNPCTool::OnBnClickedPathSave()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CFileDialog Dlg(FALSE, L"dat", L"제목없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||", this);

	TCHAR szCurPath[MAX_STR] = L"";

	GetCurrentDirectory(MAX_STR, szCurPath);
	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;	// 절대경로!

	if (IDOK == Dlg.DoModal())
	{




		CString FilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(FilePath.GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Tile Save Failed!!");
			return;
		}

		DWORD dwByte = 0;

		auto& iter = pToolView->m_vecNPCOnlyPath.begin();
		for (; iter != pToolView->m_vecNPCOnlyPath.end(); iter++)
		{
			WriteFile(hFile, *iter, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		}


		CloseHandle(hFile);
	}

	pToolView->m_vecNPCOnlyPath.clear();
	pToolView->m_vecNPCOnlyPath.shrink_to_fit();

}


void CNPCTool::OnBnClickedPathLoad()
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

		pToolView->m_vecNPCOnlyPath.clear();
		pToolView->m_vecNPCOnlyPath.shrink_to_fit();


		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;
		_vec3	vTemp = {};
		while (1)
		{
			ReadFile(hFile, &vTemp, sizeof(_vec3), &dwByte, nullptr);
			if (dwByte == 0)
				break;

			pToolView->m_vecNPCOnlyPath.push_back(vTemp);
		}

		pToolView->Invalidate(FALSE);
		CloseHandle(hFile);
	}
}



void CNPCTool::OnBnClickedApply()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CTerrain* pTerrain = pView->m_pTerrain;


	for (auto& iter : pTerrain->GetTile())
		iter->AlphaCheck = true;

	pView->Invalidate(FALSE);
}


void CNPCTool::OnBnClickedClose()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CTerrain* pTerrain = pView->m_pTerrain;
	pView->m_bMouseLButtonClick = true;

	for (auto& iter : pTerrain->GetTile())
		iter->AlphaCheck = true;
}
