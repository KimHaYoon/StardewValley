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

// 	list<CObj*> vObj;
// 	CObj* pTemp;
// 	for (int i = 0; i < OBJECT_ID_END; ++i)
// 		for (auto& iter : m_listObject[i])
// 		{
// 			pTemp = iter;
// 			vObj.push_back(pTemp);
// 		}
// 
// 	vObj.sort([](CObj* a, CObj* b)
// 	{
// 		return a->GetLayerID() < b->GetLayerID();
// 	});
// 
// 	for (auto& iter : vObj)
// 	{
// 		iter->Render();
// 		SafeDelete(iter);
// 	}
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
	CRenderMgr::GetInstance()->Release();
}

void CObjectMgr::Release_Scene(OBJECT_ID eID)
{
	for_each(m_listObject[eID].begin(), m_listObject[eID].end(), SafeDelete<CObj*>);
	m_listObject[eID].clear();
	CRenderMgr::GetInstance()->Release();
}
