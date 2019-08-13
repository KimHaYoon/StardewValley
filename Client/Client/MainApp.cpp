#include "stdafx.h"
#include "MainApp.h"
#include "Terrain.h"


CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
	Release();
}

HRESULT CMainApp::Initialize()
{
	locale::global(locale("kor"));
	if (FAILED(CDevice::GetInstance()->InitDevice()))
		return E_FAIL;

	if (FAILED(CSceneMgr::GetInstance()->SceneChange(SCENE_ID_DONGKU)))
	{
		ERR_MSG(L"Scene change Failed!!");
		return E_FAIL;
	}


	CTimerMgr::GetInstance()->InitTime();

	CMyFont::GetInstance()->Ready_Font(L"Dong", 7, 5, L"Arial");
	CMyFont::GetInstance()->Get_Font(L"Dong");	// 이 함수 호출로 사용할 폰트 가져옴



	/*for (auto& iter : CObjectMgr::GetInstance()->GetTerrain())
	{
		if (dynamic_cast<CTerrain*>(iter)->GetFront() == 100)
		{

		}
	}*/
	return S_OK;
}

void CMainApp::Update()
{
	CTimerMgr::GetInstance()->UpdateTime();
	m_fTimeDelta=CTimerMgr::GetInstance()->GetDeltaTime();
	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update(m_fTimeDelta);
}

void CMainApp::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate(m_fTimeDelta);
}

void CMainApp::Render()
{
	CDevice::GetInstance()->GetDevice()->Clear(0, nullptr, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
		| D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	CDevice::GetInstance()->Render_Begin();

	//m_pSceneMgr->Render();
	CRenderMgr::GetInstance()->RenderGroup();

	CDevice::GetInstance()->Render_End();


	CDevice::GetInstance()->Render_Begin();

	CFrameMgr::GetInstance()->RenderFrame();

	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}

void CMainApp::Release()
{
	CMyFont::GetInstance()->DestroyInstance();
	CFontMgr::GetInstance()->DestroyInstance();//
	CObjectMgr::GetInstance()->DestroyInstance();//
	CRenderMgr::GetInstance()->DestroyInstance();//
	CPathMgr::GetInstance()->DestroyInstance();//
	CKeyMgr::GetInstance()->DestroyInstance();//
	CSceneMgr::GetInstance()->DestroyInstance();//
	CTextureMgr::GetInstance()->DestroyInstance();	//
	CFrameMgr::GetInstance()->DestroyInstance();//
	CTimerMgr::GetInstance()->DestroyInstance();//
	CCollisionMgr::GetInstance()->DestroyInstance();
	CMonsterMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();//
}

void CMainApp::KeyInput(const _float & fTimeDelta)
{
	
}
