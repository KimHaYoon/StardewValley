#pragma once
#include "Texture.h"
class CMultiTexture :
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();

public:
	// CTexture을(를) 통해 상속됨
	virtual const TEXINFO * GetTexInfo(const TCHAR* pStateKey = L"", 
		const int & iIndex = 0) override;
	virtual HRESULT InsertTexture(const TCHAR* pFilePath, 
		const TCHAR * pStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	map<wstring, vector<TEXINFO*>>	m_MapMulti;
};

