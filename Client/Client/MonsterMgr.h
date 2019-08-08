#pragma once
class CMonsterMgr
{
	_DECLARE_SINGLETON(CMonsterMgr)
private:
	CMonsterMgr();
	~CMonsterMgr();

public:
	void LoadMonsterInfo();
	MonsterInfo* FindMonsterInfo( string strTag );

private:
	map<string, MonsterInfo*> m_mapMonster;
};

