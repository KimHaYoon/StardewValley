#pragma once
#include "UI.h"

class CClock : public CUI
{
	CObj *m_pClockHand = NULL;
public:
	CClock();
	virtual ~CClock();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
	void RenderFont();
};

