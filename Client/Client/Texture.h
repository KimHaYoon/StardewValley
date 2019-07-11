#pragma once
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();

public:
	virtual const TEXINFO* GetTexInfo(const TCHAR* pStateKey = L"",
		const int& iIndex = 0) PURE;

public:
	virtual HRESULT InsertTexture(const TCHAR* pFilePath, /*이미지 경로*/
		const TCHAR* pStateKey = L"", /*멀티 텍스쳐일 경우에만 사용*/
		const int& iCount = 0 /*멀티 텍스쳐일 경우에만 사용할 총 이미지 개수*/) PURE;
	virtual void Release() PURE;
};

