#include "stdafx.h"
#include "Town.h"

#include "MyMap.h"
#include "ReactionTerrain.h"


CTown::CTown()
{
}


CTown::~CTown()
{
	Release();
}

HRESULT CTown::Init()
{
	CObjectMgr::GetInstance()->Release_NonePlayer();
	CRenderMgr::GetInstance()->Update_Renderer();

	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_FRONT)
	{
		CScrollMgr::SetScrolling(_vec3{ 0.f, 0.f,0.f });
	}
	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_BACK)
	{
		if (CSceneMgr::GetInstance()->GetBackTileNum() == 1)
		{
			// ���� �ִ� scene�߿��� ���� BackTileNum�� ������
		}
	}

	CObj* pObj = CAbstractFactory<CMyMap>::CreateObj(OBJECT_ID_MAP, 2);
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_MAP);

	return S_OK;
}

void CTown::Update(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CTown::LateUpdate(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);
}

void CTown::Render()
{
}

void CTown::Release()
{
}
