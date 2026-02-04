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
    vector<Texture*>& Get_TileImageList() { return m_vecTileImage; }

public:
    HRESULT         Add_Tile(GameObject* pObject, _vec3 vPos, TILE_SIDE eTile);
    void            Delete_TileImage(_vec3 vPos, _vec3 Origin, _vec3 vDir);
    HRESULT         Update_TileImageList(const _float& fTimeDetla);
    void            Render_TileImageList();

private:
    vector<Texture*>     m_vecTileImage;

private:
    virtual void            Free();
};

END