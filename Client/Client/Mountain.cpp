#include "stdafx.h"
#include "Mountain.h"
#include "MyMap.h"

CMountain::CMountain()
{
}


CMountain::~CMountain()
{
}

HRESULT CMountain::Init()
{
	CObjectMgr::GetInstance()->Release_NonePlayer();
	CRenderMgr::GetInstance()->Update_Renderer();

	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_FRONT)
	{
		CScrollMgr::SetScrolling(_vec3{ 0.f, -0.f,0.f });
	}
	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_BACK)
	{
		if (CSceneMgr::GetInstance()->GetBackTileNum() == 1)
		{
			// 전에 있던 scene중에서 밟은 BackTileNum을 가져옴
		}
	}

	CObj* pObj = CAbstractFactory<CMyMap>::CreateObj(OBJECT_ID_MAP, 3);
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_MAP);
	return S_OK;
}

void CMountain::Update(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CMountain::LateUpdate(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);
}

void CMountain::Render()
{
}

void CMountain::Release()
{
}
