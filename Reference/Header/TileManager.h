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
    vector<GameObject*>& Get_TileList() { return m_vecTileBuffer; }

public:
    HRESULT         Add_Tile(GameObject* pObject, _vec3 vPos );
    void            Delete_Tile(_vec3 vPos, _vec3 Origin, _vec3 vDir);
    HRESULT         Update_TileList(const _float& fTimeDetla);
    void            Render_TileList();

private:
    vector<GameObject*>     m_vecTileBuffer;

private:
    virtual void            Free();
};

END