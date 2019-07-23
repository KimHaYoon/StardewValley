#pragma once
class CObj;
class CObjectMgr
{
	_DECLARE_SINGLETON(CObjectMgr)
private:
	CObjectMgr();
	~CObjectMgr();
public:
	void			AddObject(CObj* pObj, OBJECT_ID eID);
	void			Update(const _float& fTimeDelta);
	void			LateUpdate(const _float& fTimeDelta);
	void			Render();
	void			Release();
	void			Release_Scene(OBJECT_ID eID);
public:
	list<CObj*>		&GetPlayer() { return m_listObject[OBJECT_ID_PLAYER]; }
private:
	list<CObj*>		m_listObject[OBJECT_ID_END];
};

