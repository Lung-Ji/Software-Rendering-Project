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
    struct ImageFile {
        wstring* wstr;
        _vec2     vSize;
    };
public:

    virtual			HRESULT		Ready_GameObject();
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();
public:
    void                        Mode_Change();
    void                        Tile_Offset(_vec3 vMouse);
    void                        Imgui();
    void                        Imgui_Setting();
    void                        Imgui_Image();
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

    Texture*        m_pTexture;

    Transform*      m_pTransform;

    vector<ImageFile>     m_vecImage;
    _bool           m_bTileCheck;

    TILE_SIDE       m_eTile;


    const _tchar*   m_pTileName;

private:
  
    TILEMODE_CHANGE     m_eMode;
public:
    static      Tile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
   
private:
    virtual void            Free();

};

