#include "stdafx.h"
#include "Vincent.h"


CVincent::CVincent()
{
}


CVincent::~CVincent()
{
	Release();
}

HRESULT CVincent::Init()
{
	m_tInfo.vPos = { 100.f, 100.f,0.f };
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_strObjectKey = L"Vincent";
	m_strStateKey = L"Vincent_Forward";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 4.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;
	if (FAILED(CNPC::LoadPath()))
		return E_FAIL;
	for (auto& iter : m_mapPos)
	{
		m_tInfo.vPos = iter.second.front();
		break;
	}
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	return S_OK;
}

_int CVincent::Update(const _float & fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;
	return NO_EVENT;
}

void CVincent::LateUpdate(const _float & fTimeDelta)
{
	CObj::MoveFrame();
	CNPC::TraceThePath(m_iPathIdx, fTimeDelta);
	ChangeStateKey(m_eCurDir);
}

void CVincent::Render()
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

void CVincent::Release()
{
	for (auto& iter : m_mapPos)
	{
		iter.second.clear();
		iter.second.shrink_to_fit();
	}
	m_mapPos.clear();
}

void CVincent::ChangeStateKey(DIR_ID eID)
{
	if (eID == DIR_ID_FORWORD)
		m_strStateKey = L"Vincent_Forward";
	else if (eID == DIR_ID_BACK)
		m_strStateKey = L"Vincent_Back";
	else if (eID == DIR_ID_LEFT)
		m_strStateKey = L"Vincent_Left";
	else if (eID == DIR_ID_RIGHT)
		m_strStateKey = L"Vincent_Right";
}

HRESULT CVincent::Init(OBJECT_ID eID)
{
	m_tInfo.vPos = { 100.f, 100.f,0.f };
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_strObjectKey = L"Vincent";
	m_strStateKey = L"Vincent_Forward";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 4.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;
	m_eObjID = eID;
	if (FAILED(CNPC::LoadPath()))
		return E_FAIL;
	for (auto& iter : m_mapPos)
	{
		m_tInfo.vPos = iter.second.front();
		break;
	}
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	return S_OK;
}
