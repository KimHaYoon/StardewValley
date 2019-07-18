#pragma once
#include "NPC.h"
class CCaroline :
	public CNPC
{
public:
	CCaroline();
	virtual ~CCaroline();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void ChangeStateKey(DIR_ID eID) override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
	virtual HRESULT Init(LAYER_ID eID);
};

