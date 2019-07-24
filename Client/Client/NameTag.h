#pragma once
#include "UI.h"
class CNameTag :
	public CUI
{
public:
	CNameTag();
	virtual ~CNameTag();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(_vec3 vPos, _tchar* pName)override;
private:
	_tchar* m_pName = nullptr;
};

