#pragma once
#define NULL_CHECK_VOID(PTR) if(nullptr == PTR) return;
#define NULL_CHECK_VAL(PTR, RETURN_VAL) if(nullptr == PTR) return RETURN_VAL;

#define ERR_MSG(message)						\
MessageBox(g_hWnd, message, L"Error!", MB_OK);

#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName& _Obj);			\
	ClassName& operator=(const ClassName& _Obj);

#define _DECLARE_SINGLETON(ClassName)			\
		NO_COPY(ClassName)						\
public:											\
	static ClassName* GetInstance()				\
	{											\
		if(nullptr == m_pInstance)				\
			m_pInstance = new ClassName;		\
		return m_pInstance;						\
	}											\
	void DestroyInstance()						\
	{											\
		if(m_pInstance)							\
		{										\
			delete m_pInstance;					\
			m_pInstance = nullptr;				\
		}										\
	}											\
private:										\
	static ClassName*	m_pInstance;			

#define _IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;


template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}