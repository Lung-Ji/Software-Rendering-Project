#pragma once
#include "GameObject.h"


namespace Engine
{
    TILE_SIDE;
    TILEMODE_CHANGE;
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
public:
    void                        Mode_Change();
    void                        Tile_Offset(_vec3 vMouse);
    void                        TIleXY_Intersect();
    void                        Cube_Intersect();
private:
    HRESULT			            Component_Initialize();
    _bool                       Check_Bottom(_vec3* vOrigin);
    void                        Check_TilePoint();
    void                        Check_Distance(_vec3 vMouse);
    //타일 체크용 버퍼
    Buffer*         m_pBuffer;
    Buffer*         m_pBufferTileFRONT;
    Buffer*         m_pBufferTileRIGHT;
    Buffer*         m_pBufferTileLEFT;
    Buffer*         m_pBufferTileBACK;


    Transform*      m_pTransform;

    _bool           m_bTileCheck;

    TILE_SIDE       m_eTile;

private:
    TILEMODE_CHANGE     m_eMode;
public:
    static      Tile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
   
private:
    virtual void            Free();

};

