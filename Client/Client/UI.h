#pragma once
#include "Obj.h"

enum UISPRITE {
	QUICKSLOT,
	SELECTSLOT,
	CLOCKHANDLE,
	INFOCLOCK,
	ENERGY,
	GAUGE,
	NONE,
	ITEMTAB,
	CHARACTERTAB,
	TAB0,
	MAPTAB,
	TOOLTAB,
	TAB1,
	UNKNOWN,
	CANCEL,
	INVENTORY,
	TRASH,
	BACKGROUND,
	LABEL,
	TUTORIAL,
	CURSOR,
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
public:
	_int		GetIdxofTitle() { return m_iNumOfTitle; }
protected:
	_int		m_iNumOfTitle = 0;
};

