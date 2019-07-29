#include "stdafx.h"
#include "Pickaxe.h"

CPickaxe::CPickaxe()
{
}


CPickaxe::~CPickaxe()
{
	Release();
}

HRESULT CPickaxe::Init()
{
	return S_OK;
}


HRESULT CPickaxe::Init(OBJECT_ID eID)
{
	m_pName = L"Pickaxe";

	_float fSize = (float)WINCX / 1920.f * 3.f;
	m_tInfo.vPos = { (float)(WINCX) / 19.f, (float)(WINCY)-(30.f * fSize), 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"Emily";
	m_strStateKey = L"Emily_Forward";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	m_eType = ITEM_TOOL;
	m_nCount = 1;

	m_nIndex = 3;
	m_nIndexLine = 0;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CPickaxe::Update(const _float & fTimeDelta)
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_LEFT))
		m_nIndex--;
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RIGHT))
		m_nIndex++;
	return NO_EVENT;
}

void CPickaxe::LateUpdate(const _float & fTimeDelta)
{
}

void CPickaxe::Render()
{
	CItem::Render();
}

void CPickaxe::Release()
{
}

