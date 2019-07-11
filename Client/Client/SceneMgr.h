#pragma once
class CScene;
class CSceneMgr
{
	_DECLARE_SINGLETON(CSceneMgr)
private:
	CSceneMgr();
	~CSceneMgr();
public:
	HRESULT			SceneChange(SCENE_ID eCurScene);
	void			Update(const _float& fTimeDelta);
	void			LateUpdate(const _float& fTimeDelta);
	void			Render();
	void			Release();

private:
	SCENE_ID		m_eCurScene = SCENE_ID_END;
	SCENE_ID		m_ePreScene = SCENE_ID_END;

	CScene*			m_pScene=nullptr;
};

