#include "stdafx.h"
#include "MainApp.h"


CMainApp::CMainApp()
{
	m_pDevice = CDevice::GetInstance();
	m_pSceneMgr = CSceneMgr::GetInstance();

}


CMainApp::~CMainApp()
{
	Release();
}

HRESULT CMainApp::Initialize()
{
	locale::global(locale("kor"));
	if (FAILED(m_pDevice->InitDevice()))
		return E_FAIL;

	if (FAILED(m_pSceneMgr->SceneChange(SCENE_ID_LOGO)))
	{
		ERR_MSG(L"Scene change Failed!!");
		return E_FAIL;
	}


	CTimerMgr::GetInstance()->InitTime();

	return S_OK;
}

void CMainApp::Update()
{
	CTimerMgr::GetInstance()->UpdateTime();
	m_fTimeDelta=CTimerMgr::GetInstance()->GetDeltaTime();
	CKeyMgr::GetInstance()->Update();
	m_pSceneMgr->Update(m_fTimeDelta);
}

void CMainApp::LateUpdate()
{
	m_pSceneMgr->LateUpdate(m_fTimeDelta);
}

void CMainApp::Render()
{
	m_pDevice->GetDevice()->Clear(0, nullptr, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
		| D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	m_pDevice->Render_Begin();

	//m_pSceneMgr->Render();
	CRenderMgr::GetInstance()->RenderGroup();

	m_pDevice->Render_End();


	m_pDevice->Render_Begin();

	CFrameMgr::GetInstance()->RenderFrame();

	m_pDevice->Render_End();
	m_pDevice->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}

void CMainApp::Release()
{
	CFontMgr::GetInstance()->DestroyInstance();
	CObjectMgr::GetInstance()->DestroyInstance();
	CRenderMgr::GetInstance()->DestroyInstance();
	CPathMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();	
	CTimerMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

void CMainApp::KeyInput(const _float & fTimeDelta)
{
	
}
