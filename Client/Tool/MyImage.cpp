#include "stdafx.h"
#include "MyImage.h"
#include "ToolView.h"

CMyImage::CMyImage()
{
}


CMyImage::~CMyImage()
{
	Release();
}

HRESULT CMyImage::Initialize()
{
	return S_OK;
}

void CMyImage::Update()
{
}

void CMyImage::Render()
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
		0.f,
		0.f,
		0.f);

	matWorld = matScale * matTrans;

	SetRatio(&matWorld, fRatioX, fRatioY);
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_pObjKey, m_pStateKey, m_iImageNum);
	NULL_CHECK_VOID(pTexInfo);

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CMyImage::MiniRender(float fRatio)
{
}

void CMyImage::Release()
{
}

void CMyImage::SetRatio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
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
