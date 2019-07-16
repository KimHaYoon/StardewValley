#pragma once
#include "NPC.h"
class CAbigail :
	public CNPC
{
public:
	CAbigail();
	virtual ~CAbigail();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void ChangeStateKey(DIR_ID eID);
public:
	virtual HRESULT Init(OBJECT_ID eID);

};

