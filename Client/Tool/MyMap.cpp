#include "stdafx.h"
#include "MyMap.h"
#include "ToolView.h"


CMyMap::CMyMap()
{
}


CMyMap::~CMyMap()
{
	Release();
}

HRESULT CMyMap::Initialize()
{
	return S_OK;
}

void CMyMap::Update()
{
}

void CMyMap::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	TCHAR szBuf[MIN_STR] = L"";

	RECT rc = {};
	m_pViewWnd->GetClientRect(&rc); // 윈도우의 RECT 정보를 얻어옴.

	float fCurWinCX = float(rc.right - rc.left);
	float fCurWinCY = float(rc.bottom - rc.top);

	float fRatioX = WINCX / fCurWinCX;
	float fRatioY = WINCY / fCurWinCY;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		0.f - m_pViewWnd->GetScrollPos(0),
		0.f - m_pViewWnd->GetScrollPos(1),
		0.f);

	matWorld = matScale * matTrans;

	SetRatio(&matWorld, fRatioX, fRatioY);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		L"Map", L"Map", m_iMapNum);
	NULL_CHECK_VOID(pTexInfo);

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMyMap::MiniRender(float fRatio)
{
	D3DXMATRIX matScale, matTrans, matWorld;
	TCHAR szBuf[MIN_STR] = L"";
	RECT rc = {};
	m_pViewWnd->GetClientRect(&rc); // 윈도우의 RECT 정보를 얻어옴.

	float fCurWinCX = float(rc.right - rc.left);
	float fCurWinCY = float(rc.bottom - rc.top);

	float fRatioX = WINCX / fCurWinCX;
	float fRatioY = WINCY / fCurWinCY;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		0.f - m_pViewWnd->GetScrollPos(0),
		0.f - m_pViewWnd->GetScrollPos(1),
		0.f);

	matWorld = matScale * matTrans;
	SetRatio(&matWorld, fRatio, fRatio);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		L"Terrain", L"Map", m_iMapNum);
	NULL_CHECK_VOID(pTexInfo);

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMyMap::Release()
{
}

void CMyMap::SetRatio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
{
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;
}
