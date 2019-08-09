#pragma once
#include "Scene.h"
class CBusStop :
	public CScene
{
public:
	CBusStop();
	virtual ~CBusStop();
public:
	virtual HRESULT Init() override;
	virtual void Update(const _float& fTimeDelta) override;
	virtual void LateUpdate(const _float& fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

