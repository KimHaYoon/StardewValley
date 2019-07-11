#pragma once
#include "Obj.h"

class CMyMap :public CObj 
{
public:
	CMyMap();
	~CMyMap();
public:
	virtual HRESULT Init();
	virtual _int Update(const _float& fTimeDelta);
	virtual void LateUpdate(const _float& fTimeDelta);
	virtual void Render();
	virtual void Release();
private:
	_int m_iMapNum = 0;
};