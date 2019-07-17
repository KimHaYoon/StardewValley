#include "stdafx.h"
#include "FontMgr.h"

_IMPLEMENT_SINGLETON(CFontMgr)
CFontMgr::CFontMgr()
{
}


CFontMgr::~CFontMgr()
{
	Release();
}

HRESULT CFontMgr::LoadData(const _tchar* pFilePath, const _int& iIdx, _tchar* NPCName)
{
	
	//wstring -> string
	//str = CT2CA(wstr.c_str());

	//string -> wstring
	//wstr = CA2CT(str.c_str());
	
	for (int i = 0; i < iIdx; ++i)
	{
		TCHAR szFullPath[MAX_STR] = L"";
		swprintf_s(szFullPath, pFilePath, i);

		wfstream File(szFullPath);
		if (File.fail() == TRUE)
			return E_FAIL;
		wstring wtemp;
		string strTemp;
		TEXTINFO* pinfo = new TEXTINFO;
		pinfo->szName = NPCName;
		_int	iCount = 0;
	
		for(;getline(File, wtemp);)
		{			
			vector<wstring>	vTemp;
			vTemp.push_back(wtemp);
			pinfo->mapText.insert(make_pair(iCount, vTemp));	
			iCount++;
		}

		m_vText.push_back(pinfo);
		File.close();
	}
	
	return S_OK;
}

void CFontMgr::Release()
{
	for (auto& iter : m_vText)
	{
		for (auto& iter1 : iter->mapText)
		{
			iter1.second.clear();
			iter1.second.shrink_to_fit();
		}
		SafeDelete(iter);
	}
	m_vText.clear();
}
