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
public:
	virtual HRESULT Init(OBJECT_ID eID, _int iNum);
private:
	_int m_iMapNum = 0;
};