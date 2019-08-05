#include "stdafx.h"
#include "HaYoonTestScene.h"
#include "Bat.h"
#include "Clock.h"
#include "GameTime.h"
#include "BackTerrain.h"
#include "Terrain.h"
#include "CropManager.h"
#include "Crop.h"

CHaYoonTestScene::CHaYoonTestScene()
{
}


CHaYoonTestScene::~CHaYoonTestScene()
{
	CGameTime::GetInstance()->DestroyInstance();
	CCropManager::GetInstance()->DestroyInstance();
}

HRESULT CHaYoonTestScene::Init()
{
	if ( FAILED( CTextureMgr::GetInstance()->ReadImgPath( L"../Data/ImgPathInfo.txt" ) ) )
	{
		ERR_MSG( L"Image Load Failed" );
		return E_FAIL;
	}
	CObj* pObj = CAbstractFactory<CBackTerrain>::CreateObj( L"../Data//Tile/Vacant/Vacant_Tile_Back.dat" );
	if ( nullptr == pObj )
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_TERRAIN );

	pObj = CAbstractFactory<CTerrain>::CreateObj( L"../Data//Tile/Vacant/Vacant_Tile_Front.dat" );
	if ( nullptr == pObj )
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_TERRAIN );


	pObj = CAbstractFactory<CBat>::CreateObj( OBJECT_ID_MONSTER );
	if ( nullptr == pObj )
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_MONSTER );

	pObj = CAbstractFactory<CClock>::CreateObj( OBJECT_ID_UI );
	if ( nullptr == pObj )
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_UI );

	CCropManager::GetInstance()->LoadCropInfo();

	pObj = CAbstractFactory<CCrop>::CreateObj( OBJECT_ID_CROP );
	if ( nullptr == pObj )
		return E_FAIL;
	( ( CCrop* )pObj )->SetCropName( "Parsnip" );
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_CROP );

	return S_OK;
}

void CHaYoonTestScene::Update( const _float & fTimeDelta )
{
	CGameTime::GetInstance()->Update( fTimeDelta );
	CGameTime::GetInstance()->Input( );
	CObjectMgr::GetInstance()->Update( fTimeDelta );
}

void CHaYoonTestScene::LateUpdate( const _float & fTimeDelta )
{
	CObjectMgr::GetInstance()->LateUpdate( fTimeDelta );
}

void CHaYoonTestScene::Render()
{
	CObjectMgr::GetInstance()->Render();
}


void CHaYoonTestScene::Release()
{

}
