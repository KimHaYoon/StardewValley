#include "stdafx.h"
#include "RenderMgr.h"
#include "Obj.h"

_IMPLEMENT_SINGLETON(CRenderMgr)
CRenderMgr::CRenderMgr()
{
}


CRenderMgr::~CRenderMgr()
{
	Release();
}

HRESULT CRenderMgr::AddRenderObect(CObj * pObj, LAYER_ID eID)
{
	if (pObj == nullptr)
		return E_FAIL;
	m_RenderLst[eID].push_back(pObj);
	return S_OK;
}

void CRenderMgr::RenderGroup()
{
	Render_Layer_1();
	Render_Layer_2();
	Render_Layer_3();
	Render_Layer_4();
	Render_Layer_5();
	Render_Layer_6();
}

void CRenderMgr::Render_Layer_1()
{
	for (auto& iter : m_RenderLst[LAYER_ID_1])
		iter->Render();
}

void CRenderMgr::Render_Layer_2()
{
	for (auto& iter : m_RenderLst[LAYER_ID_2])
		iter->Render();
}

void CRenderMgr::Render_Layer_3()
{
	for (auto& iter : m_RenderLst[LAYER_ID_3])
		iter->Render();
}

void CRenderMgr::Render_Layer_4()
{
	for (auto& iter : m_RenderLst[LAYER_ID_4])
		iter->Render();
}

void CRenderMgr::Render_Layer_5()
{
	for (auto& iter : m_RenderLst[LAYER_ID_5])
		iter->Render();
}

void CRenderMgr::Render_Layer_6()
{
	for (auto& iter : m_RenderLst[LAYER_ID_6])
		iter->Render();	
}
void CRenderMgr::Update_Renderer()
{
	if (bCheckOfRenderer)
	{
		for (int i = 0; i < LAYER_ID_END; ++i)
		{
			auto& iter = m_RenderLst[i].begin();
			for (; iter != m_RenderLst[i].end(); )
			{
				if (iter[0]->GetCheckNum() != 100)
				{
					iter = m_RenderLst[i].erase(iter);
				}
				else
					++iter;
			}
		}

		bCheckOfRenderer = false;
	}
}
void CRenderMgr::Release()
{
	for (int i = 0; i < LAYER_ID_END; ++i)
	{
		auto& iter = m_RenderLst[i].begin();
		for (; iter != m_RenderLst[i].end(); )
		{
			if (iter[0]->GetCheckNum() != 100)
			{
				iter = m_RenderLst[i].erase(iter);
			}
			else
				++iter;
		}
	}
}


