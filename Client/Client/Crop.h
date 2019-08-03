#pragma once
class CCrop 
{
	_DECLARE_SINGLETON( CCrop )

public:
	CCrop();
	~CCrop();

	void LoadCropInfo();

private:
	map<string, CropInfo*>		m_mapCrop[SEASON_END];
};

