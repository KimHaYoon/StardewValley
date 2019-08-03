#pragma once
#include "Obj.h"
class CCrop :
	public CObj
{
public:
	CCrop();
	~CCrop();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Init() override PURE;
	virtual _int Update( const _float & fTimeDelta ) override PURE;
	virtual void LateUpdate( const _float & fTimeDelta ) override PURE;
	virtual void Render() override PURE;
	virtual void Release() override PURE;
};

