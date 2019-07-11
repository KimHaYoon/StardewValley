#include "stdafx.h"
#include "MyMap.h"

CMyMap::CMyMap()
{

}
CMyMap::~CMyMap()
{

}
HRESULT CMyMap::Init()
{
	m_tInfo.vPos = { 400.f, 300.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	m_strStateKey = L"Forward_Idle";
	m_tFrame = { 0.f, 10.f };
	return S_OK;
}

_int CMyMap::Update(const _float& fTimeDelta)
{
	return NO_ERROR;
}
void CMyMap::LateUpdate(const _float& fTimeDelta)
{
	CObj::MoveFrame();
}
void CMyMap::Render()
{
	D3DXMATRIX matScale, matTrans, matWorld;
	TCHAR szBuf[MIN_STR] = L"";

	RECT rc = {};

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

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		L"MapImage", L"Map", (_int)m_tFrame.fFrame);
	NULL_CHECK_VOID(pTexInfo);

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0, 0, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CMyMap::Release()
{
}