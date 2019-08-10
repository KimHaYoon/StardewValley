#include "stdafx.h"
#include "Stage.h"

#include "BackTerrain.h"
#include "Terrain.h"
#include "ReactionTerrain.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

HRESULT CStage::Init()
{
	CObjectMgr::GetInstance()->Release_NonePlayer();
	CRenderMgr::GetInstance()->Update_Renderer();
	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_FRONT)
		CScrollMgr::SetScrolling(_vec3{56.f, -24.f,0.f});
	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_BACK)
	{
		if (CSceneMgr::GetInstance()->GetBackTileNum() == 1)
		{
			CScrollMgr::SetScrolling(_vec3{ 56.f, -24.f,0.f });
		}
	}
	CObj* pObj = CAbstractFactory<CBackTerrain>::CreateObj(L"../Data//Tile/Vacant/Vacant_Tile_Back.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CTerrain>::CreateObj(L"../Data//Tile/Vacant/Vacant_Tile_Front.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CReactionTerrain>::CreateObj(L"../Data/Tile/Vacant/Vacant_Tile_Reaction.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);
	return S_OK;
}

void CStage::Update(const _float& fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CStage::LateUpdate(const _float& fTimeDelta)
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

void CStage::Render()
{
}

void CStage::Release()
{
}
