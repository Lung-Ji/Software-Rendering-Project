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

#include "EditorManager.h"
#include "EditorWindow.h"
#include "Inspector.h"

//////////////////////////////////////////// Client Function

#include "ENUM.h"
#include "DEFINE.h"

//////////////////////////////////////////// Object List

#include "Camera.h"
#include "Terrain.h"
#include "NPC.h"
#include "Monster.h"
#include "Player.h"

//////////////////////////////////////////// Scene List

#include "StartScene.h"

//////////////////////////////////////////// Manager
#include "GUIManager.h"
#include "KeyManager.h"
#include "SoundManager.h"
#include "RenderManager.h"
#include "ProtoManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "GameManager.h"

//////////////////////////////////////////// Global Variable

extern HWND			hWnd;
extern HINSTANCE	hInst;

//////////////////////////////////////////// End
#endif //PCH_H