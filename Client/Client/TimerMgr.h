#pragma once
class CTimerMgr
{
	_DECLARE_SINGLETON(CTimerMgr)
private:
	CTimerMgr();
	~CTimerMgr();
public:
	float			GetDeltaTime() { return m_fDeltaTime; }

public:
	void			InitTime();
	void			UpdateTime();

private:
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime;
	LARGE_INTEGER	m_CpuTick;

	float			m_fDeltaTime=0.f;
};

