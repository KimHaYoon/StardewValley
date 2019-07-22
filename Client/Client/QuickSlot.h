#pragma once
#include "UI.h"
class CQuickSlot : public CUI
{
	CObj* m_pItems[12] = { NULL };
public:
	CQuickSlot();
	virtual ~CQuickSlot();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
};

