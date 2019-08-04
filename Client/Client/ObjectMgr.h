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
public:
	void			Release_Group(OBJECT_ID eID);
public:
	list<CObj*>		&GetNPCList() { return m_listObject[OBJECT_ID_NPC]; }
	list<CObj*>		&GetMonsterList() { return m_listObject[OBJECT_ID_MONSTER]; }
	CObj*			&GetPlayer() { return m_listObject[OBJECT_ID_PLAYER].front(); }
	CObj*			GetNPC(const _tchar* pName);
private:
	list<CObj*>		m_listObject[OBJECT_ID_END];
};

