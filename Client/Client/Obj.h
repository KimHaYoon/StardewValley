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
	virtual	HRESULT Init(const _tchar* pFilePath, OBJECT_ID eID=OBJECT_ID_TERRAIN);
	virtual HRESULT Init(OBJECT_ID eID);
public:
	const UNITIFNO		GetInfo() const { return m_tInfo; }
	OBJECT_ID			GetObjectID() { return m_eObjID; }
protected:
	UNITIFNO		m_tInfo;
	_float			m_fSpeed=0.f;
	FRAME			m_tFrame;
	TCHAR*			m_strObjectKey = L"";
	TCHAR*			m_strStateKey = L"";
protected:
	DIR_ID			m_ePastDIr;
	DIR_ID			m_eCurDir;
	OBJECT_ID		m_eObjID;
protected:
	void			MoveFrame();
	void			MoveFrame(float num);
	void			MoveFrameStop();
};

