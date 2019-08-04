#include "stdafx.h"
#include "CropManager.h"

_IMPLEMENT_SINGLETON( CCropManager )

CCropManager::CCropManager()
{
}


CCropManager::~CCropManager()
{
	for ( int i = 0; i < SEASON_END; ++i )
	{
		auto iter = m_mapCrop[i].begin();
		while ( iter != m_mapCrop[i].end() )
		{
			delete iter->second;
			++iter;
		}
		m_mapCrop[i].clear();
	}
}

void CCropManager::LoadCropInfo()
{
	string strSeason[SEASON_END] = { "Spring", "Summer", "Fall", "Winter" };
	for ( int i = 0; i < SEASON_END; ++i )
	{
		string strFilename = "../Data/Crop/";
		strFilename += strSeason[i];
		strFilename += ".txt";
		ifstream in( strFilename );
		if ( !in )
			continue;

		while ( !in.eof() )
		{
			string strData;
			getline( in, strData );

			int iCount{ };
			auto begin = strData.begin();

			string strTemp;
			string strTag;
			CropInfo* tInfo = new CropInfo;

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
						tInfo->strName = strTemp;
					}

					else if ( iCount == 2 )
					{
						tInfo->iSellPrice = atoi( strTemp.c_str() );
					}

					else if ( iCount == 3 )
					{
						tInfo->iDate = atoi( strTemp.c_str() );
					}

					else if ( iCount == 4 )
					{
						if ( strTemp == "X" )
							tInfo->bBig = false;
						else
							tInfo->bBig = true;
					}

					else
					{
						tInfo->iCycle = atoi( strTemp.c_str() );
					}

					strTemp.clear();
					++iCount;
				}

				else
					strTemp += *begin;
				++begin;
			}

			m_mapCrop[i].insert( make_pair( tInfo->strName, tInfo ) );
		}

		in.close();
	}

	int a = 0;
}
