#pragma once
#include <atlstr.h>
typedef struct tagFrame
{
	float fFrame;
	float fMax;
}FRAME;

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9	pTexture;
	D3DXIMAGE_INFO		tImgInfo;

}TEXINFO;

typedef struct tagImgPathInfo
{
	wstring wstrObjKey;
	wstring wstrStateKey;
	wstring wstrPath;
	int		iCount;
}IMGPATHINFO;

typedef struct tagUNITINFO
{
	TCHAR		ObjKey[128];
	TCHAR		StateKey[128];
	D3DXMATRIX	matWorld;
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	LAYER_ID	eID;
	int			iMapNum;
	bool		Check=false;
}UNITIFNO;


typedef struct tagTile
{
	TCHAR		ObjKey[128];
	TCHAR		StateKey[128];
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	int			byDrawID;
	BYTE		byOption;
	bool		AlphaCheck=true;
}TILE;


typedef struct tagNPCInfo
{
	TCHAR*							szName;
	map<int, vector<D3DXVECTOR3>>	mapInfo;
}NPCInfo;

typedef struct tagTextInfo
{
	TCHAR*						szName;
	map<int, vector<wstring>>	mapText;
}TEXTINFO;

typedef struct tagMonsterInfo
{
	string strImgName;
	int		iHP;
	int		iDamage;
	map<string, float> mapDropItem;
}MonsterInfo;

typedef struct tagSeedInfo
{
	string			strName;
	list<int>		listPrice;
 }SeedInfo;

typedef struct tagCropInfo
{
	string		strName;
	int			iSellPrice;
	int			iDate;
	bool		bBig;
	int			iCycle;

	tagCropInfo() 
	{
		iSellPrice = 0;
		iDate = 0;
		bBig = false;
		iCycle = 0;
	}

}CropInfo;