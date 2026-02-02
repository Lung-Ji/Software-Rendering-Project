#ifndef Engine_Macro_h__
#define Engine_Macro_h__

namespace Engine
{
	#define	WINCX		1280
	#define	WINCY		720

	#define	VTXCNTX		129
	#define VTXCNTZ		129
	#define VTXITV		1

	#ifndef			MSG_BOX
	#define			MSG_BOX(_message)			MessageBox(NULL, TEXT(_message), L"System Message", MB_OK)
	#endif

	#define			BEGIN(NAMESPACE)		namespace NAMESPACE {
	#define			END						}
	
	#define			USING(NAMESPACE)	using namespace NAMESPACE;
	
	#ifdef	ENGINE_EXPORTS
	#define ENGINE_DLL		_declspec(dllexport)
	#else
	#define ENGINE_DLL		_declspec(dllimport)
	#endif


	#define NULL_CHECK( _ptr)	\
		{if( _ptr == 0){ return;}}
	
	#define NULL_CHECK_RETURN( _ptr, _return)	\
		{if( _ptr == 0){return _return;}}
	
	#define NULL_CHECK_MSG( _ptr, _message )		\
		{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);}}
	
	#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
		{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);return _return;}}
	
	#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
		{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK);  return E_FAIL;}
	
	#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
		{ MessageBoxW(NULL, L"Failed", L"System Error",MB_OK);  return _return;}
	
	#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
		{ MessageBoxW(NULL, _message, L"System Message",MB_OK); return E_FAIL;}
	
	#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
		{ MessageBoxW(NULL, _message, L"System Message",MB_OK); return _return;}
	
	#define COMPONENT_SINGLETON(CLASSNAME)	DECLARE_SINGLETON(CLASSNAME)
	
	#define NO_COPY(CLASSNAME)								\
			private:										\
			CLASSNAME(const CLASSNAME&) = delete;					\
			CLASSNAME& operator = (const CLASSNAME&) = delete;		
	
	#define DECLARE_SINGLETON(CLASSNAME)					\
			NO_COPY(CLASSNAME)								\
			private:										\
			static CLASSNAME*	m_pInstance;				\
			public:											\
			static CLASSNAME*	GetInstance( void );		\
			static void DestroyInstance( void );			
	
	#define IMPLEMENT_SINGLETON(CLASSNAME)					\
			CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
			CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
				if(NULL == m_pInstance) {					\
					m_pInstance = new CLASSNAME;			\
				}											\
				return m_pInstance;							\
			}												\
			void CLASSNAME::DestroyInstance( void ) {		\
				if(NULL != m_pInstance)	{					\
					delete m_pInstance;						\
					m_pInstance = NULL;						\
				}											\
			}
	#define DECLARE_FSM_SINGLETON(CLASSNAME)				\
			NO_COPY(CLASSNAME)								\
			private:										\
			static CLASSNAME*	m_pInstance;				\
			public:											\
			static CLASSNAME*	GetInstance( void );		\
			static void DestroyInstance( void );			\
			CLASSNAME* Instance() { return m_pInstance; }	\
			private:										\
				CLASSNAME() {}								\
				virtual ~CLASSNAME() {}						
}

#endif // Engine_Macro_h__
