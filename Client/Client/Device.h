#pragma once
class CDevice
{
	_DECLARE_SINGLETON(CDevice)
private:
	CDevice();
	~CDevice();
public:
	LPDIRECT3DDEVICE9	GetDevice() { return m_pDevice; }
	LPD3DXSPRITE		GetSprite() { return m_pSprite; }
	LPD3DXFONT			GetFont() { return m_pFont; }
	LPD3DXLINE			GetLine() { return m_pLine; }
public:
	HRESULT				InitDevice();
	void				Render_Begin();
	void				Render_End(HWND hWnd = nullptr);
	void				Release();
private:
	void				SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9			m_p3D=nullptr;
	LPDIRECT3DDEVICE9	m_pDevice=nullptr;
	LPD3DXSPRITE		m_pSprite=nullptr;
	LPD3DXFONT			m_pFont=nullptr;
	LPD3DXLINE			m_pLine=nullptr;
};

