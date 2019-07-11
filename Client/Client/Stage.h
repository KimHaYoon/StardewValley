#pragma once
#include "Scene.h"
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();
public:
	virtual HRESULT Init() override;
	virtual void Update(const _float& fTimeDelta) override;
	virtual void LateUpdate(const _float& fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

