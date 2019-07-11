#pragma once
class CFrameMgr
{
	_DECLARE_SINGLETON(CFrameMgr)
private:
	CFrameMgr();
	~CFrameMgr();
public:
	void			InitFrame(float framePersec);
	bool			LockFrame();
	void			RenderFrame();

private:
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime;
	LARGE_INTEGER	m_CpuTick;

	float			m_fDeltaTime=0.f;
	float			m_fSpf=0.f;	// sec / frame
	float			m_fSpfTime=0.f;

	TCHAR			m_szFps[MIN_STR];
	int				m_iFps=0;
	float			m_fFpsTime=0.f;
};

