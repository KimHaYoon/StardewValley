#pragma once
#include "UI.h"
class CTextBox :
	public CUI
{
public:
	CTextBox();
	virtual ~CTextBox();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

