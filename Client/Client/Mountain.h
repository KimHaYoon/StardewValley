#pragma once
#include "Scene.h"
class CMountain :
	public CScene
{
public:
	CMountain();
	virtual ~CMountain();
public:
	virtual HRESULT Init() override;
	virtual void Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

