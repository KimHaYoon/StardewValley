#pragma once
class CCropManager
{
	_DECLARE_SINGLETON( CCropManager )
public:
	CCropManager();
	~CCropManager();

	void LoadCropInfo();

private:
	map<string, CropInfo*>		m_mapCrop[SEASON_END];
};

