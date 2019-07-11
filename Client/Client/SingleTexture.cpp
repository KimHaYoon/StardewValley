#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	: m_pTexInfo(nullptr)
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

const TEXINFO* CSingleTexture::GetTexInfo(const TCHAR * pStateKey, 
	const int & iIndex)
{
	return m_pTexInfo;
}

HRESULT CSingleTexture::InsertTexture(const TCHAR* pFilePath, 
	const TCHAR* pStateKey /*= L""*/, const int & iCount /*= 0*/)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	// D3DXGetImageInfoFromFile: 파일로부터 이미지 정보를 얻어옴.
	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
	{
		SafeDelete(m_pTexInfo);
		ERR_MSG(pFilePath);
		return E_FAIL;
	}

	// D3DXCreateTextureFromFileEx: LPDIRECT3DTEXTURE9 객체를 생성.
	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(),
		pFilePath, /*생성할 이미지의 경로*/
		m_pTexInfo->tImgInfo.Width, /*이미지 가로 너비*/
		m_pTexInfo->tImgInfo.Height, /*이미지 세로 너비*/
		m_pTexInfo->tImgInfo.MipLevels, /*Mip level*/
		0, /*불러온 이미지의 사용방식, 특별한 경우가 아닌 이상 0*/
		m_pTexInfo->tImgInfo.Format,  /*픽셀 포맷*/
		D3DPOOL_MANAGED, /*불러온 이미지의 메모리를 어디서 관리?*/
		D3DX_DEFAULT, /*이미지 테두리 표현*/
		D3DX_DEFAULT, /*Mip Filter: Mipmap을 이용한 확대 축소 처리*/
		0, /*제거할 색상*/
		nullptr, nullptr, &(m_pTexInfo->pTexture))))
	{
		SafeDelete(m_pTexInfo);
		ERR_MSG(L"SingleTexture Create Failed!");
		return E_FAIL;
	}

	return S_OK;
}

void CSingleTexture::Release()
{
	// 순서 주의
	if (m_pTexInfo->pTexture)
		m_pTexInfo->pTexture->Release();

	SafeDelete(m_pTexInfo);
}
