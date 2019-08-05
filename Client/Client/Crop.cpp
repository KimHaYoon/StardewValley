#include "stdafx.h"
#include "Crop.h"
#include "CropManager.h"
#include "GameTime.h"

CCrop::CCrop()
{
}


CCrop::~CCrop()
{
}

HRESULT CCrop::Init()
{
	m_tInfo.vPos = { 100.f, 200.f,0.f };
	m_tInfo.vSize = { 3.f,3.f,0.f };

	m_strObjectKey = L"Crop";
	m_strStateKey = L"";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 0.f };


	m_iBaseDate = CGameTime::GetInstance()->GetCurrentDate();
	m_iCurrentDate = m_iBaseDate;
	m_iSubDate = 0;
	m_bHarvest = false;
	CRenderMgr::GetInstance()->AddRenderObect( this, LAYER_ID_2 );

	return S_OK;
}

_int CCrop::Update( const _float & fTimeDelta )
{
	_matrix matTrans, matScale;
	D3DXMatrixScaling( &matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f );
	D3DXMatrixTranslation( &matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f );

	m_tInfo.matWorld = matScale * matTrans;


	m_iCurrentDate = CGameTime::GetInstance()->GetCurrentDate();
	
	if( !m_bHarvest )
		m_iSubDate = ( m_iCurrentDate - m_iBaseDate );

	if ( m_iSubDate == m_tCropInfo->iDate  - 1)
		m_bHarvest = true;


	return NO_EVENT;
}

void CCrop::LateUpdate( const _float & fTimeDelta )
{
	CObj::MoveFrame();
}

void CCrop::Render()
{
	if ( m_strStateKey == L"")
		return;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, m_iSubDate );

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform( &m_tInfo.matWorld );
	CDevice::GetInstance()->GetSprite()->Draw( pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3( fCenterX, fCenterY, 0.f ), nullptr, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
}

void CCrop::Release()
{
}

HRESULT CCrop::Init( OBJECT_ID eID )
{
	m_eObjID = eID;

	return CCrop::Init();
}

void CCrop::SetCropName(const string& strName)
{	
 	m_strTemp.assign( strName.begin(), strName.end() );
 
 	m_strStateKey = const_cast< TCHAR * >( m_strTemp.c_str() );

	m_tCropInfo = CCropManager::GetInstance()->FindCropInfo( strName );	
	m_tFrame = { 0.f, (float)m_tCropInfo->iFrame };
}
