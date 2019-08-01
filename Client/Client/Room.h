#pragma once
#include "Scene.h"
class CRoom :
	public CScene
{
public:
	CRoom();
	virtual ~CRoom();
public:
	virtual HRESULT Init() override;
	virtual void Update(const _float & fTimeDelta) override;
	virtual void LateUpdate(const _float & fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

