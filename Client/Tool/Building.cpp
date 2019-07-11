#include "stdafx.h"
#include "Building.h"
#include "ToolView.h"

CBuilding::CBuilding()
{
}


CBuilding::~CBuilding()
{
	Release();
}

HRESULT CBuilding::Initialize()
{
	return S_OK;
}

void CBuilding::Update()
{
}

void CBuilding::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	TCHAR szBuf[MIN_STR] = L"";

	RECT rc = {};
	m_pViewWnd->GetClientRect(&rc);

	float fCurWinCX = float(rc.right - rc.left);
	float fCurWinCY = float(rc.bottom - rc.top);

	float fRatioX = WINCX / fCurWinCX;
	float fRatioY = WINCY / fCurWinCY;


	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_tUintInfo.ObjKey, m_tUintInfo.StateKey, m_tUintInfo.iMapNum);

	NULL_CHECK_VOID(pTexInfo);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tUintInfo.vPos.x - pTexInfo->tImgInfo.Width / 2 - m_pViewWnd->GetScrollPos(0),
		m_tUintInfo.vPos.y - pTexInfo->tImgInfo.Height / 2 - m_pViewWnd->GetScrollPos(1),
		0.f);

	matWorld = matScale * matTrans;

	SetRatio(&matWorld, fRatioX, fRatioY);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);


	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBuilding::MiniRender(float fRatio)
{
}

void CBuilding::AlphaRender(POINT pt)
{
	D3DXMATRIX matScale, matTrans, matWorld;
	TCHAR szBuf[MIN_STR] = L"";

	RECT rc = {};
	m_pViewWnd->GetClientRect(&rc);

	float fCurWinCX = float(rc.right - rc.left);
	float fCurWinCY = float(rc.bottom - rc.top);

	float fRatioX = WINCX / fCurWinCX;
	float fRatioY = WINCY / fCurWinCY;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_tUintInfo.ObjKey, m_tUintInfo.StateKey, m_tUintInfo.iMapNum);
	NULL_CHECK_VOID(pTexInfo);


	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		pt.x-pTexInfo->tImgInfo.Width/2 - m_pViewWnd->GetScrollPos(0),
		pt.y - pTexInfo->tImgInfo.Height / 2 - m_pViewWnd->GetScrollPos(1),
		0.f);

	matWorld = matScale * matTrans;

	SetRatio(&matWorld, fRatioX, fRatioY);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);



	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(150, 255, 255, 255));
}

void CBuilding::Release()
{
}

void CBuilding::SetRatio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
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
