#pragma once
#include "Obj.h"

class CEquipment : public CObj
{
	float m_fAngle;

	bool m_bActive;
public:
	CEquipment();
	virtual ~CEquipment();

	virtual HRESULT Init();
	virtual HRESULT Init(OBJECT_ID eID);

	virtual _int Update(const _float& fTimeDelta);
	virtual void LateUpdate(const _float& fTimeDelta);
	virtual void Render();
	virtual void Release();

	float GetRadian() { return m_fAngle / 180.f * 3.141592f; }
};

