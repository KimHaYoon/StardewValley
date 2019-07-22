#pragma once
class CFontMgr
{
	_DECLARE_SINGLETON(CFontMgr)
private:
	CFontMgr();
	~CFontMgr();
public:
	HRESULT					LoadData(const _tchar* pFilePath, const _int& iIdx, _tchar* NPCName);
	void					Release();
private:
	vector<TEXTINFO*>		m_vText;

};

