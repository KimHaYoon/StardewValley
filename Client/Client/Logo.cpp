#include "stdafx.h"
#include "Logo.h"
#include "Obj.h"
#include "MyMap.h"
#include "Terrain.h"
#include "BackTerrain.h"
#include "NPC.h"
#include "Abigail.h"
#include "Alex.h"
#include "Caroline.h"
#include "Demetrius.h"
#include "Elliott.h"
#include "Emily.h"
#include "Evelyn.h"
#include "George.h"
#include "Haley.h"
#include "Harvey.h"
#include "Jas.h"
#include "Jodi.h"
#include "Kent.h"
#include "Leah.h"

#include "Lewis.h"
#include "Linus.h"
#include "Marcello.h"
#include "Marlon.h"
#include "Marnie.h"
#include "Maru.h"
#include "Morris.h"
#include "Penny.h"
#include "Pierre.h"
#include "Robin.h"
#include "Sam.h"
#include "Sandy.h"
#include "Sebastian.h"
#include "Vincent.h"

#include "Player.h"
#include "TextBox.h"
#include "ReactionTerrain.h"

#include "Title.h"
#include "ClickBox.h"

CLogo::CLogo()
{
}
CLogo::~CLogo()
{
	Release();
}

HRESULT CLogo::Init()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPathInfo.txt")))
	{
		ERR_MSG(L"Image Load Failed");
		return E_FAIL;
	}

	// Ÿ�� 2104 -> ���� �ǰ�
	// Ÿ�� 2105-> ���Ѹ���

	//PathFile
	{
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Abigail/Abigail%d.dat", L"Abigail", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Alex/Alex%d.dat", L"Alex", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Caroline/Caroline%d.dat", L"Caroline", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Demetrius/Demetrius%d.dat", L"Demetrius", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Elliott/Elliott%d.dat", L"Elliott", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Emily/Emily%d.dat", L"Emily", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Evelyn/Evelyn%d.dat", L"Evelyn", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/George/George%d.dat", L"George", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Haley/Haley%d.dat", L"Haley", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Harvey/Harvey%d.dat", L"Harvey", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Jas/Jas%d.dat", L"Jas", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Jodi/Jodi%d.dat", L"Jodi", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Kent/Kent%d.dat", L"Kent", 1)))
// 			return E_FAIL;
// 		if (FAILED(CPathMgr::GetInstance()->InsertPath(L"../Data/Leah/Leah%d.dat", L"Leah", 1)))
// 			return E_FAIL;
	}


	//Object
	{
// 		CObj* pObj = CAbstractFactory<CPlayer>::CreateObj(OBJECT_ID_PLAYER);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_PLAYER);
// 
// 		pObj = CAbstractFactory<CAbigail>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 
// 		pObj = CAbstractFactory<CAlex>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CCaroline>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CDemetrius>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CElliott>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CEmily>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CEvelyn>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CGeorge>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CHaley>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CHarvey>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CJas>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CJodi>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CKent>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);
// 		pObj = CAbstractFactory<CLeah>::CreateObj(OBJECT_ID_NPC);
// 		if (nullptr == pObj)
// 			return E_FAIL;
// 		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_NPC);

		CObj* pObj = CAbstractFactory<CMyMap>::CreateObj(OBJECT_ID_MAP, 10);
		if (pObj == nullptr)
			return E_FAIL;
		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_MAP);

		 pObj = CAbstractFactory<CTitle>::CreateObj(OBJECT_ID_MENU);
		if (pObj == nullptr)
			return E_FAIL;
		CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_MENU);

		for (int i = 0; i < 4; ++i)
		{
			pObj = CAbstractFactory<CClickBox>::CreateObj(OBJECT_ID_MENU, i);
			if (pObj == nullptr)
				return E_FAIL;
			CObjectMgr::GetInstance()->AddObject(pObj, OBJECT_ID_MENU);

		}

	}

	return S_OK;
}

void CLogo::Update(const _float& fTimeDelta)
{
	CObjectMgr::GetInstance()->Update(fTimeDelta);
}

void CLogo::LateUpdate(const _float& fTimeDelta)
{
	CObjectMgr::GetInstance()->LateUpdate(fTimeDelta);
	if (CSceneMgr::GetInstance()->GetPass_ID() ==PASS_ID_FRONT)
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::GetInstance()->GetNextScene());
		CSceneMgr::GetInstance()->SetPass_ID(PASS_ID_END, SCENE_ID_END, SCENE_ID_END);
	}
}

void CLogo::Render()
{
	CObjectMgr::GetInstance()->Render();
}

void CLogo::Release()
{
	
}
