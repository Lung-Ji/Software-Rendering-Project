#pragma once
#include "GameObject.h"
enum class OBJECT_DESTORY { STONE, GRASS, DESTORY_END };
class TileDestoryEffect :
    public GameObject
{
private:
    explicit TileDestoryEffect(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit TileDestoryEffect(const GameObject& _RHS);
    virtual ~TileDestoryEffect();

public:
    virtual			HRESULT		Ready_GameObject(OBJECT_DESTORY eid, _int iCnt, _vec3 vPos);
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

public:
    void            Effect_On(OBJECT_DESTORY eId) { m_bEffect = true; m_eDestory = eId; }
    
public:
    void            Frame_Move(CONST FLOAT& _DT);
    void            Add_Effect(OBJECT_DESTORY eid,const _tchar* pName,_int iCnt);
private:
    HRESULT			                Component_Initialize();
    
private: 
    vector<IDirect3DBaseTexture9*>	m_vecTileEffectList[static_cast<int>(OBJECT_DESTORY::DESTORY_END)];
    vector<const _tchar*>           m_vecName[static_cast<int>(OBJECT_DESTORY::DESTORY_END)];
    
    Buffer*                         m_pTileEffectBuff;
    Transform*                      m_pTransform;

    OBJECT_DESTORY                  m_eDestory;

    _float                          m_fFrame;
    _float                          m_fTime;
    
    _bool                           m_bEffect;

    _int                            m_iCnt;
public:
    static         TileDestoryEffect* Create(LPDIRECT3DDEVICE9 pGraphicDev, OBJECT_DESTORY eid, _int iCnt, _vec3 vPos);

private:
    virtual  void            Free();

};

