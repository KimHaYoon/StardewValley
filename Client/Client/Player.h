#pragma once
#include "Obj.h"
class CPlayer : public CObj
{
	_float m_fTime = 0.f;
	_bool m_bIDLE;
public:
	CPlayer();
	~CPlayer();

	virtual HRESULT Init();

	virtual _int Update(const _float& fTimeDelta);
	virtual void LateUpdate(const _float& fTimeDelta);
	virtual void Render();
	virtual void Release();
};

