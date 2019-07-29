#pragma once
#include "Item.h"

class CAxe : public CItem
{
public:
	CAxe();
	virtual ~CAxe();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render();
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
};

