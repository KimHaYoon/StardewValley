#include "stdafx.h"
#include "Logo.h"
#include "Obj.h"
#include "MyMap.h"
#include "Terrain.h"
#include "BackTerrain.h"
CLogo::CLogo()
{
}


CLogo::~CLogo()
{
}

HRESULT CLogo::Init()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPathInfo.txt")))
	{
		ERR_MSG(L"Image Load Failed");
		return E_FAIL;
	}
// 	CObj* pObj = CAbstractFactory<CMyMap>::CreateObj();
// 	if (nullptr == pObj)
// 		return E_FAIL;
// 	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_LOGO);


	CObj* pObj = CAbstractFactory<CBackTerrain>::CreateObj(L"../Data/Vacant_Tile_Back.dat");
	if (nullptr == pObj)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);

 	pObj = CAbstractFactory<CTerrain>::CreateObj(L"../Data/Vacant_Tile_Front.dat");
 	if (nullptr == pObj)
 		return E_FAIL;
 	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);
	return S_OK;
}

void CLogo::Update(const _float& fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CLogo::LateUpdate(const _float& fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);
}

void CLogo::Render()
{
	CObjectMgr::GetInstance()->Render();
}

void CLogo::Release()
{
	//CObjectMgr::GetInstance()->Release();
}
