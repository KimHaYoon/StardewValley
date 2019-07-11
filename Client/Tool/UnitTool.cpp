// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
{

}

CUnitTool::~CUnitTool()
{
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_RADIO4, m_Radio[3]);
	DDX_Control(pDX, IDC_RADIO5, m_Radio[4]);

	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)

	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedApply)
END_MESSAGE_MAP()



void CUnitTool::OnLbnSelchangeList()
{

}


void CUnitTool::OnBnClickedApply()
{

}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR strName[MIN_STR] = L"";
	auto& iter_find = m_mapchar.find(strName);
	CString str = L"";
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
			m_mapchar.insert({ str, str });
			m_ListBox.AddString(str);
		}
	}

	return TRUE;
}
