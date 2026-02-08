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
    vector<GameObject*>& Get_TileList(TILE_STAGE eStage, TILEMODE_CHANGE eid) {
       
            return m_vecTileBuffer[eStage][eid];
        }

public:
    HRESULT         Add_Tile(GameObject* pObject, _vec3 vPos, TILE_STAGE eStage,TILEMODE_CHANGE eMode, TILE_SIDE eSid = TILE_SIDE::TILE_OTHER,_vec3 PivotHeight = { 0,0,0 });
    void            Delete_Tile(_vec3 vPos, _vec3 Origin, _vec3 vDir);
    HRESULT         Update_TileList(const _float& fTimeDetla);
    void            Render_TileList();
    void            Set_TileMode(TILEMODE_CHANGE eMode) { m_eMode = eMode; }

    void            Save_Tile(HWND g_hWnd);
    void            Load_TilePush(GameObject* pGame,TILE_STAGE eStage, TILEMODE_CHANGE eMod) { m_vecTileBuffer[eStage][eMod].push_back(pGame); }

    void            Change_Tile(TILE_STAGE eStage) { m_eStage = eStage; }
    void            Reset_TileList();
private:
    TILE_STAGE              m_eStage;
    TILEMODE_CHANGE         m_eMode;
    vector<GameObject*>     m_vecTileBuffer[TILE_STAGE::STAGE_END][TILEMODE_CHANGE::MODE_END];
private:
    virtual void            Free();
};

END