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
	static CObj* CreateObj(const _tchar* pFilePath)
	{
		CObj* pObject = new T;

		if (FAILED(pObject->Init(pFilePath)))
		{
			SafeDelete(pObject);
			return nullptr;
		}

		return pObject;
	}
};