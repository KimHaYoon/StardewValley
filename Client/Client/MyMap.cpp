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

	D3DXMatrixScaling(&matScale, 3.f, 3.f, 0.f);
	D3DXMatrixTranslation(&matTrans,
		0.f,
		0.f,
		0.f);

	matWorld = matScale * matTrans;



	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		L"MapImage", L"Map", m_iMapNum);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CMyMap::Release()
{
}

HRESULT CMyMap::Init(OBJECT_ID eID, _int iNum)
{
	m_iMapNum = iNum;
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}
