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
        void SetSize(_float x, _float y)  { vSize.x = x; vSize.y = y;}
    };
public:

    virtual			HRESULT		Ready_GameObject();
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();
public:
    void                        Mode_Change();
    void                        Imgui();
    void                        Imgui_Setting();
    void                        Imgui_Image(const char* tName, TILE_STATE eid);
    void                        Imgui_ModeChanger();
    void                        Imgui_PivotButton(const char pName[32], _vec3* vPivot);
public:
    void                        Set_AnimationCount(int* icnt);
private:
    HRESULT                     Load_Image(const _tchar* pName, TILE_STATE eid);
    HRESULT                     LoadFile();
    HRESULT			            Component_Initialize();
    _bool                       Check_Bottom(_vec3* vOrigin);
    void                        Check_TilePoint();
    void                        Check_Distance(_vec3 vMouse);
    //타일 체크용 버퍼
    Buffer*                      m_pBuffer;
    Buffer*                      m_pTileLeft;
    Buffer*                      m_pTileRight;
    Buffer*                      m_pTileBack;
    Buffer*                      m_pTileFront;

    Transform*                   m_pTransform;

    _float                       m_fHeight;

    vector<const _tchar*>        m_vecName[TILE_STATE::STATE_END];
    vector<ImageFile>            m_vecImage[TILE_STATE::STATE_END];
    _bool                        m_bTileCheck;
    _bool                        m_bMouseClick;

    const _tchar*                m_pPathName;
    const _tchar*                m_pTileName;
    const _tchar*                m_pTileState;

private:
    _vec3                        m_vOriginal;
    _vec3                        m_vNextPos;
    _vec3                        m_vMousePos;
    _vec3                        m_vTilePos;
    _vec3                        m_vPosPivot;
    _vec3                        m_vScalePivot;
    _vec3                        m_vRotationPivot;
private:
    TILE_SIDE                    m_eTile;
    TILE_STATE                   m_eTileState;
    TILEMODE_CHANGE              m_eMode;
    TILE_STAGE                   m_eStage;
public:
    static      Tile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
   
private:
    virtual void            Free();

};

