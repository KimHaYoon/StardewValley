#include "stdafx.h"
#include "HaYoonTestScene.h"
#include "MonsterMgr.h"

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

	CMonsterMgr::GetInstance()->GetInstance()->LoadMonsterInfo();

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
