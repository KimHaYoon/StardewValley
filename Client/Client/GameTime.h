#pragma once
class CGameTime
{
public:
	CGameTime();
	~CGameTime();

private:
	float		m_fTime;
	int			m_iMin;
	int			m_iHour;
	
	int			m_iMonth;
	int			m_iDate;

	bool		m_bChangeDay;

public:
	void Update( const _float& fDeltaTime );
	void Input();
};

