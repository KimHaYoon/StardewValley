#include "stdafx.h"
#include "HaYoonTestScene.h"
#include "MonsterMgr.h"
#include "Bat.h"
#include "BackTerrain.h"

CHaYoonTestScene::CHaYoonTestScene()
{
}


CHaYoonTestScene::~CHaYoonTestScene()
{
	CMonsterMgr::GetInstance()->DestroyInstance();
}

HRESULT CHaYoonTestScene::Init()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPathInfo.txt")))
	{
		ERR_MSG(L"Image Load Failed");
		return E_FAIL;
	}
	CObj* pObj = CAbstractFactory<CBackTerrain>::CreateObj( L"../Data/Mountain_Tile_Back.dat" );
	if ( nullptr == pObj )
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_TERRAIN );

	CMonsterMgr::GetInstance()->GetInstance()->LoadMonsterInfo();
	pObj = CAbstractFactory<CBat>::CreateObj();
	if ( !pObj )
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_MONSTER );

	return S_OK;
}

void CHaYoonTestScene::Update(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CHaYoonTestScene::LateUpdate(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);
}

void CHaYoonTestScene::Render()
{
	CObjectMgr::GetInstance()->Render();
}


void CHaYoonTestScene::Release()
{

}
