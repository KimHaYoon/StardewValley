#include "stdafx.h"
#include "PathMgr.h"

_IMPLEMENT_SINGLETON(CPathMgr)
CPathMgr::CPathMgr()
{
	
}


CPathMgr::~CPathMgr()
{
	Release();
}

HRESULT CPathMgr::InsertPath(const _tchar * pFilePath, TCHAR* pNPCName, const _int & iCount)
{
	TCHAR szFullPath[MAX_STR] = L"";
	NPCInfo* pInfo = new NPCInfo;
	pInfo->szName = pNPCName;
	vector<_vec3> v;
	for (int i = 0; i < iCount; ++i)
	{
		swprintf_s(szFullPath, pFilePath, i);
		{
			HANDLE fFile = nullptr;
			fFile = CreateFile(szFullPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

			DWORD dwByte = 0;
			
			_vec3 vt;
			while (true)
			{
				ReadFile(fFile, &vt, sizeof(_vec3), &dwByte, nullptr);

				if (0 == dwByte)
					break;
				v.push_back(vt);
			}

			CloseHandle(fFile);
		}

		pInfo->mapInfo.insert(make_pair(i, v));
		v.clear();
		v.shrink_to_fit();
	}
	m_vecNPCInfo.push_back(pInfo);
	return S_OK;
}

void CPathMgr::Release()
{
	for (auto& iter : m_vecNPCInfo)
	{
		for (auto& iter1 : iter->mapInfo)
			iter1.second.clear();
		iter->mapInfo.clear();
		SafeDelete(iter);
	}
	m_vecNPCInfo.clear();
	m_vecNPCInfo.shrink_to_fit();
}
