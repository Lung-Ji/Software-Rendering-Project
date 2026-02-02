#pragma once
#include "GameObject.h"

namespace Engine
{
    TILE_SIDE;
}
class Tile :
    public GameObject
{
private:
    explicit Tile();
    explicit Tile(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit Tile(const GameObject& ths);
    virtual ~Tile();

public:

    virtual			HRESULT		Ready_GameObject();
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

private:
    HRESULT			Component_Initialize();
    _bool           Check_Bottom(_vec3* vOrigin);
    void            Check_TilePoint();

    //타일 체크용 버퍼
    Buffer*         m_pBuffer;
    Buffer*         m_pBufferTileFRONT;
    Buffer*         m_pBufferTileRIGHT;
    Buffer*         m_pBufferTileLEFT;
    Buffer*         m_pBufferTileBACK;

    Transform*      m_pTransform;

    _bool           m_bTileCheck;

    TILE_SIDE       m_eTile;
    _float          m_TileHeight;
public:
    static      Tile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
   
private:
    virtual void            Free();

};

