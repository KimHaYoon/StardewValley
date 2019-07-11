#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual HRESULT Init() PURE;
	virtual void Update(const _float& fTimeDelta) PURE;
	virtual void LateUpdate(const _float& fTimeDelta) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

