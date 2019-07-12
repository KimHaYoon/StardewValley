#include "stdafx.h"
#include "NPC.h"


CNPC::CNPC()
{
}


CNPC::~CNPC()
{
}

HRESULT CNPC::LoadPath()
{
	for (auto& iter : CPathMgr::GetInstance()->GetNPCInfo())
	{
		if (iter->szName == m_strObjectKey)
		{
			for (auto& iter1 : iter->mapInfo)
			{
				m_mapPos.insert(iter1);
			}
			break;
		}
	}
	return S_OK;
}

void CNPC::TraceThePath(const _float& fTimeDelta)
{

}

