#pragma once
#include "Scene.h"
#include <iostream>
using namespace std;
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

class CDongKuTestScene :
	public CScene
{
public:
	CDongKuTestScene();
	virtual ~CDongKuTestScene();
public:
	virtual HRESULT Init() override;
	virtual void Update(const _float& fTimeDelta) override;
	virtual void LateUpdate(const _float& fTimeDelta) override;
	virtual void Render() override;
	virtual void Release() override;
};

