#pragma once
#include "Obj.h"

#define WALKSPEED 100.f
#define RUNSPEED 150.f

class CPlayer : public CObj
{
	D3DXVECTOR3			m_vCursorPos;
	_float				m_fTime = 0.f;
	_bool				m_bIDLE;
	_bool				m_bDrag;
	_bool				m_bPause;

	_float				m_fMoveFrame = 1.f;

	CObj				*m_pEquip = NULL;

	CObj				*m_pInven = NULL;

	CObj				*m_pClock = NULL;

	CObj				*m_pEnergyGauge = NULL;

	CObj				*m_pCursor = NULL;

public:
	CPlayer();
	virtual ~CPlayer();

	virtual HRESULT Init();

	virtual _int Update(const _float& fTimeDelta);
	virtual void LateUpdate(const _float& fTimeDelta);
	virtual void Render();
	virtual void Release();
public:
	virtual HRESULT Init(OBJECT_ID eID);

	bool GetInventoryState();

	CObj* &GetInven() { return m_pInven; }
	_int GetMoney() const;

	void Drag(const POINT& pt);
	void Click(const POINT& pt);
	void EndClick(const POINT& pt);

	void ActiveItem(const _float& x, const _float& y);
	void SetDir(const _int& eDir);
	TCHAR* GetObjectKey() const { return m_strObjectKey; }
	TCHAR* GetStateKey() const { return m_strStateKey; }
};

