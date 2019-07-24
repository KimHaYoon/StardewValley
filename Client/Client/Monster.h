#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	~CMonster();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Init() override = 0;
	virtual _int Update( const _float & fTimeDelta ) override = 0;
	virtual void LateUpdate( const _float & fTimeDelta ) override = 0;
	virtual void Render() override = 0;
	virtual void Release() override = 0;
};

