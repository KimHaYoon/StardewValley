#pragma once
#include "Obj.h"
#include "Player.h"

enum ITEM_TYPE {
	ITEM_NONE,
	ITEM_TOOL,
	ITEM_EXPENDABLE,
	ITEM_END
};


enum ITEM_GRADE {
	NOGRADE,
	STONE,
	BRONZE,
	IRON,
	GOLD,
	PURPLE
};

enum ITEM_STATE {
	ITEM_IDLE = 0,
	ITEM_LEFT = 0,
	ITEM_RIGHT,
	ITEM_FORWARD,
	ITEM_BACKWARD,
	ITEM_ICON = 5
};

class CItem :
	public CObj
{
protected:
	_tchar*			m_pName = nullptr;

	ITEM_TYPE		m_eType;
	ITEM_GRADE		m_eGrade;
	ITEM_STATE		m_eState;
	UNITIFNO		m_tInfo2;

	_int			m_nCount;

	_int			m_nIndex;
	_int			m_nIndexLine;

	_float			m_fAngle;

	_bool			m_bSelect = false;
	_bool			m_bActive = false;
public:
	CItem();
	virtual ~CItem();
public:
	virtual HRESULT Init() PURE;
	virtual _int Update(const _float & fTimeDelta) PURE;
	virtual void LateUpdate(const _float & fTimeDelta) PURE;
	virtual void Render();
	virtual void Release() PURE;
	virtual void Active(const _float& x, const _float& y) PURE;

	void SetIndex(_int line, _int index);

	void SelectOn() { m_bSelect = true; }
	void SelectOff() { m_bSelect = false; }
};