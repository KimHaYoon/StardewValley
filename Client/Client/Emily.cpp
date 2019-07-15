#include "stdafx.h"
#include "Emily.h"


CEmily::CEmily()
{
}


CEmily::~CEmily()
{
}

HRESULT CEmily::Init()
{
	m_tInfo.vPos = { 100.f, 100.f,0.f };
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_strObjectKey = L"Emily";
	m_strStateKey = L"Emily_Forward";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 4.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;
	if (FAILED(CNPC::LoadPath()))
		return E_FAIL;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	return S_OK;
}

_int CEmily::Update(const _float & fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;


	return NO_EVENT;
}

void CEmily::LateUpdate(const _float & fTimeDelta)
{
	CObj::MoveFrame();
	CNPC::TraceThePath(1, fTimeDelta);
	ChangeStateKey(m_eCurDir);
}

void CEmily::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, (int)m_tFrame.fFrame);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CEmily::Release()
{
	for (auto& iter : m_mapPos)
	{
		iter.second.clear();
		iter.second.shrink_to_fit();
	}
	m_mapPos.clear();
}

void CEmily::ChangeStateKey(DIR_ID eID)
{
	if (eID == DIR_ID_FORWORD)
		m_strStateKey = L"Emily_Forward";
	else if (eID == DIR_ID_BACK)
		m_strStateKey = L"Emily_Back";
	else if (eID == DIR_ID_LEFT)
		m_strStateKey = L"Emily_Left";
	else if (eID == DIR_ID_RIGHT)
		m_strStateKey = L"Emily_Right";
}
