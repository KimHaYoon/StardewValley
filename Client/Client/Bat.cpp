#include "stdafx.h"
#include "Bat.h"
#include "MonsterMgr.h"


CBat::CBat()
{
}

CBat::~CBat()
{
}

HRESULT CBat::Init()
{
	m_tInfo.vPos = { 100.f, 100.f,0.f };
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_strObjectKey = L"Bat";
	m_strStateKey = L"Bat_Fly";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 5.f };
	m_eCurDir = DIR_ID_FORWORD;
	m_ePastDIr = m_ePastDIr;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_2);

	return S_OK;
}

_int CBat::Update( const _float & fTimeDelta )
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling( &matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f );
	D3DXMatrixTranslation( &matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f );

	m_tInfo.matWorld = matScale * matTrans;


	return NO_EVENT;
}

void CBat::LateUpdate( const _float & fTimeDelta )
{
}

void CBat::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, ( int )m_tFrame.fFrame );
	NULL_CHECK_VOID( pTexInfo );

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform( &m_tInfo.matWorld );
	CDevice::GetInstance()->GetSprite()->Draw( pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3( fCenterX, fCenterY, 0.f ), nullptr, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
}

void CBat::Release()
{
}
