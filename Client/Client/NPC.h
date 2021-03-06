#pragma once
#include "Obj.h"
#include "NameTag.h"
class CNPC :
	public CObj
{
public:
	CNPC();
	virtual ~CNPC();
public:
	virtual HRESULT Init() PURE;
	virtual _int Update(const _float & fTimeDelta) PURE;
	virtual void LateUpdate(const _float & fTimeDelta) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	virtual void ChangeStateKey(DIR_ID eID)PURE;
public:
	HRESULT		  LoadPath();
	void		  TraceThePath(const _int& iIdx, const _float& fTimeDelta);
	void		  Check_DIR(vector<_vec3>& vPos, const _float& fTimeDelta);
public:
	HRESULT		  LoadText();
protected:
	map<_int, vector<_vec3>>		m_mapPos;	
	map<_int, vector<wstring>>		m_mapTex;
protected:
	_int							m_iIdx = 0;
	_int							m_iVecSize = 0;
	_bool							m_bSizeCheck = false;
	_bool							m_bForwardPath = false;
	_bool							m_bBackPath = false;
	_int							m_iPathIdx = 0;
	_tchar*							m_pNPCName = L"";
protected:
	_vec3							m_vTempPos;
	
};

