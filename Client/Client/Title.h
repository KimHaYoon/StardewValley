#pragma once
#include "UI.h"
class CTitle :
	public CUI
{
public:
	CTitle();
	virtual ~CTitle();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual HRESULT Init(OBJECT_ID eID);
};

