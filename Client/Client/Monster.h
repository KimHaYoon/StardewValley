#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	~CMonster();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Init() override;
	virtual _int Update( const _float & fTimeDelta ) override;
	virtual void LateUpdate( const _float & fTimeDelta ) override;
	virtual void Render() override;
	virtual void Release() override;
};

