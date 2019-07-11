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

	// D3DXGetImageInfoFromFile: ���Ϸκ��� �̹��� ������ ����.
	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
	{
		SafeDelete(m_pTexInfo);
		ERR_MSG(pFilePath);
		return E_FAIL;
	}

	// D3DXCreateTextureFromFileEx: LPDIRECT3DTEXTURE9 ��ü�� ����.
	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::GetInstance()->GetDevice(),
		pFilePath, /*������ �̹����� ���*/
		m_pTexInfo->tImgInfo.Width, /*�̹��� ���� �ʺ�*/
		m_pTexInfo->tImgInfo.Height, /*�̹��� ���� �ʺ�*/
		m_pTexInfo->tImgInfo.MipLevels, /*Mip level*/
		0, /*�ҷ��� �̹����� �����, Ư���� ��찡 �ƴ� �̻� 0*/
		m_pTexInfo->tImgInfo.Format,  /*�ȼ� ����*/
		D3DPOOL_MANAGED, /*�ҷ��� �̹����� �޸𸮸� ��� ����?*/
		D3DX_DEFAULT, /*�̹��� �׵θ� ǥ��*/
		D3DX_DEFAULT, /*Mip Filter: Mipmap�� �̿��� Ȯ�� ��� ó��*/
		0, /*������ ����*/
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
	// ���� ����
	if (m_pTexInfo->pTexture)
		m_pTexInfo->pTexture->Release();

	SafeDelete(m_pTexInfo);
}
