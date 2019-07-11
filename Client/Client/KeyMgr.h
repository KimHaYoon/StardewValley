#pragma once
class CKeyMgr
{
	_DECLARE_SINGLETON(CKeyMgr)
private:
	CKeyMgr();
	~CKeyMgr();
public:
	void Update();
	bool KeyUp(DWORD dwKey);
	bool KeyDown(DWORD dwKey);
	bool KeyPressing(DWORD dwKey);
	bool KeyCombine(DWORD dwFirstKey, DWORD dwSecondKey);

private:
	DWORD m_dwKey=0;
	DWORD m_dwKeyPressed=0;
	DWORD m_dwKeyDown=0;
};

