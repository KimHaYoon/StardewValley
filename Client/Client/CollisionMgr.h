#pragma once
class CObj;
class CCollisionMgr
{
	_DECLARE_SINGLETON(CCollisionMgr)
private:
	CCollisionMgr();
	~CCollisionMgr();
public:
	void CollisionPlayer(list<CObj*>& dstLst, list<CObj*>& srcLst);
	void CollisionRects(list<CObj*>	& dstLst, list<CObj*>& srcLst);
	void CollisionMonster(list<CObj*>& Lst);
public:
	static bool CheckRect(CObj*& pDst, CObj*& pSrc, float* pMoveX, float* pMoveY);
	static bool CheckRects(CObj*& pDst, CObj*& pSrc, float* pMoveX, float* pMoveY, int num);

private:
	float m_fCoolTime = 0.f;
};

