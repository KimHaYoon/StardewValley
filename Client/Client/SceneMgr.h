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
	void			SetPass_ID(PASS_ID eID, SCENE_ID eNextSceneID, SCENE_ID ePreSceneID);
	void			SetTileNum(_int iFrontTileNum, _int iBackTileNum);
public:
	SCENE_ID		&GetCurScene() { return m_eCurScene; }
	SCENE_ID		&GetNextScene() { return m_eNextScene; }
	SCENE_ID		&GetPreScene() { return m_ePreScene; }
public:
	_int			&GetBackTileNum() { return m_iBackTileNum; }
	_int			&GetFrontTileNum() { return m_iFrontTileNum; }
private:
	SCENE_ID		m_eCurScene = SCENE_ID_END;
	SCENE_ID		m_ePreScene = SCENE_ID_END;
	SCENE_ID		m_eNextScene = SCENE_ID_END;
	SCENE_ID		m_eTempScene = SCENE_ID_END;
private:
	_int			m_iBackTileNum = 0;
	_int			m_iFrontTileNum = 0;
private:
	CScene*			m_pScene=nullptr;
	_bool			m_bCheckRelease = false;
	PASS_ID			m_ePass_ID = PASS_ID_END;
};

