#pragma once
#include "Obj.h"
class CCrop : public CObj
{
public:
	CCrop();
	~CCrop();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Init() override;
	virtual _int Update( const _float & fTimeDelta ) override;
	virtual void LateUpdate( const _float & fTimeDelta ) override;
	virtual void Render() override;
	virtual void Release() override;
	virtual HRESULT Init( OBJECT_ID eID );

public:
	void SetCropName(const string& strName);

private:
	CropInfo* m_tCropInfo;
};

