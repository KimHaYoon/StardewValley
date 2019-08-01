#pragma once
class CObj;
class CCollisionMgr
{
	_DECLARE_SINGLETON(CCollisionMgr)
private:
	CCollisionMgr();
	~CCollisionMgr();
public:
	void Collision_Player(list<CObj*>& dstLst, list<CObj*>& srcLst);
	void Collision_NonePlayer(list<CObj*>	& dstLst, list<CObj*>& srcLst);
	void Collision_Monster(list<CObj*>& Lst);
public:
	static bool CheckRect_Player(CObj*& pDst, CObj*& pSrc, float* pMoveX, float* pMoveY);
	static bool CheckRect_NonePlayer(CObj*& pDst, CObj*& pSrc, float* pMoveX, float* pMoveY);

private:
	float m_fCoolTime = 0.f;
};

