#include "stdafx.h"
#include "Crop.h"
#include "CropManager.h"

CCrop::CCrop()
{
}


CCrop::~CCrop()
{
	
}

HRESULT CCrop::Init()
{
	m_tInfo.vPos = { 100.f, 100.f,0.f };
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_strObjectKey = L"Crop";
	m_strStateKey = L"";
	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 4.f };

	CRenderMgr::GetInstance()->AddRenderObect( this, LAYER_ID_2 );

	return S_OK;
}

_int CCrop::Update( const _float & fTimeDelta )
{
	return NO_EVENT;
}

void CCrop::LateUpdate( const _float & fTimeDelta )
{
}

void CCrop::Render()
{
	if ( m_strStateKey == L"")
		return;

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, 1 );

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

void CCrop::SetCropName( const string & strName )
{
	wstring strTemp{ };
	strTemp.assign( strName.begin(), strName.end() );

	m_strStateKey = const_cast< TCHAR * >( strTemp.c_str() );

	m_tCropInfo = CCropManager::GetInstance()->FindCropInfo( strName );
}
