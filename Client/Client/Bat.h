#pragma once
#include "Obj.h"
class CBat :
	public CObj
{
public:
	CBat();
	virtual ~CBat();
public:
	virtual HRESULT  Init() override;
	virtual _int Update( const _float & fTimeDelta ) override;
	virtual void LateUpdate( const _float & fTimeDelta ) override;
	virtual void Render() override;
	virtual void Release() override;
public:
	virtual HRESULT Init(OBJECT_ID eID);

private:
	MonsterInfo* m_tMonsterInfo;
};

