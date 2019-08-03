#pragma once
#include "UI.h"

class CInventory : public CUI
{
	_bool			m_bActive = false;
	_bool			m_bInput = false;
	_bool			m_bSelect = false;

	_int			m_nItemIndex;
	_int			m_nItemIndexLine;

	_int			m_nOrginIndex;
	_int			m_nOrginIndexLine;

	_int			m_nSelect;

	CObj			*m_pItem[3][12];

	UNITIFNO		m_tQuickSlot;
	UNITIFNO		m_tSelectSlot;
public:
	CInventory();
	virtual ~CInventory();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);

	void Active() { m_bActive = !m_bActive; }
	bool GetActive() { return m_bActive; }
	void Drag(const _float& x, const _float& y);
	void Click(const _float& x, const _float& y);
	void EndClick();
};

