#pragma once
class CRenderMgr
{
_DECLARE_SINGLETON(CRenderMgr)
private:
	CRenderMgr();
	~CRenderMgr();
public:
	HRESULT			AddRenderObect(CObj* pObj, LAYER_ID eID);
public:
	void			RenderGroup();
	void			Render_Layer_1();
	void			Render_Layer_2();
	void			Render_Layer_3();
	void			Render_Layer_4();
	void			Render_Layer_5();
	void			Render_Layer_6();
public:
	void			Update_Renderer();
public:
	void			Release();
private:
	vector<CObj*>		m_RenderLst[LAYER_ID_END];
};

