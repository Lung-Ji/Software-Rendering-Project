#pragma once
#include "GameObject.h"

class Spawner :
    public GameObject
{
private:
    explicit Spawner(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit Spawner(const GameObject& _RHS);
    virtual ~Spawner();

public:

    virtual			HRESULT		Ready_GameObject(TILE_SIDE eid, TILE_SPAWNER eSpawn);
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

public:
    void                    Set_Buffer(TILE_SIDE eid);
    void                    Frame_Move(CONST FLOAT& _DT);
    void                    Monster_Spawn();
    Transform* Crash_Player();
private:
    HRESULT			Component_Initialize(TILE_SIDE eid, TILE_SPAWNER eSpawn );

    TileInfo*               m_pTileInfo;
    Transform*              m_pTransform;
    Buffer*                 m_pBuffer;
private:
    _float                  m_fFrame;
    _float                  m_fTime;
    _bool                   m_bStopFrame;
    _bool                   m_bSpawn;
public:
    static         Spawner* Create(LPDIRECT3DDEVICE9 pGraphicDev, TILE_SIDE eid, TILE_SPAWNER eSpawn);

private:
    virtual  void            Free();

};

