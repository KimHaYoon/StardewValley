#include "stdafx.h"
#include "Equipment.h"


CEquipment::CEquipment()
{
}


CEquipment::~CEquipment()
{
}

HRESULT CEquipment::Init()
{
	m_tInfo.vPos = { 400.f, 300.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	m_strStateKey = L"Kent_Forward";
	m_tFrame = { 0.f, 1.f };
	m_fAngle = 0.f;
	m_bActive = false;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	return S_OK;
}

HRESULT CEquipment::Init(OBJECT_ID eID)
{
	m_tInfo.vPos = { 400.f, 300.f,0.f };
	m_tInfo.vSize = { 1.f, 1.f,0.f };
	m_strStateKey = L"Kent_Forward";
	m_tFrame = { 0.f, 1.f };
	m_fAngle = 0.f;
	m_bActive = false;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	return S_OK;
}

void CEquipment::LateUpdate(const _float& fTimeDelta)
{
	CObj::MoveFrame(fTimeDelta);
}

_int CEquipment::Update(const _float& fTimeDelta)
{
	if (!m_bActive)
		return NO_ERROR;

	m_fAngle += 1.f;
	if (m_fAngle > 360.f)
		m_bActive = false;

	return NO_ERROR;
}

void CEquipment::Render()
{
	if (!m_bActive)
		return;

	D3DXMATRIX matScale, matTrans, matRotate;

	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		0.f);
	D3DXMatrixRotationZ(&matRotate, GetRadian());
	m_tInfo.matWorld = matScale * matRotate * matTrans;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		L"Kent", m_strStateKey, (_int)m_tFrame.fFrame);
	NULL_CHECK_VOID(pTexInfo);

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(0.f, 0.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CEquipment::Release()
{

}