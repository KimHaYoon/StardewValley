#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO * CMultiTexture::GetTexInfo(const TCHAR * pStateKey, 
	const int & iIndex)
{
	auto& iter_find = m_MapMulti.find(pStateKey);

	if (m_MapMulti.end() == iter_find)
		return nullptr;

	if (iter_find->second.empty())
		return nullptr;

	return iter_find->second[iIndex];
}

// pFilePath: ..\Texture\Stage\TERRAIN\Tile\Tile%d.png
HRESULT CMultiTexture::InsertTexture(const TCHAR* pFilePath, 
	const TCHAR* pStateKey, const int & iCount)
{
	auto& iter_find = m_MapMulti.find(pStateKey);

	if (m_MapMulti.end() != iter_find)
		return S_OK;

	TCHAR szFullPath[MAX_STR] = L"";

	for (int i = 0; i < iCount; ++i)
	{
		swprintf_s(szFullPath, pFilePath, i);

		TEXINFO* pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		// D3DXGetImageInfoFromFile: 파일로부터 이미지 정보를 얻어옴.
		if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &(pTexInfo->tImgInfo))))
		{
			SafeDelete(pTexInfo);
			ERR_MSG(pFilePath);
			return E_FAIL;
		}

		// D3DXCreateTextureFromFileEx: LPDIRECT3DTEXTURE9 객체를 생성.
		if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(),
			szFullPath, /*생성할 이미지의 경로*/
			pTexInfo->tImgInfo.Width, /*이미지 가로 너비*/
			pTexInfo->tImgInfo.Height, /*이미지 세로 너비*/
			pTexInfo->tImgInfo.MipLevels, /*Mip level*/
			0, /*불러온 이미지의 사용방식, 특별한 경우가 아닌 이상 0*/
			pTexInfo->tImgInfo.Format,  /*픽셀 포맷*/
			D3DPOOL_MANAGED, /*불러온 이미지의 메모리를 어디서 관리?*/
			D3DX_DEFAULT, /*이미지 테두리 표현*/
			D3DX_DEFAULT, /*Mip Filter: Mipmap을 이용한 확대 축소 처리*/
			0, /*제거할 색상*/
			nullptr, nullptr, &(pTexInfo->pTexture))))
		{
			SafeDelete(pTexInfo);
			ERR_MSG(L"MultiTexture Create Failed!");
			return E_FAIL;
		}

		m_MapMulti[pStateKey].push_back(pTexInfo);
	}

	return S_OK;
}

void CMultiTexture::Release()
{
	for_each(m_MapMulti.begin(), m_MapMulti.end(),
		[](auto& MyPair)
	{
		for_each(MyPair.second.begin(), MyPair.second.end(), 
			[](auto& pTexInfo)
		{
			pTexInfo->pTexture->Release();
			SafeDelete(pTexInfo);
		});

		MyPair.second.clear();
		MyPair.second.shrink_to_fit();
	});

	m_MapMulti.clear();
}
