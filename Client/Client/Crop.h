#pragma once
#include "Obj.h"
class CCrop : public CObj
{
public:
	CCrop();
	~CCrop();

	// CObj��(��) ���� ��ӵ�
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
	wstring m_strTemp{};
	int			m_iCurrentDate;
	int			m_iBaseDate;
	int			m_iSubDate;
	bool		m_bHarvest;
};

