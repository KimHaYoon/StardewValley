#include "stdafx.h"
#include "BusStop.h"


CBusStop::CBusStop()
{
}


CBusStop::~CBusStop()
{
}

HRESULT CBusStop::Init()
{
	CObjectMgr::GetInstance()->Release_NonePlayer();
	CRenderMgr::GetInstance()->Update_Renderer();

	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_FRONT)
	{
		CScrollMgr::SetScrolling(_vec3{ 56.f, -24.f,0.f });
	}
	if (CSceneMgr::GetInstance()->GetPass_ID() == PASS_ID_BACK)
	{
		if (CSceneMgr::GetInstance()->GetBackTileNum() == 1)
		{
			// 전에 있던 scene중에서 밟은 BackTileNum을 가져옴
		}
	}

	return S_OK;
}

void CBusStop::Update(const _float & fTimeDelta)
{
}

void CBusStop::LateUpdate(const _float & fTimeDelta)
{
}

void CBusStop::Render()
{
}

void CBusStop::Release()
{
}
