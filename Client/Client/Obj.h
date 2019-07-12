#pragma once
class CObj
{
public:
	CObj();
	~CObj();
public:
	virtual HRESULT Init()PURE;
	virtual _int Update(const _float& fTimeDelta)PURE;
	virtual void LateUpdate(const _float& fTimeDelta)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
public:
	virtual	HRESULT Init(const _tchar* pFilePath);
protected:
	UNITIFNO		m_tInfo;
	_float			m_fSpeed=0.f;
	FRAME			m_tFrame;
	TCHAR*			m_strObjectKey = L"";
	TCHAR*			m_strStateKey = L"";
protected:
	void			MoveFrame();
	void			MoveFrame(float num);
	void			MoveFrameStop();
};

