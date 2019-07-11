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
	TCHAR							szName[128];
	map<int, vector<D3DXVECTOR3>>	mapInfo;
}NPCInfo;