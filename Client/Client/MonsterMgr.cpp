#include "stdafx.h"
#include "MonsterMgr.h"
#include <fstream>
#include <string>

_IMPLEMENT_SINGLETON(CMonsterMgr)
CMonsterMgr::CMonsterMgr()
{
}

CMonsterMgr::~CMonsterMgr()
{
}

void CMonsterMgr::LoadMonsterInfo()
{
	ifstream in( "../Data/MonsterInfo.txt" );
	
	while ( !in.eof() )
	{
		string strData;
		getline( in, strData );

		int iCount{ };
		auto begin = strData.begin();

		string strTemp;
		string strTag;
		string strItemTag;
		float fItemRate{};
		MonsterInfo* tInfo = new MonsterInfo;
		
		while ( begin != strData.end() )
		{
			if ( *begin == '/' )
			{
				if ( iCount == 0 )
				{
					strTag = strTemp;
				}

				else if ( iCount == 1 )
				{
					tInfo->strImgName = strTemp;
				}

				else if ( iCount == 2 )
				{
					tInfo->iHP = atoi( strTemp.c_str() );
				}

				else if ( iCount == 3 )
				{
					tInfo->iDamage = atoi( strTemp.c_str() );
				}

				else if ( iCount == 4 )
				{
					strItemTag = strTemp;
				}

				else
				{
					fItemRate = (_float)atof( strTemp.c_str() );
				}

				if ( !strItemTag.empty() && fItemRate != 0.f )
				{
					tInfo->mapDropItem.insert( make_pair( strItemTag, fItemRate ) );
				}

				strTemp.clear();
				++iCount;
			}

			else
				strTemp += *begin;
			++begin;
		}

		m_mapMonster.insert( make_pair( strTag, tInfo ) );
	}
	
	in.close();
}

MonsterInfo * CMonsterMgr::FindMonsterInfo( string strTag )
{
	auto iter = m_mapMonster.find( strTag );

	if ( iter == m_mapMonster.end() )
		return NULL;

	return iter->second;
}
