#include "stdafx.h"
#include "Axe.h"

CAxe::CAxe()
{
}


CAxe::~CAxe()
{
	Release();
}

HRESULT CAxe::Init()
{
	return S_OK;
}


HRESULT CAxe::Init(OBJECT_ID eID)
{
	m_pName = L"Axe";

	_float fSize = (float)WINCX / 1920.f * 3.f;
	m_tInfo.vPos = { (float)(WINCX) / 19.f, (float)(WINCY)-(30.f * fSize), 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"Abigail";
	m_strStateKey = L"Abigail_Forward";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	m_eType = ITEM_TOOL;
	m_nCount = 1;

	m_nIndex = 1;
	m_nIndexLine = 0;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CAxe::Update(const _float & fTimeDelta)
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_LEFT))
		m_nIndex--;
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RIGHT))
		m_nIndex++;
	return NO_EVENT;
}

void CAxe::LateUpdate(const _float & fTimeDelta)
{
}

void CAxe::Render()
{
	CItem::Render();
}

void CAxe::Release()
{
}

