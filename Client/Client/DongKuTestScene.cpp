#include "stdafx.h"
#include "DongKuTestScene.h"
#include "Obj.h"
#include "Player.h"
#include "Terrain.h"
#include "BackTerrain.h"


CDongKuTestScene::CDongKuTestScene()
{
}


CDongKuTestScene::~CDongKuTestScene()
{
	Release();
}

HRESULT CDongKuTestScene::Init()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPathInfo.txt")))
	{
		ERR_MSG(L"Image Load Failed");
		return E_FAIL;
	}
	CObj* pObj = CAbstractFactory<CBackTerrain>::CreateObj(L"../Data/Tile/Mountain/Mountain_Tile_Back.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CTerrain>::CreateObj(L"../Data/Tile/Mountain/Mountain_Tile_Front.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CPlayer>::CreateObj(OBJECT_ID_PLAYER);
	if (nullptr == pObj)
		return E_FAIL;

	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_PLAYER);

	return S_OK;
}

void CDongKuTestScene::Update(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CDongKuTestScene::LateUpdate(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);
}

void CDongKuTestScene::Render()
{
	CObjectMgr::GetInstance()->Render();
}

void CDongKuTestScene::Release()
{
	CObjectMgr::GetInstance()->Release();
}
