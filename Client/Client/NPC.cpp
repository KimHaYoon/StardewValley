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

void CNPC::TraceThePath(const _int& iIdx, const _float& fTimeDelta)
{
	auto& iter_find = m_mapPos.find(iIdx);
	if (iter_find == m_mapPos.end())
		return;

	Check_DIR(iter_find->second, fTimeDelta);

	
}

void CNPC::Check_DIR(vector<_vec3>& vPos, const _float& fTimeDelta)
{
	_vec3 vTemp = vPos[m_iIdx];
	if (!m_bTransCheck)
	{	
		if (m_tInfo.vPos.x > vTemp.x)
			m_eCurDir = DIR_ID_LEFT;
		else if (m_tInfo.vPos.x < vTemp.x)
			m_eCurDir = DIR_ID_RIGHT;
		else if (m_tInfo.vPos.y > vTemp.y)
			m_eCurDir = DIR_ID_BACK;
		else if (m_tInfo.vPos.y < vTemp.y)
			m_eCurDir = DIR_ID_FORWORD;


		m_bTransCheck = true;
	}

	_vec3 vTrans = vTemp - m_tInfo.vPos;
	_float fLength = D3DXVec3Length(&vTrans);
	D3DXVec3Normalize(&vTrans, &vTrans);
	m_tInfo.vPos += vTrans*fTimeDelta*m_fSpeed;

	if (fLength<1.f)
	{
		m_iIdx++;
		m_bTransCheck = false;
	}
}

