#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Logo.h"
#include "Stage.h"
#include "DongKuTestScene.h"
#include "HaYoonTestScene.h"
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
	if (m_ePreScene != eCurScene)
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

		m_eCurScene = eCurScene;
		m_ePreScene = eCurScene;
	}

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
