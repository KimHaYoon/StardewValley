#pragma once
#include "Scene.h"
class CHaYoonTestScene :
	public CScene
{
public:
	CHaYoonTestScene();
	virtual ~CHaYoonTestScene();
public:
	virtual HRESULT Init() override;
	virtual void Update(const _float& fTimeDelta) override;
	virtual void LateUpdate(const _float& fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

