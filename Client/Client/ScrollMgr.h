#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:
	static D3DXVECTOR3 &GetScroll() { return m_vScroll; }
	static D3DXVECTOR3 &GetScroll_Menu() { return m_vScroll_Menu; }
public:
	static void SetScroll(const D3DXVECTOR3& vScroll)
	{
		m_vScroll += vScroll;
	}

	static void SetScrolling(const D3DXVECTOR3& vScroll)
	{
		m_vScroll = vScroll;
	}

	static void SetScrolling_Menu(const D3DXVECTOR3& vScroll)
	{
		m_vScroll_Menu += vScroll;
	}


private:
	static D3DXVECTOR3 m_vScroll;
	static D3DXVECTOR3 m_vScroll_Menu;
	static float Ran;

};

