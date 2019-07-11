#pragma once
#include "Scene.h"
class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();
public:
	virtual HRESULT Init() override;
	virtual void Update(const _float& fTimeDelta) override;
	virtual void LateUpdate(const _float& fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

