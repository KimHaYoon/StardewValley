#pragma once
#include "Monster.h"
class CBat :
	public CMonster
{
public:
	CBat();
	~CBat();

	// CMonster을(를) 통해 상속됨
	virtual HRESULT  Init() override;
	virtual _int Update( const _float & fTimeDelta ) override;
	virtual void LateUpdate( const _float & fTimeDelta ) override;
	virtual void Render() override;
	virtual void Release() override;
};

