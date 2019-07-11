// PathFinder.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "PathFinder.h"
#include "afxdialogex.h"
#include "FileInfo.h"


// CPathFinder 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPathFinder, CDialog)

CPathFinder::CPathFinder(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PATHFINDER, pParent)
{

}

CPathFinder::~CPathFinder()
{
}

void CPathFinder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPathFinder, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPathFinder::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON6, &CPathFinder::OnBnClickedLoad)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CPathFinder 메시지 처리기입니다.


void CPathFinder::OnBnClickedSave()
{
	UpdateData(TRUE);

	CFileDialog Dlg(FALSE, L"txt", L"제목없음.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Txt Files(*.txt)|*.txt||", this);

	TCHAR szCurPath[MAX_STR] = L"";
	GetCurrentDirectory(MAX_STR, szCurPath);


	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;	

	if (IDOK == Dlg.DoModal())
	{
		wofstream fout;
		fout.open(Dlg.GetPathName().GetString());

		if (fout.fail())
			return;

		wstring wstrCombined = L"";
		TCHAR szCount[MIN_STR] = L"";

		for (auto& pImgPathInfo : m_ImgInfoLst)
		{
			_itow_s(pImgPathInfo->iCount, szCount, 10);

			wstrCombined = pImgPathInfo->wstrObjKey + L"|" + pImgPathInfo->wstrStateKey + L"|"
				+ szCount + L"|" + pImgPathInfo->wstrPath;

			fout << wstrCombined << endl;
		}

		fout.close();
	}

	UpdateData(FALSE);

	WinExec("notepad.exe ../Data/ImgPathInfo.txt", SW_SHOW);
}


void CPathFinder::OnBnClickedLoad()
{
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, L"txt", L"제목없음.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Txt Files(*.txt)|*.txt||", this);

	TCHAR szCurPath[MAX_STR] = L"";

	// GetCurrentDirectory: 현재 작업경로를 얻어옴.
	GetCurrentDirectory(MAX_STR, szCurPath);

	PathRemoveFileSpec(szCurPath);
	lstrcat(szCurPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szCurPath;	

	if (IDOK == Dlg.DoModal())
	{
		wifstream fin;
		fin.open(Dlg.GetPathName().GetString());

		if (fin.fail())
			return;

		m_ListBox.ResetContent();

		for_each(m_ImgInfoLst.begin(), m_ImgInfoLst.end(), SafeDelete<IMGPATHINFO*>);
		m_ImgInfoLst.clear();

		wstring wstrCombined = L"";
		TCHAR szBuf[MAX_STR] = L"";

		IMGPATHINFO* pImgPathInfo = nullptr;

		while (true)
		{
			wstrCombined = L"";
			pImgPathInfo = new IMGPATHINFO;

			fin.getline(szBuf, MAX_STR, '|');
			wstrCombined += wstring(szBuf) += L"|"; 
			pImgPathInfo->wstrObjKey = szBuf;

			fin.getline(szBuf, MAX_STR, '|');
			wstrCombined += wstring(szBuf) += L"|";
			pImgPathInfo->wstrStateKey = szBuf;

			fin.getline(szBuf, MAX_STR, '|');
			wstrCombined += wstring(szBuf) += L"|";
			pImgPathInfo->iCount = _wtoi(szBuf);

			fin.getline(szBuf, MAX_STR);
			wstrCombined += szBuf;
			pImgPathInfo->wstrPath = szBuf;

			if (fin.eof())
			{
				SafeDelete(pImgPathInfo);
				break;
			}

			m_ListBox.AddString(wstrCombined.c_str());
			m_ImgInfoLst.push_back(pImgPathInfo);
		}

		fin.close();
	}

	SetHorizontalScroll();

	UpdateData(FALSE);
}


BOOL CPathFinder::OnInitDialog()
{
	CDialog::OnInitDialog();



	return TRUE;  
}


void CPathFinder::OnDropFiles(HDROP hDropInfo)
{
	CDialog::OnDropFiles(hDropInfo);

	UpdateData(TRUE);

	int iCount = DragQueryFile(hDropInfo, -1, nullptr, 0);

	TCHAR szFullPath[MAX_STR] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, MAX_STR);
		CFileInfo::DirInfoExtraction(szFullPath, m_ImgInfoLst);
	}

	wstring wstrCombined = L"";
	TCHAR szCount[MIN_STR] = L"";

	for (auto& pImgPathInfo : m_ImgInfoLst)
	{
		_itow_s(pImgPathInfo->iCount, szCount, 10);

		wstrCombined = pImgPathInfo->wstrObjKey + L"|" + pImgPathInfo->wstrStateKey + L"|"
			+ szCount + L"|" + pImgPathInfo->wstrPath;

		m_ListBox.AddString(wstrCombined.c_str());
	}

	SetHorizontalScroll();

	UpdateData(FALSE);
}

void CPathFinder::SetHorizontalScroll()
{
	CString strName = L"";
	CSize	size;

	int iCX = 0;

	CDC* pDC = m_ListBox.GetDC();
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		size = pDC->GetTextExtent(strName);

		if (size.cx > iCX)
			iCX = size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	if (iCX > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iCX);
}
