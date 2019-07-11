// ObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Building.h"


// CObjectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectTool, CDialog)

CObjectTool::CObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
{

}

CObjectTool::~CObjectTool()
{
}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO7, m_Radio[2]);
	DDX_Control(pDX, IDC_RADIO8, m_Radio[3]);
	DDX_Control(pDX, IDC_RADIO9, m_Radio[4]);
}


BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectTool::OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectTool::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON11, &CObjectTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON12, &CObjectTool::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_BUTTON3, &CObjectTool::OnBnClickedClear)
END_MESSAGE_MAP()


// CObjectTool 메시지 처리기입니다.


void CObjectTool::OnLbnSelchangeList()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));


	int Select = m_ListBox.GetCurSel();

	if (Select == -1)
	{
		return;
	}

	CString strTmp = L"";
	m_ListBox.GetText(Select, strTmp);

	auto& iter_find = m_mapchar.find(strTmp);

	if (iter_find == m_mapchar.end())
		return;

	m_tInfo.iMapNum = iter_find->second.iMapNum;
}


void CObjectTool::OnBnClickedApply()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));

	if (m_Radio[0].GetCheck() == TRUE)
	{
		m_tInfo.eID = LAYER_ID_1;
	}
	else if (m_Radio[1].GetCheck() == TRUE)
	{
		m_tInfo.eID = LAYER_ID_2;
	}
	else if (m_Radio[2].GetCheck() == TRUE)
	{
		m_tInfo.eID = LAYER_ID_3;
	}
	else if (m_Radio[3].GetCheck() == TRUE)
	{
		m_tInfo.eID = LAYER_ID_4;
	}
	else if (m_Radio[4].GetCheck() == TRUE)
	{
		m_tInfo.eID = LAYER_ID_5;
	}
	
	wcscpy_s(m_tInfo.ObjKey, L"Spring");
	wcscpy_s(m_tInfo.StateKey, L"Building");
	m_tInfo.Check = true;
	pView->m_bCheck = true;
}


BOOL CObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR strName[MIN_STR] = L"";
	auto& iter_find = m_mapchar.find(strName);
	CString str = L"";
	UNITIFNO tinfo;
	if (iter_find == m_mapchar.end())
	{
		for (int i = 0; i < 26; ++i)
		{
			if (i == 0)
			{
				str = L"Beach House0";
			}
			else if (i == 1)
			{
				str = L"Beach House1";
			}
			else if (i == 2)
			{
				str = L"Out Door House0";
			}
			else if (i == 3)
			{
				str = L"Out Door House1";

			}
			else if (i == 4)
			{
				str = L"Out Door House2";
			}
			else if (i == 5)
			{
				str = L"Out Door House3";
			}
			else if (i == 6)
			{
				str = L"Out Door House4";
			}
			else if (i == 7)
			{
				str = L"Out Door House5";
			}
			else if (i == 8)
			{
				str = L"Out Door House6";
			}
			else if (i == 9)
			{
				str = L"Out Door House7";
			}
			else if (i == 10)
			{
				str = L"Town House0";
			}
			else if (i == 11)
			{
				str = L"Town House1";
			}
			else if (i == 12)
			{
				str = L"Town House2";
			}
			else if (i == 13)
			{
				str = L"Town House3";
			}
			else if (i == 14)
			{
				str = L"Town House4";
			}
			else if (i == 15)
			{
				str = L"Town House5";
			}
			else if (i == 16)
			{
				str = L"Town House6";
			}
			else if (i == 17)
			{
				str = L"Town House7";
			}
			else if (i == 18)
			{
				str = L"Town House8";
			}
			else if (i == 19)
			{
				str = L"Town House9";
			}
			else if (i == 20)
			{
				str = L"Town House10";
			}
			else if (i == 21)
			{
				str = L"Town House11";
			}
			else if (i == 22)
			{
				str = L"Town House12";
			}
			else if (i == 23)
			{
				str = L"Town House13";
			}
			else if (i == 24)
			{
				str = L"Town House14";
			}
			else if (i == 25)
			{
				str = L"Town House15";
			}
			tinfo.iMapNum = i;
			wcscpy_s(tinfo.ObjKey, L"Spring");
			wcscpy_s(tinfo.StateKey,L"Building");
			m_mapchar.insert({ str, tinfo });
			m_ListBox.AddString(str);
		}
	}

	return TRUE;  
}


void CObjectTool::OnBnClickedSave()
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

		

		CString FilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(FilePath.GetString(), GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"Tile Save Failed!!");
			return;
		}

		DWORD dwByte = 0;



		for (int i = 0; i < LAYER_ID_END; ++i)
		{
			for (auto& iter : pToolView->m_vecBuilding[i])
			{			
				WriteFile(hFile, (void*)&iter->m_tUintInfo, sizeof(UNITIFNO), &dwByte, nullptr);
			}
		}


		CloseHandle(hFile);
	}
}


void CObjectTool::OnBnClickedLoad()
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

	
		for (int i = 0; i < LAYER_ID_END; ++i)
		{
			for (auto& iter : pToolView->m_vecBuilding[i])
					SafeDelete(iter);
			pToolView->m_vecBuilding[i].clear();
		}

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;

	

		while (1)
		{
			UNITIFNO tunit = {};
			CBuilding* pBuilding = new CBuilding;
			ReadFile(hFile, &tunit, sizeof(UNITIFNO), &dwByte, nullptr);

			if (0 == dwByte)
				break;
			pBuilding->m_tUintInfo = tunit;
			pBuilding->SetViewWnd(pToolView);
			if (tunit.eID == LAYER_ID_1)
				pToolView->m_vecBuilding[LAYER_ID_1].push_back(pBuilding);			
			else if (tunit.eID == LAYER_ID_2)
				pToolView->m_vecBuilding[LAYER_ID_2].push_back(pBuilding);
			else if (tunit.eID == LAYER_ID_3)
				pToolView->m_vecBuilding[LAYER_ID_3].push_back(pBuilding);
			else if (tunit.eID == LAYER_ID_4)
				pToolView->m_vecBuilding[LAYER_ID_4].push_back(pBuilding);
			else if (tunit.eID == LAYER_ID_5)
				pToolView->m_vecBuilding[LAYER_ID_5].push_back(pBuilding);
		}
		pToolView->Invalidate(FALSE);
		CloseHandle(hFile);
	}
}


void CObjectTool::OnBnClickedClear()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));

	for (int i = 0; i < LAYER_ID_END; ++i)
	{

		for (auto& iter : pToolView->m_vecBuilding[i])
			SafeDelete(iter);
		pToolView->m_vecBuilding[i].clear();
		pToolView->m_vecBuilding[i].shrink_to_fit();
	}

	pToolView->Invalidate(FALSE);
}
