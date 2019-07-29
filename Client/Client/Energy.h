#pragma once
#include "UI.h"

class CEnergy : public CUI
{
	_float m_fMaxEnergyScale;
	_float m_fEnergy;
public:
	CEnergy();
	virtual ~CEnergy();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);
};

