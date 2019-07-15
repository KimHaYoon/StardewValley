#pragma once
#include "NPC.h"
class CMorris :
	public CNPC
{
public:
	CMorris();
	virtual ~CMorris();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void ChangeStateKey(DIR_ID eID) override;
};

