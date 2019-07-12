#pragma once
#include "Obj.h"
class CCamera :
	public CObj
{
public:
	CCamera();
	virtual ~CCamera();
public:
	virtual HRESULT Init() override;
	virtual _int Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
private:
	void		 Ready_ViewProj();
private:
	_matrix			m_matView;
	_matrix			m_matProj;
};

