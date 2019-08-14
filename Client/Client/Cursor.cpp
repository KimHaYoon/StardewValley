#include "stdafx.h"
#include "Cursor.h"

CCursor::CCursor()
{
}


CCursor::~CCursor()
{
	Release();
}

HRESULT CCursor::Init()
{
	return S_OK;
}


HRESULT CCursor::Init(OBJECT_ID eID)
{

	m_tInfo.vPos = { WINCX, WINCY, 0.f };
	m_tInfo.vSize = { 0.5f, 0.5f, 0.f };

	//1366 x 768
	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };


	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	ShowCursor(false);
	return S_OK;
}

_int CCursor::Update(const _float & fTimeDelta)
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.vPos = { (float)pt.x, (float)pt.y, 0.f };
	return NO_EVENT;
}

void CCursor::LateUpdate(const _float & fTimeDelta)
{
}

void CCursor::Render()
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, CURSOR);
	NULL_CHECK_VOID(pTexInfo);


	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CCursor::Release()
{
}

