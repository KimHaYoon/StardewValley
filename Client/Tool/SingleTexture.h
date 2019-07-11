#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	virtual const TEXINFO* GetTexInfo(const TCHAR* pStateKey = L"",
		const int& iIndex = 0) override;

public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT InsertTexture(const TCHAR * pFilePath, 
		const TCHAR * pStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	TEXINFO*	m_pTexInfo;

};

