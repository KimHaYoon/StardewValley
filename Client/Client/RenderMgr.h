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
public:
	void			Release();
	void			Release_RenderObj(OBJECT_ID eID);
private:
	vector<CObj*>		m_RenderLst[LAYER_ID_END];
};

