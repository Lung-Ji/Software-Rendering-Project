#ifndef PCH_H
#define PCH_H
//////////////////////////////////////////// Precompiled Header

#include "framework.h"
#include <process.h>
#include <io.h>
#include <iostream>

//////////////////////////////////////////// Engine Import
////////////////////////////// IMGUIZMO Import
#include "ImGuizmo.h"
#include "ImSequencer.h"
#include "ImZoomSlider.h"
#include "ImCurveEdit.h"
#include "GraphEditor.h"

//////////////////////////////

#include "Base.h"
#include "Engine_Define.h"
#include "GraphicDevice.h"

//////////////////////////////////////////// Client Function

#include "ENUM.h"
#include "DEFINE.h"

//////////////////////////////////////////// Object List

#include "Camera.h"
#include "Terrain.h"
#include "MainUI.h"
#include "Inventory.h"
#include "NPCTalk.h"
#include "PlayerEffect.h"
#include "UIEffect.h"
#include "NPC.h"
#include "Object_Explain.h"
//#include "Monster_State.h"
//#include "Monster1.h"
//#include "BossMonster.h"

#include "Monster.h"
#include "MonsterTest.h"

//#include "MonsterSummon01.h"
//#include "MonsterSummon02.h"
//#include "MonsterSummon03.h"
#include "Bat.h"
#include "ScorpionEvilSoul.h"
#include "Docheol.h"

#include "Bullet_Standard.h"
#include "Fireball.h"

#include "Player.h"
#include "Tile.h"
#include "CubeTile.h"
#include "CXZTile.h"
#include "MainMenuButton.h"
#include "MainMenu.h"
#include "Bow.h"
#include "Arrow.h"
#include "TileDestoryEffect.h"
#include "PlayerInven.h"
#include "Augments.h"
#include "Spawner.h"
//////////////////////////////////////////// Scene List

#include "StartScene.h"
#include "DebugScene.h"
#include "MapScene.h"
//////////////////////////////////////////// Manager
#include "FontManager.h"
#include "GUIManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EffectManager.h"
#include "UIManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "ProtoManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "TileManager.h"
//////////////////////////////////////////// Global Variable

extern HWND			hWnd;
extern HINSTANCE	hInst;

//////////////////////////////////////////// End
#endif //PCH_H