#pragma once
#include "Item.h"

class CHoe : public CItem
{
public:
	CHoe();
	virtual ~CHoe();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render();
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);

	virtual void Active(const _float& x, const _float& y);
};

