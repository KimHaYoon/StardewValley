#pragma once

enum DAY {
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class CGameTime
{
	_DECLARE_SINGLETON(CGameTime)

public:
	CGameTime();
	~CGameTime();

private:
	DAY			m_eDay;

	float		m_fTime;
	int			m_iMin;
	int			m_iHour;

	int			m_iMonth;
	int			m_iDate;

	_int			m_iYear;

	bool		m_bChangeDay;

public:
	void Update(const _float& fDeltaTime);
	void Input();

	int GetCurrentDate() const;
	_int GetCurrentMin() const;
	_int GetCurrentHour() const;
	_int GetCurrentMonth() const;
	_int GetCurrentYear() const;
	DAY GetCurrentDay() const;
};

