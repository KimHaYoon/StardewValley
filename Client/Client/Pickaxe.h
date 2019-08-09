#pragma once
#include "Item.h"

class CPickaxe : public CItem
{
public:
	CPickaxe();
	virtual ~CPickaxe();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render();
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
	virtual void Active(const _float& x, const _float& y) {}
};

