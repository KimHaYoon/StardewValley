#include "stdafx.h"
#include "DongKuTestScene.h"


CDongKuTestScene::CDongKuTestScene()
{
}


CDongKuTestScene::~CDongKuTestScene()
{
}

HRESULT CDongKuTestScene::Init()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPathInfo.txt")))
	{
		ERR_MSG(L"Image Load Failed");
		return E_FAIL;
	}
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
}

void CDongKuTestScene::Release()
{
}
