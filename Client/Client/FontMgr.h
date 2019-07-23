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
public:
	vector<TEXTINFO*>		&GetTEXTInfo() { return m_vText; }
private:
	vector<TEXTINFO*>		m_vText;

};

