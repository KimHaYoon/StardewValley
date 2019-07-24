#pragma once
class CTextBox;
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
	virtual HRESULT Init(_vec3 vPos, _tchar* pName);
public:
	const UNITIFNO		GetInfo() const { return m_tInfo; }
	OBJECT_ID			GetObjectID() { return m_eObjID; }
	const LAYER_ID		GetLayerID() const { return m_eLayerID; }\
public:
	void				SetPos(float x, float y) { m_tInfo.vPos.x = x, m_tInfo.vPos.y = y; }
public:
	_vec3				GetCollSize() { return m_ObjCollSize; }
public:
	TCHAR*			GetObjectKey() { return m_strObjectKey; }
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
	CObj*		m_pTextBox = nullptr;
protected:
	_vec3				m_ObjCollSize;
protected:
	void			MoveFrame();
	void			MoveFrame(float num);
	void			MoveFrameStop();
};

