#pragma once

/////////////////////////////////// SOUNDMANAGER ///////////////////////////////////
#define PLAY_SOUND(FILENAME, CHANNEL)	SoundManager::GetInstance()->Play_Sound(FILENAME, CHANNEL);						// 채널에 사운드 플레이
#define STOP_SOUND(CHANNEL)				SoundManager::GetInstance()->Stop_Sound(CHANNEL);								// 해당 채널 사운드 정지
#define STOP_ALLSOUND					SoundManager::GetInstance()->Stop_AllSound();									// 모든 채널 사운드 정지
#define CHECK_SOUNDPLAYING(CHANNEL)		SoundManager::GetInstance()->IsPlaying(CHANNEL);								// 음악 플레이 여부 확인
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////// KEYMANAGER /////////////////////////////////////
#define KEY_DOWN(KEY_IDX)				KeyManager::GetInstance()->KEY_STATE_DOWN(KEY_IDX)	== TRUE						// 해당 키 최초 입력
#define KEY_HOLD(KEY_IDX)				KeyManager::GetInstance()->KEY_STATE_HOLD(KEY_IDX)	== TRUE						// 해당 키 입력 유지
#define KEY_UP(KEY_IDX)					KeyManager::GetInstance()->KEY_STATE_UP(KEY_IDX)	== TRUE						// 해당 키 입력 중지

#define MOUSE_LBUTTON					KeyManager::GetInstance()->MOUSE_LB_DOWN()										// 마우스 L 버튼 최초 입력
#define MOUSE_RBUTTON					KeyManager::GetInstance()->MOUSE_RB_DOWN()										// 마우스 R 버튼 최초 입력
#define MOUSE_MOVE(KEY_IDX)				KeyManager::GetInstance()->Get_MouseMove(KEY_IDX)								// 마우스 움직임 감지
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////// SCENEMANAGER /////////////////////////////////////
#define CHANGE_SCENE_START				SceneManager::GetInstance()->Scene_Transition(StartScene::Create(GRPDEV));		// 시작 씬으로 전환
#define CHANGE_SCENE_VILLAGE			SceneManager::GetInstance()->Scene_Transition(VillageScene::Create(GRPDEV));	// 마을 씬으로 전환
#define CHANGE_SCENE_DUNGEON			SceneManager::GetInstance()->Scene_Transition(DungeonScene::Create(GRPDEV));	// 던전 씬으로 전환
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////// COMPONENT //////////////////////////////////////

#define ADD_COMPONENT_TRIANGLE			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_TRIANGLE));		// 삼각형 출력 컴포넌트 추가
#define ADD_COMPONENT_RECTANGLE			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_RECTANGLE),x, y);	// 사각형 출력 컴포넌트 추가
#define ADD_COMPONENT_RECTTEX			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_RECTTEX));		// 사각 텍스쳐 출력 컴포넌트 추가
#define ADD_COMPONENT_TERRAIN			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_TERRAIN));		// 지형 텍스쳐 출력 컴포넌트 추가
#define ADD_COMPONENT_TRANSFORM			dynamic_cast<Transform*>(Add_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM));	// TRANSFORM 컴포넌트 추가
#define ADD_COMPONENT_TEXTURE			dynamic_cast<Texture*>(Add_Component(COMPONENT_TYPE::COMPONENT_TEXTURE));		// 텍스쳐 저장 컴포넌트 추가
#define ADD_COMPONENT_SPRITE			dynamic_cast<SpriteObject*>(Add_Component(COMPONENT_TYPE::COMPONENT_SPRITE));	// 텍스쳐 저장 컴포넌트 추가
#define ADD_COMPONENT_COLLIDER			dynamic_cast<Collider*>(Add_Component(COMPONENT_TYPE::COMPONENT_COLLIDER));	// 텍스쳐 저장 컴포넌트 추가
#define ADD_COMPONENT_FSM				dynamic_cast<StateMachine*>(Add_Component(COMPONENT_TYPE::COMPONENT_FSM));	// FSM 컴포넌트
#define ADD_COMPONENT_TILE				dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_TILE));		// 타일
#define ADD_COMPONENT_CUBE				dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_CUBE));		// 큐브
#define ADD_COMPONENT_TILEFRONT			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_TILEFRONT));   // 타일 옆면
#define ADD_COMPONENT_TILELEFT			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_TILELEFT));
#define ADD_COMPONENT_TILERIGHT			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_TILERIGHT));
#define ADD_COMPONENT_TILEBACK			dynamic_cast<Buffer*>(Add_Component(COMPONENT_TYPE::COMPONENT_TILEBACK));
#define ADD_COMPONENT_TILEINFO			dynamic_cast<TileInfo*>(Add_Component(COMPONENT_TYPE::COMPONENT_TILEINFO));
#define ADD_COMPONENT_UISPRITE			dynamic_cast<UISprite*>(Add_Component(COMPONENT_TYPE::COMPONENT_UISPRITE));

////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////// EFFECT /////////////////////////////////////////				
#define PLAY_PLAYER_EFFECT(SKILL_TYPE, PLAYTIME)		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::PLAYER,	\
	PlayerEffect::Create(GRPDEV, SKILL_TYPE, Component_Transform, TRUE, PLAYTIME));						// 플레이어 : 이펙트 반복 실행
#define PLAY_PLAYER_EFFECT_ONCE(SKILL_TYPE, PLAYTIME)	EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::PLAYER,	\
	PlayerEffect::Create(GRPDEV, SKILL_TYPE, Component_Transform, FALSE, PLAYTIME));					// 플레이어 : 이펙트 최초 한번 실행

#define PLAY_MONSTER_EFFECT(SKILL_TYPE, PLAYTIME)		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::MONSTER,	\
	MonsterEffect::Create(GRPDEV, SKILL_TYPE, Component_Transform, TRUE, PLAYTIME));					// 몬스터 : 이펙트 반복 실행
#define PLAY_MONSTER_EFFECT_ONCE(SKILL_TYPE, PLAYTIME)	EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::MONSTER,	\
	MonsterEffect::Create(GRPDEV, SKILL_TYPE, Component_Transform, FALSE, PLAYTIME));					// 몬스터 : 이펙트 최초 한번 실행

#define PLAY_UI_EFFECT(SKILL_TYPE, _TAG, _X, _Y, _SX, _SY, PLAYTIME, OPAC)			EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::UI,	\
	UIEffect::Create(GRPDEV, _TAG, SKILL_TYPE, {_X, _Y, 0.f}, {_SX, _SY, 0.f}, OPAC, TRUE, PLAYTIME));		// 몬스터 : 이펙트 반복 실행
#define PLAY_UI_EFFECT_ONCE(SKILL_TYPE, _TAG, _X, _Y, _SX, _SY, PLAYTIME, OPAC)		EffectManager::GetInstance()->Append_Effect(EFFECT_OWNER::UI,	\
	UIEffect::Create(GRPDEV, _TAG, SKILL_TYPE, {_X, _Y, 0.f}, {_SX, _SY, 0.f}, OPAC, FALSE, PLAYTIME));		// 몬스터 : 이펙트 최초 한번 실행

#define REPLAY_UI_EFFECT(_TAG)		UIEffect::Replay_Effect(_TAG);
////////////////////////////////////////////////////////////////////////////////////
