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
	if (!m_bSizeCheck)
	{
		m_iVecSize = vPos.size() - 1;
		m_bSizeCheck = true;
	}
	_vec3 vTemp = vPos[m_iIdx];

	_vec3 vTrans = vTemp - m_tInfo.vPos;
	_float fLength = D3DXVec3Length(&vTrans);
	D3DXVec3Normalize(&vTrans, &vTrans);

	m_vTempPos = m_tInfo.vPos;
	m_tInfo.vPos += vTrans*fTimeDelta*m_fSpeed;
	if (m_iIdx > 0.f)
	{
		if (m_bBackPath)
		{

			if (vPos[m_iIdx].x > vPos[m_iIdx + 1].x)
				m_eCurDir = DIR_ID_RIGHT;
			if (vPos[m_iIdx].x < vPos[m_iIdx + 1].x)
				m_eCurDir = DIR_ID_LEFT;
			if (vPos[m_iIdx].y > vPos[m_iIdx + 1].y)
				m_eCurDir = DIR_ID_FORWORD;
			if (vPos[m_iIdx].y < vPos[m_iIdx + 1].y)
				m_eCurDir = DIR_ID_BACK;
		}
		else if (m_bForwardPath)
		{
			if (vPos[m_iIdx].x > vPos[m_iIdx - 1].x)
				m_eCurDir = DIR_ID_RIGHT;
			if (vPos[m_iIdx].x < vPos[m_iIdx - 1].x)
				m_eCurDir = DIR_ID_LEFT;
			if (vPos[m_iIdx].y > vPos[m_iIdx - 1].y)
				m_eCurDir = DIR_ID_FORWORD;
			if (vPos[m_iIdx].y < vPos[m_iIdx - 1].y)
				m_eCurDir = DIR_ID_BACK;
		}
	}

	if (fLength < 1.f)
	{
		if (m_iIdx >= m_iVecSize)
		{
			m_bBackPath = true;
			m_bForwardPath = false;
		}
		else if (m_iIdx <= 0)
		{
			m_bBackPath = false;
			m_bForwardPath = true;
		}
		if (m_bBackPath)
			--m_iIdx;
		else if (m_bForwardPath)
			m_iIdx++;
	}

}

