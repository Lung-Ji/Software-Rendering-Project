#pragma once
#include "GameObject.h"

namespace Engine
{
    Engine::TILE_SIDE;
}

class CXZTile :
    public GameObject
{
private:
    explicit CXZTile();
    explicit CXZTile(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit CXZTile(const GameObject& ths);
    virtual ~CXZTile();

public:

    virtual			HRESULT		Ready_GameObject();
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

    //이건.. 지형이 가지고 있는 타일의 인덱스 정보를 담기위함 해당 인덱스가 가진 위치위에 이 타일이 놓여있다는걸 확인하기 위해서
    void            Set_TileId(TILE_SIDE eid) { m_eTileSide = eid; }
    int             Get_TileNumber() { return m_iTileNumber; }
    void            Set_TileNumber(_int iTileNumber) { m_iTileNumber = iTileNumber; }

private:
    HRESULT			Component_Initialize();
    
    TILE_SIDE       m_eTileSide;
    
    Buffer*         m_pBuffer;
    Transform*      m_pTransform;
    int             m_iTileNumber;
public:
    static         CXZTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, Engine::TILE_SIDE eId);

private:
   virtual  void            Free();

};

