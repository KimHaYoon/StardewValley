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
public:
	virtual HRESULT Init(OBJECT_ID eID);
public:
	HRESULT	AddText(vector<wstring> v);
private:
	_tchar*			m_pConver = nullptr;
	vector<const _tchar*>	m_vConver;
	vector<_tchar*> m_vTemp;
private:
	_float			m_fTime;
};

