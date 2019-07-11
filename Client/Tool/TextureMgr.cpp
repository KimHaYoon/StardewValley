#include "stdafx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

_IMPLEMENT_SINGLETON(CTextureMgr)

CTextureMgr::CTextureMgr()
{
}


CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXINFO* CTextureMgr::GetTexInfo(
	const TCHAR* pObjKey, const TCHAR * pStateKey, const int & iIndex)
{
	auto& iter_find = m_MapTexture.find(pObjKey);

	if (m_MapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->GetTexInfo(pStateKey, iIndex);
}

HRESULT CTextureMgr::InsertTexture(
	TEXTYPE eType, const TCHAR* pFilePath,
	const TCHAR* pObjKey, const TCHAR* pStateKey, const int & iCount)
{
	auto& iter_find = m_MapTexture.find(pObjKey);

	if (m_MapTexture.end() == iter_find)
	{
		CTexture* pTexture = nullptr;

		switch (eType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;
		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(pFilePath, pStateKey, iCount)))
		{
			SafeDelete(pTexture);
			return E_FAIL;
		}

		m_MapTexture.insert({ pObjKey, pTexture });

		return S_OK;
	}
	else if (eType == TEX_MULTI)
	{
		if (FAILED(m_MapTexture[pObjKey]->InsertTexture(pFilePath, pStateKey, iCount)))
			return E_FAIL;

		return S_OK;
	}	

	return E_FAIL;
}

void CTextureMgr::Release()
{
	for_each(m_MapTexture.begin(), m_MapTexture.end(), 
		[](auto& MyPair)
	{
		SafeDelete(MyPair.second);
	});

	m_MapTexture.clear();
}
