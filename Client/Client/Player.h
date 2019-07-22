#pragma once
#include "Obj.h"

#define WALKSPEED 100.f
#define RUNSPEED 150.f

class CPlayer : public CObj
{
	_float m_fTime = 0.f;
	_bool m_bIDLE;

	_float m_fMoveFrame = 1.f;

	CObj *m_pEquip = NULL;
public:
	CPlayer();
	~CPlayer();

	virtual HRESULT Init();

	virtual _int Update(const _float& fTimeDelta);
	virtual void LateUpdate(const _float& fTimeDelta);
	virtual void Render();
	virtual void Release();
};

