#pragma once
#include "Obj.h"
class CNPC :
	public CObj
{
public:
	CNPC();
	virtual ~CNPC();
public:
	virtual HRESULT Init() PURE;
	virtual _int Update(const _float & fTimeDelta) PURE;
	virtual void LateUpdate(const _float & fTimeDelta) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

