#include "stdafx.h"
#include "TextBox.h"


CTextBox::CTextBox()
{
}
CTextBox::~CTextBox()
{
	Release();
}

HRESULT CTextBox::Init()
{
	m_tInfo.vSize = { 400.f,300.f,0.f };
	m_strObjectKey = L"UI";
	m_strStateKey = L"TextBox";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);
	return S_OK;
}

_int CTextBox::Update(const _float & fTimeDelta)
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	
	return NO_EVENT;
}

void CTextBox::LateUpdate(const _float & fTimeDelta)
{
	m_fTime += fTimeDelta;
	if (m_fTime >= 0.5f)
	{	
		m_fTime = 0.f;
	}

}

void CTextBox::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, 1);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rt = {0, 0, 800, 600};//{10, 500, 300, 600};

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(), m_vConver[0], -1, &rt, DT_TOP|DT_LEFT, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CTextBox::Release()
{
}

HRESULT CTextBox::Init(OBJECT_ID eID)
{
	m_tInfo.vPos = { 400.f,500.f,0.f };
	m_tInfo.vSize = { 2.f,1.5f,0.f };
	m_strObjectKey = L"UI";
	m_strStateKey = L"TextBox";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };
	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);

	return S_OK;
}

HRESULT CTextBox::AddText(vector<wstring> v)
{
	for (auto& iter : v)
	{
		m_vConver.push_back(iter.c_str());
	}
	return S_OK;
}
