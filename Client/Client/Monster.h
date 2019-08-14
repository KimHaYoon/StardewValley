#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual HRESULT Init();
	virtual _int Update( const _float & fTimeDelta );
	virtual void LateUpdate( const _float & fTimeDelta );
	virtual void Render() ;
	virtual void Release() ;
public:
	virtual HRESULT Init(OBJECT_ID eID);
	virtual HRESULT Init( OBJECT_ID eID, TCHAR *  strName );

private:
	MonsterInfo*		m_tMonsterInfo;

};

