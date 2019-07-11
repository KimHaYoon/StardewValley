// ImageViewTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ImageViewTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "MyImage.h"
#include "Terrain.h"
#include "ImageView.h"

// CImageViewTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageViewTool, CDialog)

CImageViewTool::CImageViewTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_IMAGEVIEW, pParent)
{

}

CImageViewTool::~CImageViewTool()
{
}

void CImageViewTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RADIO3, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO4, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO5, m_Radio[2]);
	DDX_Control(pDX, IDC_RADIO6, m_Radio[3]);
	DDX_Control(pDX, IDC_RADIO15, m_Radio[4]);
	DDX_Control(pDX, IDC_LIST4, m_ListBox);
}


BEGIN_MESSAGE_MAP(CImageViewTool, CDialog)
	ON_WM_DROPFILES()
	ON_WM_MOUSEMOVE()
	ON_LBN_SELCHANGE(IDC_LIST4, &CImageViewTool::OnLbnSelchangeList)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageViewTool::OnBnClickedApply)
	ON_BN_CLICKED(IDC_BUTTON6, &CImageViewTool::OnBnClickedCapture)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CImageViewTool 메시지 처리기입니다.


BOOL CImageViewTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR strName[MIN_STR] = L"";
	auto& iter_find = m_mapchar.find(strName);
	CString str = L"";
	if (iter_find == m_mapchar.end())
	{
		for (int i = 0; i < 3; ++i)
		{
			if (i == 0)
			{
				str = L"Beach";
			}
			else if (i == 1)
			{
				str = L"OutDoor";
			}
			else if (i == 2)
			{
				str = L"Town";
			}

			m_mapchar.insert({ str, str });
			m_ListBox.AddString(str);
		}
	}
	return TRUE;  				  
}


void CImageViewTool::OnMouseMove(UINT nFlags, CPoint point)
{


	CDialog::OnMouseMove(nFlags, point);
}


void CImageViewTool::OnLbnSelchangeList()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CMyImage* pImage = pView->m_pImage;


	int Select = m_ListBox.GetCurSel();

	if (Select == -1)
	{
		return;
	}

	CString strTmp = L"";
	m_ListBox.GetText(Select, strTmp);

	if (strTmp == L"Beach")
	{
		pImage->m_iImageNum = 0;
	}
	else if (strTmp == L"OutDoor")
	{
		pImage->m_iImageNum = 1;
	}
	else if(strTmp==L"Town")
	{
		pImage->m_iImageNum = 2;
	}

}

void CImageViewTool::OnBnClickedApply()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CImageView* pImageView= dynamic_cast<CImageView*>(pMainFrm->m_MainSplt.GetPane(0, 2));
	CMyImage* pImage = pView->m_pImage;

	if (m_Radio[0].GetCheck())
	{
		pImage->m_pObjKey = L"Season";
		pImage->m_pStateKey = L"Spring";
	}
	else if (m_Radio[1].GetCheck())
	{
		pImage->m_pObjKey = L"Season";
		pImage->m_pStateKey = L"Summer";
	}
	else if (m_Radio[2].GetCheck())
	{
		pImage->m_pObjKey = L"Season";
		pImage->m_pStateKey = L"Fall";
	}
	else if (m_Radio[3].GetCheck())
	{
		pImage->m_pObjKey = L"Season";
		pImage->m_pStateKey = L"Winter";
	}
	else if (m_Radio[4].GetCheck())
	{
		pImage->m_pObjKey = L"Season";
		pImage->m_pStateKey = L"Path";
	}
	Invalidate(FALSE);
	pImageView->Invalidate(FALSE);
}


void CImageViewTool::OnBnClickedCapture()
{
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CImageView* pImageView = dynamic_cast<CImageView*>(pMainFrm->m_MainSplt.GetPane(0, 2));

	CToolView* pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplt.GetPane(0, 1));
	CMyImage* pImage = pView->m_pImage;


	CTerrain* pTerrain = pImageView->m_pTerrain;
	POINT	point = pImageView->m_Point;


	_vec3 tempv = {(float)point.x, (float)point.y, 0.f};
	_vec3 result = {};
	int iCount = 0;

	for (auto& iter : pTerrain->GetTile())
	{
		result = iter->vPos;
		POINT Start = { (long)result.x - 8, (long)result.y - 8 };
		POINT End = { (long)result.x + 8, (long)result.y + 8 };

		int w = End.x - Start.x;
		int h = End.y - Start.y;

		CImage tips;
		TCHAR tempPath[128] = L"";
		if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 0)
		{
			tips.Load(L"../Texture/Season/Spring/Spring0.png");
			swprintf_s(tempPath, L"../Texture/Season/Spring/Beach_Tile/Beach_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 1)
		{
			tips.Load(L"../Texture/Season/Spring/Spring1.png");
			swprintf_s(tempPath, L"../Texture/Season/Spring/OutDoor_Tile/OutDoor_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Spring"&&pImage->m_iImageNum == 2)
		{
			tips.Load(L"../Texture/Season/Spring/Spring2.png");
			swprintf_s(tempPath, L"../Texture/Season/Spring/Town_Tile/Town_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}

		else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 0)
		{
			tips.Load(L"../Texture/Season/Summer/Summer0.png");
			swprintf_s(tempPath, L"../Texture/Season/Summer/Beach_Tile/Beach_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 1)
		{
			tips.Load(L"../Texture/Season/Summer/Summer1.png");
			swprintf_s(tempPath, L"../Texture/Season/Summer/OutDoor_Tile/OutDoor_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Summer"&&pImage->m_iImageNum == 2)
		{
			tips.Load(L"../Texture/Season/Summer/Summer2.png");
			swprintf_s(tempPath, L"../Texture/Season/Summer/Town_Tile/Town_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}

		else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 0)
		{
			tips.Load(L"../Texture/Season/Fall/Fall0.png");
			swprintf_s(tempPath, L"../Texture/Season/Fall/Beach_Tile/Beach_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 1)
		{
			tips.Load(L"../Texture/Season/Fall/Fall1.png");
			swprintf_s(tempPath, L"../Texture/Season/Fall/OutDoor_Tile/OutDoor_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Fall"&&pImage->m_iImageNum == 2)
		{
			tips.Load(L"../Texture/Season/Fall/Fall2.png");
			swprintf_s(tempPath, L"../Texture/Season/Fall/Town_Tile/Town_Tile%d", iCount);
			wcscat_s(tempPath, L".png");

		}

		else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 0)
		{
			tips.Load(L"../Texture/Season/Winter/Winter0.png");
			swprintf_s(tempPath, L"../Texture/Season/Winter/Beach_Tile/Beach_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 1)
		{
			tips.Load(L"../Texture/Season/Winter/Winter1.png");
			swprintf_s(tempPath, L"../Texture/Season/Winter/OutDoor_Tile/OutDoor_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Winter"&&pImage->m_iImageNum == 2)
		{
			tips.Load(L"../Texture/Season/Winter/Winter2.png");
			swprintf_s(tempPath, L"../Texture/Season/Winter/Town_Tile/Town_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}

		else if (pImage->m_pStateKey == L"Path"&&pImage->m_iImageNum == 0)
		{
			tips.Load(L"../Texture/Season/Path/Path0.png");
			swprintf_s(tempPath, L"../Texture/Season/Path/Beach_Tile/Beach_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Path"&&pImage->m_iImageNum == 1)
		{
			tips.Load(L"../Texture/Season/Path/Path1.png");
			swprintf_s(tempPath, L"../Texture/Season/Path/OutDoor_Tile/OutDoor_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}
		else if (pImage->m_pStateKey == L"Path"&&pImage->m_iImageNum == 2)
		{
			tips.Load(L"../Texture/Season/Path/Path2.png");
			swprintf_s(tempPath, L"../Texture/Season/Path/Town_Tile/Town_Tile%d", iCount);
			wcscat_s(tempPath, L".png");
		}

		CImage temp;
		//temp.SetHasAlphaChannel(true);
 		temp.Create(w, h, tips.GetBPP(), 0);
		DrawClip(temp.GetDC(), &tips, Start, End);
 		temp.ReleaseDC();

		unsigned char * pCol = 0;
		long lw = tips.GetWidth();
		long lh = tips.GetHeight();
		for (long y = 0; y < lh; y++)
		{
			for (long x = 0; x < lw; x++)
			{
				pCol = (unsigned char *)tips.GetPixelAddress(x, y);
				unsigned char alpha = pCol[3];
				if (alpha != 255)
				{
					pCol[0] = ((pCol[0] * alpha) + 128) >> 8;
					pCol[1] = ((pCol[1] * alpha) + 128) >> 8;
					pCol[2] = ((pCol[2] * alpha) + 128) >> 8;
				}
			}
		}
		temp.SetHasAlphaChannel(true);
		temp.Save(tempPath, Gdiplus::ImageFormatPNG);
		++iCount;

	}
}

void CImageViewTool::DrawClip(HDC hDC, CImage * pImage, POINT Start, POINT End, int pos1, int pos2, int pos3)
{
	int x, y, cx, cy;

	if (End.x > Start.x)
	{
		x = Start.x;
		cx = End.x - Start.x;
	}
	else
	{
		x = End.x;
		cx = Start.x - End.x;
	}

	if (End.y > Start.y)
	{
		y = Start.y;
		cy = End.y - Start.y;
	}
	else
	{
		y = End.y;
		cy = Start.y - End.y;
	}
	if (cx&&cy)
	{
		if (pos1 == 0)
		{
			pImage->Draw(hDC, x, y, cx, cy, x, y, cx, cy);
		}
		else
			pImage->Draw(hDC, pos2, pos3, cx, cy, x, y, cx, cy);
	}
}


void CImageViewTool::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
}
