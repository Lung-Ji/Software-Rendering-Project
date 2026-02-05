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
    vector<GameObject*>& Get_TileList(TILEMODE_CHANGE eid) {
       
            return m_vecTileBuffer[eid];
        }

public:
    HRESULT         Add_Tile(GameObject* pObject, _vec3 vPos, TILEMODE_CHANGE eMode);
    void            Delete_Tile(_vec3 vPos, _vec3 Origin, _vec3 vDir);
    HRESULT         Update_TileList(const _float& fTimeDetla);
    void            Render_TileList();
    void            Set_TileMode(TILEMODE_CHANGE eMode) { m_eMode = eMode; }

private:
    TILEMODE_CHANGE         m_eMode;
    vector<GameObject*>     m_vecTileBuffer[TILEMODE_CHANGE::MODE_END];
private:
    virtual void            Free();
};

END