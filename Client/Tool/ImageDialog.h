#pragma once


// CImageDialog ��ȭ �����Դϴ�.
#include "Terrain.h"
class CImageDialog : public CDialog
{
	DECLARE_DYNAMIC(CImageDialog)

public:
	CImageDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
public:
	CTerrain*	m_pTerrain = nullptr;
	POINT		m_Point;
	int			m_iNumTileMapNum = 0;
	map<_int, _vec3>	m_MapPos;
	TCHAR		ObjKey[128] = L"";
	TCHAR		StateKey[128] = L"";
	int			iIdx = 0;
	bool		Check = false;
};
