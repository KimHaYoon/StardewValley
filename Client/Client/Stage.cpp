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
}

HRESULT CStage::Init()
{
	CScrollMgr::SetScrolling(_vec3{56.f, -24.f,0.f});
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
}

void CStage::Render()
{
}

void CStage::Release()
{
	CObjectMgr::GetInstance()->CObjectMgr::GetInstance()->Release_NonePlayer();
}
