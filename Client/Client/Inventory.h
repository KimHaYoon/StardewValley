#pragma once
#include "UI.h"

class CInventory : public CUI
{
	TCHAR*			m_pPlayerName = nullptr;
	TCHAR*			m_pFarmName = nullptr;
	_bool			m_bActive = false;
	_bool			m_bInput = false;
	_bool			m_bSelect = false;

	_int			m_nItemIndex;
	_int			m_nItemIndexLine;

	_int			m_nSelect;
	_int			m_nMoney;
	_int			m_nTotalMoney;

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
	bool GetSelect() { return m_bSelect; }
	void Drag(const _float& x, const _float& y);
	void Click(const _float& x, const _float& y);
	void EndClick(const _float& x, const _float& y);

	void ActiveItem(const _float& x, const _float& y);

	void SetMoney(const _int& money) { m_nMoney = money; }
	_int GetMoney() { return m_nMoney; }
	void IncreaseMoney(const _int& money) {
		m_nMoney += money;
		if (money > 0)
			m_nTotalMoney += money;
	}

	void RenderFont();
};

