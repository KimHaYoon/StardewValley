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
	virtual HRESULT InsertTexture(const TCHAR* pFilePath, /*�̹��� ���*/
		const TCHAR* pStateKey = L"", /*��Ƽ �ؽ����� ��쿡�� ���*/
		const int& iCount = 0 /*��Ƽ �ؽ����� ��쿡�� ����� �� �̹��� ����*/) PURE;
	virtual void Release() PURE;
};

