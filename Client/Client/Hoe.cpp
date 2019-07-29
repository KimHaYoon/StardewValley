#include "stdafx.h"
#include "Hoe.h"

CHoe::CHoe()
{
}


CHoe::~CHoe()
{
	Release();
}

HRESULT CHoe::Init()
{
	return S_OK;
}


HRESULT CHoe::Init(OBJECT_ID eID)
{
	m_pName = L"Hoe";

	_float fSize = (float)WINCX / 1920.f * 3.f;
	m_tInfo.vPos = { (float)(WINCX) / 19.f, (float)(WINCY)-(30.f * fSize), 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"Kent";
	m_strStateKey = L"Kent_Forward";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	m_eType = ITEM_TOOL;
	m_nCount = 1;

	m_nIndex = 3;
	m_nIndexLine = 0;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CHoe::Update(const _float & fTimeDelta)
{
	return NO_EVENT;
}

void CHoe::LateUpdate(const _float & fTimeDelta)
{
}

void CHoe::Render()
{
	CItem::Render();
}

void CHoe::Release()
{
}

