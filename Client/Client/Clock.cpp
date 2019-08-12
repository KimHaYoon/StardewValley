#include "stdafx.h"
#include "Clock.h"
#include "ClockHand.h"
#include "Define.h"
#include "GameTime.h"
#include "Player.h"

CClock::CClock()
{
}


CClock::~CClock()
{
	Release();
}

HRESULT CClock::Init()
{
	return S_OK;
}


HRESULT CClock::Init(OBJECT_ID eID)
{
	_float fSize = (float)WINCX / 1920.f * 1.8f;

	m_tInfo.vPos = { WINCX - (153.f * fSize) ,153.f * fSize, 0.f };
	m_tInfo.vSize = { fSize, fSize, 0.f };

	//1366 x 768
	m_strObjectKey = L"UI";
	m_strStateKey = L"ETC";

	m_fSpeed = 10.f;
	m_tFrame = { 0.f, 1.f };

	_matrix matTrans, matScale;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matTrans;

	CRenderMgr::GetInstance()->AddRenderObect(this, LAYER_ID_6);

	m_pClockHand = CAbstractFactory<CClockHand>::CreateObj(OBJECT_ID_UI);
	if (m_pClockHand == nullptr)
		return E_FAIL;
	CObjectMgr::GetInstance()->AddObject(m_pClockHand, OBJECT_ID_UI);

	CMyFont::GetInstance()->Ready_Font(L"ClockInfo", (_int)(40.f * fSize), (_int)(18.f * fSize), L"Impact");
	CMyFont::GetInstance()->Get_Font(L"ClockInfo");	// 이 함수 호출로 사용할 폰트 가져옴

	CMyFont::GetInstance()->Ready_Font(L"MoneyInfo", (_int)(56.f * fSize), (_int)(30.5f * fSize), L"Impact");
	CMyFont::GetInstance()->Get_Font(L"MoneyInfo");	// 이 함수 호출로 사용할 폰트 가져옴

	return S_OK;
}

_int CClock::Update(const _float & fTimeDelta)
{
	CGameTime::GetInstance()->Update(fTimeDelta);
	CGameTime::GetInstance()->Input();
	return NO_EVENT;
}

void CClock::LateUpdate(const _float & fTimeDelta)
{
}

void CClock::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(
		m_strObjectKey, m_strStateKey, INFOCLOCK);
	NULL_CHECK_VOID(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	RenderFont();
}

void CClock::Release()
{
}

void CClock::RenderFont()
{
	UNITIFNO tInfo = m_tInfo;
	_float fSize = (float)WINCX / 1920.f;
	{ // 요일, 일
		TCHAR strDay[10] = { '\0', };
		DAY eDay = CGameTime::GetInstance()->GetCurrentDay();
		_int iDate = CGameTime::GetInstance()->GetCurrentDate();
		if (eDay == SUNDAY)
		{
			wsprintf(strDay, L"일요일. %d", iDate);
		}
		else if (eDay == MONDAY)
		{
			wsprintf(strDay, L"월요일. %d", iDate);
		}
		else if (eDay == TUESDAY)
		{
			wsprintf(strDay, L"화요일. %d", iDate);
		}
		else if (eDay == WEDNESDAY)
		{
			wsprintf(strDay, L"수요일. %d", iDate);
		}
		else if (eDay == THURSDAY)
		{
			wsprintf(strDay, L"목요일. %d", iDate);
		}
		else if (eDay == FRIDAY)
		{
			wsprintf(strDay, L"금요일. %d", iDate);
		}
		else if (eDay == SATURDAY)
		{
			wsprintf(strDay, L"토요일. %d", iDate);
		}

		tInfo.vPos = { (float)WINCX - (320.f * fSize), 65.f * fSize, 0.f };
		//tInfo.vPos = { (float)WINCX / 2.f, (float)WINCY / 2.f, 0.f };

		_matrix matTrans, matScale;
		D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
		tInfo.matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
		CMyFont::GetInstance()->Get_Font(L"ClockInfo")->DrawTextW(CDevice::GetInstance()->GetSprite(),
			strDay, lstrlen(strDay), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}
	{ // 시간
		TCHAR strDay[10] = { '\0', };
		_int iHour = CGameTime::GetInstance()->GetCurrentHour();
		_int iMin = CGameTime::GetInstance()->GetCurrentMin() * 10;
		wsprintf(strDay, L"%d:%d", iHour, iMin);

		tInfo.vPos = { (float)WINCX - (250.f * fSize), 220.f * fSize, 0.f };
		//tInfo.vPos = { (float)WINCX / 2.f, (float)WINCY / 2.f, 0.f };

		_matrix matTrans, matScale;
		D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
		tInfo.matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
		CMyFont::GetInstance()->Get_Font(L"ClockInfo")->DrawTextW(CDevice::GetInstance()->GetSprite(),
			strDay, lstrlen(strDay), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
	}
	{ // 소지금
		TCHAR strDay[10] = { '\0', };
		_int iMoney = dynamic_cast<CPlayer*>(CObjectMgr::GetInstance()->GetPlayer())->GetMoney();
		wsprintf(strDay, L"%d", iMoney);

		tInfo.vPos = { (float)WINCX - (115.f * fSize), 360.f * fSize, 0.f };
		_int iCount = -1;
		for (int n = iMoney; n > 0; n = n / 10)
		{
			iCount++;
		}
		if (iMoney == 0)
			iCount = 0;
		tInfo.vPos.x -= 45.f * fSize * iCount;
		//tInfo.vPos = { (float)WINCX / 2.f, (float)WINCY / 2.f, 0.f };

		_matrix matTrans, matScale;
		D3DXMatrixScaling(&matScale, tInfo.vSize.x, tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, tInfo.vPos.x, tInfo.vPos.y, 0.f);
		tInfo.matWorld = matScale * matTrans;

		CDevice::GetInstance()->GetSprite()->SetTransform(&tInfo.matWorld);
		CMyFont::GetInstance()->Get_Font(L"MoneyInfo")->DrawTextW(CDevice::GetInstance()->GetSprite(),
			strDay, lstrlen(strDay), nullptr, 0, D3DCOLOR_ARGB(255, 180, 0, 0));
	}
}