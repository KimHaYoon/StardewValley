#pragma once
#include "Obj.h"
class CBat :
	public CObj
{
	MonsterInfo* m_tMonsterInfo;

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
	void MoveToPlayer( const D3DXVECTOR3& vPos );
};

