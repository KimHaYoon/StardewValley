#pragma once
class CMyFont
{
	_DECLARE_SINGLETON(CMyFont)
private:
	CMyFont();
	~CMyFont();
public:
	HRESULT		Ready_Font(const _tchar* pFontName, D3DXFONT_DESCW& FontDesc);
	HRESULT		Ready_Font(const _tchar* pFontName, const _uint& iHeight, const _uint& iWidth, const _tchar* Font);
	LPD3DXFONT		Get_Font(const _tchar* pFontName);
private:
	LPD3DXFONT	Find_Font(const _tchar* pFontName);

private:
	map<const _tchar*, LPD3DXFONT>		m_mapFont;
};

