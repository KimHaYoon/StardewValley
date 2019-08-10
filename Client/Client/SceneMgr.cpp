#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Logo.h"
#include "Stage.h"
#include "DongKuTestScene.h"
#include "HaYoonTestScene.h"
#include "Room.h"
#include "BusStop.h"
#include "Town.h"
_IMPLEMENT_SINGLETON(CSceneMgr)
CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SceneChange(SCENE_ID eCurScene)
{
	if (m_eTempScene != eCurScene)
	{
		SafeDelete(m_pScene);

		switch (eCurScene)
		{
		case SCENE_ID_LOGO:
			m_pScene = new CLogo;
			break;
		case SCENE_ID_STAGE:
			m_pScene = new CStage;
			break;
		case SCENE_ID_ROOM:
			m_pScene = new CRoom;
			break;
		case SCENE_ID_BUSSTOP:
			m_pScene = new CBusStop;
			break;
		case SCENE_ID_TOWN:
			m_pScene = new CTown;
			break;
		case SCENE_ID_DONGKU:
			m_pScene = new CDongKuTestScene;
			break;
		case SCENE_ID_HAYOON:
			m_pScene = new CHaYoonTestScene;
			break;
		}

		if (FAILED(m_pScene->Init()))
		{
			ERR_MSG(L"Scene Create Failed");
			return E_FAIL;
		}
	}
	m_eCurScene = eCurScene;
	m_eTempScene = eCurScene;

	return S_OK;
}

void CSceneMgr::Update(const _float& fTimeDelta)
{
	m_pScene->Update(fTimeDelta);
}

void CSceneMgr::LateUpdate(const _float& fTimeDelta)
{
	m_pScene->LateUpdate(fTimeDelta);
}

void CSceneMgr::Render()
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
}

void CSceneMgr::SetPass_ID(PASS_ID eID, SCENE_ID eNextSceneID, SCENE_ID ePreSceneID)
{
	m_ePass_ID = eID;
	m_eNextScene = eNextSceneID;
	m_ePreScene = ePreSceneID;
}

void CSceneMgr::SetTileNum(_int iFrontTileNum, _int iBackTileNum)
{
	m_iBackTileNum = iBackTileNum;
	m_iFrontTileNum = iFrontTileNum;
}
