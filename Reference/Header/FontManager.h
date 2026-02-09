#pragma once

#include "Base.h"
#include "Engine_Define.h"
#include "Font.h"

BEGIN(Engine)

class ENGINE_DLL FontMgr : public Base
{
	DECLARE_SINGLETON(FontMgr)

private:
	explicit FontMgr();
	virtual ~FontMgr();

public:
	HRESULT				Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev,
		const _tchar* pFontTag,
		const _tchar* pFontType,
		const _uint& iWidth,
		const _uint& iHeight,
		const _uint& iWeight);

	void				Render_Font(const _tchar* pFontTag,
		const _tchar* pString,
		const _vec2* pPos,
		D3DXCOLOR Color);

private:
	FontObject* Find_Font(const _tchar* pFontTag);

private:
	map<const _tchar*, FontObject*>			m_mapFont;

private:
	virtual void	Free();
};

END