#pragma once
#include "Obj.h"

enum ITEM_TYPE {
	ITEM_NONE,
	ITEM_TOOL,
	ITEM_EXPENDABLE,
	ITEM_END
};

class CItem :
	public CObj
{
protected:
	_tchar* m_pName = nullptr;

	ITEM_TYPE		m_eType;
	UNITIFNO		m_tInfo2;

	_int			m_nCount;

	_int			m_nIndex;
	_int			m_nIndexLine;

	_bool			m_bSelect = false;
public:
	CItem();
	virtual ~CItem();
public:
	virtual HRESULT Init() PURE;
	virtual _int Update(const _float & fTimeDelta) PURE;
	virtual void LateUpdate(const _float & fTimeDelta) PURE;
	virtual void Render();
	virtual void Release() PURE;

	void SetIndex(_int line, _int index);

	void SelectOn() { m_bSelect = true; }
	void SelectOff() { m_bSelect = false; }
};