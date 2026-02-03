#pragma once
#include "Base.h"
#include "Engine_Define.h"
#include "GameObject.h"
#include "Buffer.h"
BEGIN(Engine)

class ENGINE_DLL TileManager :
    public Base
{
    DECLARE_SINGLETON(TileManager)
private:
    explicit TileManager();
    virtual ~TileManager();


public:
    vector<GameObject*>& Get_TileList() { 
        if (m_eMode == TILEMODE_CHANGE::MODE_TILE)
            return m_vecTileBuffer;
        else return m_vecCubeBuffer;
        }

public:
    HRESULT         Add_Tile(GameObject* pObject, _vec3 vPos, TILE_SIDE eTile);
    void            Delete_Tile(_vec3 vPos, _vec3 Origin, _vec3 vDir);
    HRESULT         Update_TileList(const _float& fTimeDetla);
    void            Render_TileList();
    void            Set_TileMode(TILEMODE_CHANGE eMode) { m_eMode = eMode; }

private:
    TILEMODE_CHANGE         m_eMode;
    vector<GameObject*>     m_vecTileBuffer;
    vector<GameObject*>     m_vecCubeBuffer;
private:
    virtual void            Free();
};

END