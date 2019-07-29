#pragma once
#include "UI.h"

class CEnergyGauge : public CUI
{
	CObj *m_pEnergy = NULL;
public:
	CEnergyGauge();
	virtual ~CEnergyGauge();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
};

