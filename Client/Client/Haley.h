#pragma once
#include "NPC.h"
class CHaley :
	public CNPC
{
public:
	CHaley();
	virtual ~CHaley();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void ChangeStateKey(DIR_ID eID) override;
};
