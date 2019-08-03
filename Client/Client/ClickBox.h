#pragma once
#include "UI.h"
class CClickBox :
	public CUI
{
public:
	CClickBox();
	virtual ~CClickBox();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual HRESULT Init(OBJECT_ID eID, _int iNum);
private:
	void CheckClick();
private:
	_int m_iBtnIdx = 0;
};

