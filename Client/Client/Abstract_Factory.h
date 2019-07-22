#pragma once
class CObj;

template <typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init()))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}
	static CObj* CreateObj(const _tchar* pFilePath, OBJECT_ID eID=OBJECT_ID_TERRAIN)
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init(pFilePath, eID)))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}

	static CObj* CreateObj(OBJECT_ID eID)
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init(eID)))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}


	static CObj* CreateObj(LAYER_ID eID)
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init(eID)))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}
};