#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "ScrollMgr.h"
_IMPLEMENT_SINGLETON(CCollisionMgr)
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Player(list<CObj*>& dstLst, list<CObj*>& srcLst)
{
	_vec3 vScroll = CScrollMgr::GetScroll();

	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect_Player(pDst, pSrc, &fMoveX, &fMoveY))
			{

				if (fMoveX > fMoveY)
				{
					if (pDst->GetInfo().vPos.y - vScroll.y >= pSrc->GetInfo().vPos.y)
						fMoveY *= -1.f;

					CScrollMgr::SetScroll(_vec3{ fMoveX*0.01f, fMoveY, 0.f });
				}
				else
				{
					if (pDst->GetInfo().vPos.x - vScroll.x >= pSrc->GetInfo().vPos.x)
						fMoveX *= -1.f;

					CScrollMgr::SetScroll(_vec3{ fMoveX , fMoveY*0.01f, 0.f });
				}
			}
		}
	}
}

void CCollisionMgr::Collision_NonePlayer(list<CObj*>& dstLst, list<CObj*>& srcLst)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect_NonePlayer(pDst, pSrc, &fMoveX, &fMoveY))
			{
				if (fMoveX > fMoveY)
				{
					if (pDst->GetInfo().vPos.y >= pSrc->GetInfo().vPos.y)
						fMoveY *= -1.f;

					pSrc->SetPos(pSrc->GetInfo().vPos.x, pSrc->GetInfo().vPos.y + fMoveY*0.1f);
				}
				else
				{
					if (pDst->GetInfo().vPos.x >= pSrc->GetInfo().vPos.x)
						fMoveX *= -1.f;

					pSrc->SetPos(pSrc->GetInfo().vPos.x + fMoveX*0.1f, pSrc->GetInfo().vPos.y);

				}
			}
		}
	}
}

void CCollisionMgr::Collision_Monster(list<CObj*>& Lst)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	auto& iter = Lst.begin();
	auto& iter1 = Lst.begin();

	for (; iter != Lst.end(); iter++)
	{
		for (; iter1 != Lst.end(); iter1++)
		{
			if (iter == iter1)
				continue;

			if (CheckRect_NonePlayer((*iter1), (*iter), &fMoveX, &fMoveY))
			{
				if (fMoveX > fMoveY)
				{
					if ((*iter1)->GetInfo().vPos.y >= (*iter)->GetInfo().vPos.y)
						fMoveY *= -1.f;

					(*iter)->SetPos((*iter)->GetInfo().vPos.x, (*iter)->GetInfo().vPos.y + fMoveY);
				}
				else
				{
					if ((*iter1)->GetInfo().vPos.x >= (*iter)->GetInfo().vPos.x)
						fMoveX *= -1.f;

					(*iter)->SetPos((*iter)->GetInfo().vPos.x + fMoveX, (*iter)->GetInfo().vPos.y);
				}
			}
		}
	}
}

bool CCollisionMgr::CheckRect_Player(CObj *& pDst, CObj *& pSrc, float * pMoveX, float * pMoveY)
{
	D3DXVECTOR3 vScroll = CScrollMgr::GetScroll();
	float fSumRadX = (pDst->GetCollSize().x + pSrc->GetCollSize().x)*0.5f;
	float fSumRadY = (pDst->GetCollSize().y + pSrc->GetCollSize().y)* 0.5f;


	float fDistX = fabs(pDst->GetInfo().vPos.x - pSrc->GetInfo().vPos.x - vScroll.x);
	float fDistY = fabs(pDst->GetInfo().vPos.y - pSrc->GetInfo().vPos.y - vScroll.y);


	if (fSumRadX >= fDistX && fSumRadY >= fDistY)
	{
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}
	return false;
}

bool CCollisionMgr::CheckRect_NonePlayer(CObj *& pDst, CObj *& pSrc, float * pMoveX, float * pMoveY)
{
	float fSumRadX = (pDst->GetCollSize().x + pSrc->GetCollSize().x)* 0.5f;
	float fSumRadY = (pDst->GetCollSize().y + pSrc->GetCollSize().y)* 0.5f;


	float fDistX = fabs(pDst->GetInfo().vPos.x - pSrc->GetInfo().vPos.x);
	float fDistY = fabs(pDst->GetInfo().vPos.y - pSrc->GetInfo().vPos.y);


	if (fSumRadX >= fDistX && fSumRadY >= fDistY)
	{
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}

	return false;
}
