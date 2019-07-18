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

		// D3DXGetImageInfoFromFile: ���Ϸκ��� �̹��� ������ ����.
		if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &(pTexInfo->tImgInfo))))
		{
			SafeDelete(pTexInfo);
			ERR_MSG(pFilePath);
			return E_FAIL;
		}

		// D3DXCreateTextureFromFileEx: LPDIRECT3DTEXTURE9 ��ü�� ����.
		if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(),
			szFullPath, /*������ �̹����� ���*/
			pTexInfo->tImgInfo.Width, /*�̹��� ���� �ʺ�*/
			pTexInfo->tImgInfo.Height, /*�̹��� ���� �ʺ�*/
			pTexInfo->tImgInfo.MipLevels, /*Mip level*/
			0, /*�ҷ��� �̹����� �����, Ư���� ��찡 �ƴ� �̻� 0*/
			pTexInfo->tImgInfo.Format,  /*�ȼ� ����*/
			D3DPOOL_MANAGED, /*�ҷ��� �̹����� �޸𸮸� ��� ����?*/
			D3DX_DEFAULT, /*�̹��� �׵θ� ǥ��*/
			D3DX_DEFAULT, /*Mip Filter: Mipmap�� �̿��� Ȯ�� ��� ó��*/
			0, /*������ ����*/
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
	for (auto& iter : m_MapMulti)
	{
		for (auto& iter1 : iter.second)
		{
			iter1->pTexture->Release();
			SafeDelete(iter1);
		}
		iter.second.clear();
		iter.second.shrink_to_fit();
	}

	m_MapMulti.clear();
}
