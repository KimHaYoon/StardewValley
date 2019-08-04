#include "stdafx.h"
#include "Room.h"


#include "Player.h"
#include "MyMap.h"



CRoom::CRoom()
{
}


CRoom::~CRoom()
{
	Release();
}

HRESULT CRoom::Init()
{
	return S_OK;
}

void CRoom::Update(const _float & fTimeDelta)
{
}

void CRoom::LateUpdate(const _float & fTimeDelta)
{
}

void CRoom::Render()
{
}

void CRoom::Release()
{
}
