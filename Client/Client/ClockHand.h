#pragma once
#include "UI.h"

class CClockHand : public CUI
{
	float m_fAngle;
public:
	CClockHand();
	virtual ~CClockHand();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
};

