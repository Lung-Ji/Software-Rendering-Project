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

    virtual			HRESULT		Ready_GameObject(TILE_SIDE eid, TILE_STATE eState, FLOAT& X1 , FLOAT& X2 , FLOAT& Y1 , FLOAT& Y2 );
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

    //이건.. 지형이 가지고 있는 타일의 인덱스 정보를 담기위함 해당 인덱스가 가진 위치위에 이 타일이 놓여있다는걸 확인하기 위해서
  
public:
    void            Set_Buffer(TILE_SIDE eid);
    D3DMATERIAL9            Set_Material();
    void                    Frame_Move      (CONST FLOAT& _DT);
    void                    Tile_Animation  (CONST FLOAT& _DT);
    void                    Tile_Destory    (CONST FLOAT& _DT);
    void                    Tile_Potal      (CONST FLOAT& _DT);
    void                    Tile_Potal_Effect(CONST FLOAT& _DT);
    void                    Tile_Trigger      ();
    void                    Tile_Gasi_Destory();
    Transform*              Crash_Player();
    Transform*              Crash_Arrow();
private:
    HRESULT			Component_Initialize(TILE_SIDE eid, TILE_STATE eState, FLOAT& X1, FLOAT& X2, FLOAT& Y1 , FLOAT& Y2);
    
    TileInfo*               m_pTileInfo;
    Transform*              m_pTransform;
    Buffer*                 m_pBuffer;
    Buffer*                 m_CubeBuffer;
    D3DMATERIAL9            m_Material;
private:
    _float                  m_fAlpha;
    _float                  m_fFrame;
    _float                  m_fTime;
    _bool                   m_bStopFrame;
    DWORD                   m_Alpha;

public:
    static         CXZTile* Create(LPDIRECT3DDEVICE9 pGraphicDev, TILE_SIDE eid, TILE_STATE eState, FLOAT& X1, FLOAT& X2, FLOAT& Y1, FLOAT& Y2);

private:
   virtual  void            Free();

};

