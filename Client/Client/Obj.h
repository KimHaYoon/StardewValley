#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual HRESULT Init()PURE;
	virtual _int Update(const _float& fTimeDelta)PURE;
	virtual void LateUpdate(const _float& fTimeDelta)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
public:
	virtual	HRESULT Init(const _tchar* pFilePath, OBJECT_ID eID=OBJECT_ID_TERRAIN);
	virtual HRESULT Init(OBJECT_ID eID);
	virtual HRESULT Init(LAYER_ID eID);
public:
	const UNITIFNO		GetInfo() const { return m_tInfo; }
	OBJECT_ID			GetObjectID() { return m_eObjID; }
	const LAYER_ID			GetLayerID() const { return m_eLayerID; }
protected:
	UNITIFNO		m_tInfo;
	_float			m_fSpeed=0.f;
	FRAME			m_tFrame;
	TCHAR*			m_strObjectKey = L"";
	TCHAR*			m_strStateKey = L"";
protected:
	DIR_ID			m_ePastDIr;
	DIR_ID			m_eCurDir;
protected:
	OBJECT_ID		m_eObjID;
	LAYER_ID		m_eLayerID;
protected:
	void			MoveFrame();
	void			MoveFrame(float num);
	void			MoveFrameStop();
};

