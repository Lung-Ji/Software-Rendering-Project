#pragma once
#include "GameObject.h"


class CXZTile :
    public GameObject
{
private:
    explicit CXZTile(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit CXZTile(const GameObject& _RHS);
    virtual ~CXZTile();

public:

    virtual			HRESULT		Ready_GameObject(TILE_SIDE eid);
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

    //이건.. 지형이 가지고 있는 타일의 인덱스 정보를 담기위함 해당 인덱스가 가진 위치위에 이 타일이 놓여있다는걸 확인하기 위해서
  
public:
    void            Set_Buffer(TILE_SIDE eid);
private:
    HRESULT			Component_Initialize(TILE_SIDE eid);
    
    TileInfo*              m_pTileInfo;
    Buffer*                m_pBuffer;
    Transform*             m_pTransform;

    _uint                  m_fFrame;
public:
    static         CXZTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, TILE_SIDE eid);

private:
   virtual  void            Free();

};

