#pragma once
class CPathMgr
{
	_DECLARE_SINGLETON(CPathMgr)
private:
	CPathMgr();
	~CPathMgr();
public:
	HRESULT InsertPath(const _tchar* pFilePath, const _tchar* pNPCName,  const _int& iCount = 0);
	void Release();

private:
	vector<NPCInfo*>			m_vecNPCInfo;
};

