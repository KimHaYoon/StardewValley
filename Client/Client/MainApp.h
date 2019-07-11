#pragma once
class CMainApp
{
public:
	CMainApp();
	~CMainApp();
public:
	HRESULT Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
private:
	void KeyInput(const _float& fTimeDelta);
private:
	CDevice*	m_pDevice;
	CSceneMgr*	m_pSceneMgr;
private:
	_float		m_fTimeDelta=0.f;
};

