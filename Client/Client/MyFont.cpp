#include "stdafx.h"
#include "MyFont.h"

_IMPLEMENT_SINGLETON(CMyFont)
CMyFont::CMyFont()
{
}


CMyFont::~CMyFont()
{
	for (auto& iter : m_mapFont)
	{
		iter.second->Release();
	}
	m_mapFont.clear();
}

HRESULT CMyFont::Ready_Font(const _tchar * pFontName, D3DXFONT_DESCW & FontDesc)
{
	LPD3DXFONT		pFont;
	auto& iter_find = m_mapFont.find(pFontName);
	if (iter_find != m_mapFont.end())
		return E_FAIL;


	if (FAILED(D3DXCreateFontIndirect(CDevice::GetInstance()->GetDevice(), &FontDesc, &pFont)))
	{
		ERR_MSG(L"Create Font Failed!");
		return E_FAIL;
	}

	m_mapFont.insert({ pFontName, pFont });
	return S_OK;
}

LPD3DXFONT CMyFont::Get_Font(const _tchar * pFontName)
{
	LPD3DXFONT		pFont;
	pFont = Find_Font(pFontName);
	if (nullptr == pFontName)
		return nullptr;

	return pFont;
}

LPD3DXFONT CMyFont::Find_Font(const _tchar * pFontName)
{
	auto& iter_find = m_mapFont.find(pFontName);
	if (iter_find == m_mapFont.end())
		return nullptr;



	return iter_find->second;
}
