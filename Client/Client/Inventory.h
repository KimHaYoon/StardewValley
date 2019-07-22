#pragma once
#include "UI.h"
class CInventory : public CUI
{
	bool m_bActive = false;
public:
	CInventory();
	virtual ~CInventory();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);

	void Active() { m_bActive = !m_bActive; }
};

