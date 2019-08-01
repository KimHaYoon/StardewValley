#include "stdafx.h"
#include "HaYoonTestScene.h"
#include "Bat.h"

CHaYoonTestScene::CHaYoonTestScene()
{
}


CHaYoonTestScene::~CHaYoonTestScene()
{
}

HRESULT CHaYoonTestScene::Init()
{
	if ( FAILED( CTextureMgr::GetInstance()->ReadImgPath( L"../Data/ImgPathInfo.txt" ) ) )
	{
		ERR_MSG( L"Image Load Failed" );
		return E_FAIL;
	}

	CObj* pObj = CAbstractFactory<CBat>::CreateObj( OBJECT_ID_MONSTER );
	if ( nullptr == pObj )
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject( pObj, OBJECT_ID_MONSTER );

	return S_OK;
}

void CHaYoonTestScene::Update( const _float & fTimeDelta )
{
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
