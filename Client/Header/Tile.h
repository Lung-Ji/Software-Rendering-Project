#pragma once
#include "GameObject.h"
enum class INSTALL_MODE{MODE_INSTALL, MODE_MOVE, MODE_END};
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
    void                        Imgui_PivotButton(const char pName[32], _vec3* vPivot,_float iLinePivot = 0);
    void                        Imgui_ButtonStyle();
    void                        Imgui_ObjectValue(const char* TextName, const char* SliderName, const char* ButtonName, _vec3* vValue, _float fMax, _float fMin, _float iLinePivot = 0);
public:
    void                        Set_AnimationCount(int* icnt);

public:

    _bool                       Check_Bottom(_vec3* vOrigin);
    void                        Check_TilePoint();
    void                        Check_Distance(_vec3 vMouse);
    void                        Move_Tile();
private:
    HRESULT                     Load_Image(const _tchar* pName, TILE_STATE eid);
    HRESULT                     LoadFile();
    HRESULT			            Component_Initialize();
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
    vector<RECT>                 m_vecTileUnder;
    vector<UvXY>                 m_vecUVXY;
    _bool                        m_bTileCheck;
    _bool                        m_bMouseClick;
    _bool                        m_bOnlyAnimation;

    const _tchar*                m_pPathName;
    const _tchar*                m_pTileName;
    const _tchar*                m_pTileState;

private:
    _float                       m_fPivot;
    _int                         m_iStge;
    _int                         m_iMode;
    _int                         m_iNumber;
    _float                         m_iTileUnderNumber;

    _vec3                        m_vOriginal;
    _vec3                        m_vNextPos;
    _vec3                        m_vMousePos;
    _vec3                        m_vTilePos;
    _vec3                        m_vPosPivot;
    _vec3                        m_vScalePivot;
    _vec3                        m_vOriginRotation;
    _vec3                        m_vRotationPivot;
private:
    ID3DXSprite*                 m_Sprite;
    TILE_SIDE                    m_eTile;
    TILE_STATE                   m_eTileState;
    TILEMODE_CHANGE              m_eMode;
    TILE_STAGE                   m_eStage;
    TILE_SPAWNER                 m_eSpawner;
    INSTALL_MODE                 m_eTileInstall;
public:
    static      Tile* Create(LPDIRECT3DDEVICE9 pGraphicDev);
   
private:
    virtual void            Free();

};

