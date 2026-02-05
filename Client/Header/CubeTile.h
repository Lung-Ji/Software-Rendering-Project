#pragma once
#include "GameObject.h"

class CubeTile :
    public GameObject
{
private:
    explicit CubeTile();
    explicit CubeTile(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit CubeTile(const GameObject& ths);
    virtual ~CubeTile();

public:

    virtual			HRESULT		Ready_GameObject();
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

    //이건.. 지형이 가지고 있는 타일의 인덱스 정보를 담기위함 해당 인덱스가 가진 위치위에 이 타일이 놓여있다는걸 확인하기 위해서
    int             Get_TileNumber() { return m_iTileNumber; }
    void            Set_TileNumber(_int iTileNumber) { m_iTileNumber = iTileNumber; }
    void            Set_TileState(TILE_STATE eid) { m_eTileState = eid; }
        
private:
    HRESULT			Component_Initialize();
    TILE_STATE      m_eTileState;
    TILE_SIDE       m_eTileSide;
    
    const  _tchar* m_pTileName;
    Buffer*         m_pBuffer;
    Transform*      m_pTransform;
    int             m_iTileNumber;
public:
    static         CubeTile* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
   virtual  void            Free();

};

