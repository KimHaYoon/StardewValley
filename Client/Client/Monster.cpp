#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

HRESULT CMonster::Init()
{
	return S_OK;
}

_int CMonster::Update( const _float & fTimeDelta )
{
	return NO_ERROR;
}

void CMonster::LateUpdate( const _float & fTimeDelta )
{
}

void CMonster::Render()
{
}

void CMonster::Release()
{
}
