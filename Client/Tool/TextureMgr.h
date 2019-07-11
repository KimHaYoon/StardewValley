#pragma once

class CTexture;
class CTextureMgr
{
	_DECLARE_SINGLETON(CTextureMgr)

public:
	enum TEXTYPE { TEX_SINGLE, TEX_MULTI };

private:
	CTextureMgr();
	~CTextureMgr();

public:
	const TEXINFO* GetTexInfo(
		const TCHAR* pObjKey, const TCHAR* pStateKey = L"", const int& iIndex = 0);

public:
	HRESULT InsertTexture(TEXTYPE eType, const TCHAR* pFilePath,
		const TCHAR* pObjKey, const TCHAR* pStateKey = L"",
		const int& iCount = 0 );
	void Release();

private:
	map<wstring, CTexture*>	m_MapTexture;
};

