#pragma once
#include "Base.h"
#include "Engine_Define.h"
#include "GameObject.h"
#include "Buffer.h"
BEGIN(Engine)

class ENGINE_DLL TileImageManager :
    public Base
{
    DECLARE_SINGLETON(TileImageManager)
private:
    explicit TileImageManager();
    virtual ~TileImageManager();

public:
    vector<Texture*>& Get_TileImageList(TILE_IMAGEPAGE eId) { return m_vecTileImage[eId]; }

public:
    HRESULT         Add_TileImage(Texture* pTexture, TILE_IMAGEPAGE eid);
    void            Delete_TileImage(_vec3 vPos, _vec3 Origin, _vec3 vDir);
    HRESULT         Update_TileImageList(const _float& fTimeDetla);
    void            Render_TileImageList();

private:
    vector<Texture*>     m_vecTileImage[TILE_IMAGEPAGE::IMAGEPAGE_END];

private:
    virtual void            Free();
};

END