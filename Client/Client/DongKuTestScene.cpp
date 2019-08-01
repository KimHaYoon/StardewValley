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
	if ( FAILED( CTextureMgr::GetInstance()->ReadImgPath( L"../Data/DT.txt" ) ) )
	{
		ERR_MSG( L"Image Load Failed" );
		return E_FAIL;
	}
	CObj* pObj = CAbstractFactory<CBackTerrain>::CreateObj(L"../Data/Mountain_Tile_Back.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CTerrain>::CreateObj(L"../Data/Mountain_Tile_Front.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

	pObj = CAbstractFactory<CPlayer>::CreateObj();
	if ( nullptr == pObj )
		return E_FAIL;

	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_PLAYER );

	return S_OK;
}

void CDongKuTestScene::Update( const _float & fTimeDelta )
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
		CSceneMgr::GetInstance()->SceneChange(SCENE_ID_HAYOON);
	CObjectMgr::GetInstance()->Update( fTimeDelta );
}

void CDongKuTestScene::LateUpdate( const _float & fTimeDelta )
{
	CObjectMgr::GetInstance()->LateUpdate( fTimeDelta );
}

void CDongKuTestScene::Render()
{
	CObjectMgr::GetInstance()->Render();
}

void CDongKuTestScene::Release()
{
	CObjectMgr::GetInstance()->Release();
}
