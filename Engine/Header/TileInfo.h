#pragma once
#include "Component.h"
#include "Engine_Define.h"

class TileInfo :
    public Component
{
private:
    explicit TileInfo();
    explicit TileInfo(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit TileInfo(const TileInfo& ths);
    virtual ~TileInfo();

public:

    virtual HRESULT		        Ready_Component();
    virtual INT			        Update_Component(CONST FLOAT& _DT);
    virtual VOID		        LateUpdate_Component(CONST FLOAT& _DT);
  
    //이건.. 지형이 가지고 있는 타일의 인덱스 정보를 담기위함 해당 인덱스가 가진 위치위에 이 타일이 놓여있다는걸 확인하기 위해서
    void            Set_TileId(TILE_SIDE eid) { m_eTileSide = eid; }
    void            Set_TileNumber(_int iTileNumber) { m_iTileNumber = iTileNumber; }
    void            Set_TileAll(const _tchar* pName, Engine::TILE_SIDE eId, TILE_STATE eState, TILEMODE_CHANGE eMode, _int iTileNumber = 0)
    {
        m_pTileName = pName;
        m_eTileSide = eId;
        m_eTileState = eState;
        m_eTileMode = eMode;
        m_iTileNumber = iTileNumber;

        wstring  path = L"../../Resource/Tile";
        wstring WideRootPath = path + L"/" + m_pTileName;
        D3DXIMAGE_INFO img;

        D3DXCreateTextureFromFileEx(GRPDEV, WideRootPath.c_str(), 0, 0, 1, 0,
            D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0,
            &img, NULL, (LPDIRECT3DTEXTURE9*)&m_pTexture);
    }
    void            Set_TileState(TILE_STATE eid) { m_eTileState = eid; }


    _int                 Get_TileNumber() { return m_iTileNumber; }
    TILE_SIDE            Get_TileSideName() { return m_eTileSide; }
    TILE_STATE           Get_TileStateName() { return m_eTileState; }
    TILEMODE_CHANGE      Get_TileMode() { return m_eTileMode; }
    const _tchar*        Get_TileTextureName() { return m_pTileName; }
    IDirect3DBaseTexture9* Get_TileTexture() { return m_pTexture; }

private:
    TILE_SIDE              m_eTileSide;
    TILE_STATE             m_eTileState;
    TILEMODE_CHANGE        m_eTileMode;
    const  _tchar*         m_pTileName;
    IDirect3DBaseTexture9* m_pTexture;

private:
    _int                   m_iTileNumber;
public:
    static          TileInfo* Create(LPDIRECT3DDEVICE9 pGraphicDev);
    virtual		    Component* Clone();

private:
    virtual  void            Free();

};

