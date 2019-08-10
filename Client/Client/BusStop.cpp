#include "stdafx.h"
#include "BusStop.h"
#include "MyMap.h"

#include "Terrain.h"
#include "ReactionTerrain.h"
#include "BackTerrain.h"

CBusStop::CBusStop()
{
}


CBusStop::~CBusStop()
{
}

HRESULT CBusStop::Init()
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

	CObj* pObj = CAbstractFactory<CMyMap>::CreateObj(OBJECT_ID_MAP, 6);
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_MAP);

	pObj = CAbstractFactory<CBackTerrain>::CreateObj(L"../Data//Tile/BusStop/BusStop_Tile_Back.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CTerrain>::CreateObj(L"../Data//Tile/BusStop/BusStop_Tile_Front.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CReactionTerrain>::CreateObj(L"../Data//Tile/BusStop/BusStop_Tile_Reaction.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	return S_OK;
}

void CBusStop::Update(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CBusStop::LateUpdate(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);

	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_FRONT)
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::GetInstance()->GetNextScene());
		CSceneMgr::GetInstance()->SetPass_ID(PASS_ID_END, SCENE_ID_END, SCENE_ID_END);
	}
	else if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_BACK)
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::GetInstance()->GetPreScene());
		CSceneMgr::GetInstance()->SetPass_ID(PASS_ID_END, SCENE_ID_END, SCENE_ID_END);
	}

}

void CBusStop::Render()
{
	
}

void CBusStop::Release()
{
}
