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
public:
	_bool			&GetCheckRelease() { return m_bCheckRelease; }
public:
	PASS_ID			GetPass_ID() { return m_ePass_ID; }
	void			SetPass_ID(PASS_ID eID) { m_ePass_ID = eID; }
private:
	SCENE_ID		m_eCurScene = SCENE_ID_END;
	SCENE_ID		m_ePreScene = SCENE_ID_END;
	CScene*			m_pScene=nullptr;
	_bool			m_bCheckRelease = false;
	PASS_ID			m_ePass_ID = PASS_ID_END;
};

