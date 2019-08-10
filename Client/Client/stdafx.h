// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
using namespace std;

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")



//Headers
#include "Define.h"
#include "Constant.h"
#include "Enum.h"
#include "Extern.h"
#include "Funtion.h"
#include "Funtor.h"
#include "Struct.h"
#include "Typedef.h"


// For.CRTDBG
#ifdef _DEBUG 
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif 
#endif  // _DEBUG  


//Managers
#include "Device.h"
#include "TimerMgr.h"
#include "FrameMgr.h"
#include "ObjectMgr.h"
#include "SceneMgr.h"
#include "Abstract_Factory.h"
#include "TextureMgr.h"
#include "KeyMgr.h"
#include "PathMgr.h"
#include "RenderMgr.h"
#include "FontMgr.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "MonsterMgr.h"
#include "MyFont.h"



//Console
//#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")