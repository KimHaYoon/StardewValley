#pragma once
class CPathMgr
{
	_DECLARE_SINGLETON(CPathMgr)
private:
	CPathMgr();
	~CPathMgr();
public:
	HRESULT InsertPath(const _tchar* pFilePath, TCHAR* pNPCName,  const _int& iCount = 0);
	void Release();
public:
	vector<NPCInfo*>		&GetNPCInfo() { return m_vecNPCInfo; }
private:
	vector<NPCInfo*>			m_vecNPCInfo;
};

