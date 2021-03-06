#include "stdafx.h"
#include "ObjectMgr.h"
#include "Obj.h"

_IMPLEMENT_SINGLETON(CObjectMgr)
CObjectMgr::CObjectMgr()
{
}


CObjectMgr::~CObjectMgr()
{
	Release();
}

void CObjectMgr::AddObject(CObj * pObj, OBJECT_ID eID)
{
	if (nullptr == pObj)
		return;
	m_listObject[eID].push_back(pObj);
}

void CObjectMgr::Update(const _float& fTimeDelta)
{
	for (int i = 0; i < OBJECT_ID_END; ++i)
	{
		auto iter_begin = m_listObject[i].begin();

		for (; iter_begin != m_listObject[i].end();)
		{
			int iEvent = (*iter_begin)->Update(fTimeDelta);

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = m_listObject[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}
}

void CObjectMgr::LateUpdate(const _float& fTimeDelta)
{
	for (int i = 0; i < OBJECT_ID_END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->LateUpdate(fTimeDelta);
	}
}

void CObjectMgr::Render()
{
	for (int i = 0; i < OBJECT_ID_END; ++i)
	{
		for (auto& pObject : m_listObject[i])
			pObject->Render();
	}
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OBJECT_ID_END; ++i)
	{
		for (auto& iter : m_listObject[i])
		{
			SafeDelete(iter);
		}
		m_listObject[i].clear();
	}
	bCheckOfRenderer = true;
}


void CObjectMgr::Release_Group(OBJECT_ID eID)
{
	for_each(m_listObject[eID].begin(), m_listObject[eID].end(), SafeDelete<CObj*>);
	m_listObject[eID].clear();
	bCheckOfRenderer = true;
}

void CObjectMgr::Release_NonePlayer()
{
	for (int i = 0; i < OBJECT_ID_END; ++i)
	{
		if(i==OBJECT_ID_PLAYER)
			continue;
		if (i == OBJECT_ID_UI)
			continue;
		for (auto& iter : m_listObject[i])
		{
			SafeDelete(iter);
		}
		m_listObject[i].clear();
	}
	bCheckOfRenderer = true;
}

CObj* CObjectMgr::GetNPC(const _tchar * pName)
{
	for (auto& iter : m_listObject[OBJECT_ID_NPC])
	{
		if (iter->GetObjectKey() == pName)
		{
			return iter;
		}
	}
	return nullptr;
}
