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
    void            Set_TileAll(const _tchar* pPath, const _tchar* pName, Engine::TILE_SIDE eId, TILE_STATE eState, TILEMODE_CHANGE eMode, _int iTileNumber = 0, _vec3 vNext = {})
    {
        m_pTileName = pName;
        m_eTileSide = eId;
        m_eTileState = eState;
        m_eTileMode = eMode;
        m_iTileNumber = iTileNumber;
        m_NextPos = vNext;
    }
    void            Set_TileAnimaiton(const _tchar* pName, _int iCnt, Engine::TILE_SIDE eId, TILE_STATE eState, TILEMODE_CHANGE eMode, _int iTileNumber = 0, _vec3 vNext = {})
    {
        m_iTextureCount = iCnt;
        m_pTileName = pName;
        m_eTileSide = eId;
        m_eTileState = eState;
        m_eTileMode = eMode;
        m_iTileNumber = iTileNumber;
        m_NextPos = vNext;
        for (int i = 0; i < iCnt; ++i)
        {
            TCHAR   Name[128] = L"";
            wsprintf(Name, m_pTileName.c_str(), i);
            m_vecAnimationName.push_back(Name);
        }
    
    }
    void            Set_TileState(TILE_STATE eid)        { m_eTileState = eid; }

    _int                   Get_TileNumber()              { return m_iTileNumber;}
    TILE_SIDE              Get_TileSideName()            { return m_eTileSide;  }
    TILE_STATE             Get_TileStateName()           { return m_eTileState; }
    TILEMODE_CHANGE        Get_TileMode()                { return m_eTileMode;  }
    _int                   Get_TileTextureNumber()       { return m_iTextureCount; }
    wstring                Get_TileTextureName()         { return m_pTileName;  }
    const _tchar*          Get_AnimationName(_uint iCnt) { return m_vecAnimationName[iCnt].c_str(); }
    TILE_STAGE             Get_TileStage()               { return m_eTileStage; }
    _vec3                  Get_NextPos()                 { return m_NextPos; }
    _bool                  Set_PotalOpen()               { return m_bPortal; }
    void                   Set_TextureID(IDirect3DBaseTexture9* pTexture) { m_pTexture = pTexture; }
    
    IDirect3DBaseTexture9* Get_Texture()                    { return m_pTexture; }
private:
    TILE_SIDE              m_eTileSide;
    TILE_STATE             m_eTileState;
    TILEMODE_CHANGE        m_eTileMode;
    TILE_STAGE             m_eTileStage;

    wstring                m_pTileName;
    IDirect3DBaseTexture9* m_pTexture;
           
    vector<wstring>  m_vecAnimationName;
private:
    _bool                  m_bPortal;
    _vec3                  m_NextPos;
    _int                   m_iTileNumber;
    _int                   m_iTextureCount;
public:
    static          TileInfo* Create(LPDIRECT3DDEVICE9 pGraphicDev);
    virtual		    Component* Clone();

private:
    virtual  void            Free();

};

