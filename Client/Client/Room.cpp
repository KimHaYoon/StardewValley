#include "stdafx.h"
#include "Room.h"


#include "Player.h"
#include "MyMap.h"
#include "ReactionTerrain.h"



CRoom::CRoom()
{
}


CRoom::~CRoom()
{
	Release();
}

HRESULT CRoom::Init()
{
	CObjectMgr::GetInstance()->Release_NonePlayer();
	CRenderMgr::GetInstance()->Update_Renderer();
	if(CSceneMgr::GetInstance()->GetPass_ID()==PASS_ID_BACK)
		CScrollMgr::SetScrolling(_vec3{ 0.f,0.f,0.f });
	else if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_FRONT)
	{
		CScrollMgr::SetScrolling(_vec3{ 0.f,0.f,0.f });
		CObj* pObj = CAbstractFactory<CPlayer>::CreateObj(OBJECT_ID_PLAYER);
		if (pObj == nullptr)
			return E_FAIL;
		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_PLAYER);
	}

	CObj* pObj = CAbstractFactory<CMyMap>::CreateObj(OBJECT_ID_MAP, 0);
	if (pObj == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_MAP);



	pObj = CAbstractFactory<CReactionTerrain>::CreateObj(L"../Data/Tile/Room/Room_Tile_Reaction.dat");
	if (pObj == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_TERRAIN);


	return S_OK;
}

void CRoom::Update(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CRoom::LateUpdate(const _float & fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);

	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_FRONT)
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::GetInstance()->GetNextScene());
		CSceneMgr::GetInstance()->SetPass_ID(PASS_ID_END, SCENE_ID_END, SCENE_ID_END);
	}
}

void CRoom::Render()
{
	CObjectMgr::GetInstance()->Render();
}

void CRoom::Release()
{

}

