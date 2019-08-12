#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual HRESULT Init()PURE;
	virtual _int Update( const _float & fTimeDelta )PURE;
	virtual void LateUpdate( const _float & fTimeDelta )PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
public:
	virtual HRESULT Init(OBJECT_ID eID);

private:
	MonsterInfo*		m_tMonsterInfo;

};

