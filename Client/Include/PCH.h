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
#include "NPC.h"
#include "Monster_State.h"
#include "Monster.h"
#include "Monster1.h"
#include "BossMonster.h"
#include "Player.h"
#include "Tile.h"
#include "CubeTile.h"
#include "CXZTile.h"
#include "MainMenuButton.h"
#include "MainMenu.h"
//////////////////////////////////////////// Scene List

#include "StartScene.h"
#include "VillageScene.h"
#include "DungeonScene.h"

//////////////////////////////////////////// Manager
#include "GUIManager.h"
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