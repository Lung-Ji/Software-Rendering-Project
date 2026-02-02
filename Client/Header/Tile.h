#pragma once
#include "GameObject.h"

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
    _bool           Check_Bottom(_matrix* matWorld, _vec3* vPos, _vec3* vOrigin, _vec3* vDirection);
    void            Check_TilePoint();
    Buffer*         m_pBuffer;
    Transform*      m_pTransform;

    _bool           m_bTileCheck;
    _float          m_TileHeight;
public:
    static      Tile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
   
private:
    virtual void            Free();

};

