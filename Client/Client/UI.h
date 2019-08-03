#pragma once
#include "Obj.h"

enum UISPRITE {
	QUICKSLOT,
	SELECTSLOT,
	CLOCKHANDLE,
	INFOCLOCK,
	ENERGY,
	GAUGE,
	END
};

class CUI :
	public CObj
{
public:
	CUI();
	virtual ~CUI();
public:
	virtual HRESULT Init() PURE;
	virtual _int Update(const _float & fTimeDelta) PURE;
	virtual void LateUpdate(const _float & fTimeDelta) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual HRESULT Init(OBJECT_ID eID);
protected:
	_int		m_iNumOfTitle = 0;
};

