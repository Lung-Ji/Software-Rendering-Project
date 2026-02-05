#pragma once
class GUIManager {
	DECLARE_SINGLETON(GUIManager)
private:
	explicit GUIManager();
	~GUIManager();

public:
	enum class STATE { DISABLE, ACTIVE, DESTROYED };

public:
	VOID	Ready_GUIManager();
	VOID	Update_GUIManager();
	VOID	LateUpdate_GUIManager();
	VOID	Render_GUIManager();
	VOID	Release_GUIManager();

public:
	VOID	Setting_DarkTheme(); 

private:
	LPDIRECT3DDEVICE9		GRPDEV;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	CameraObject*				Camera;
	BOOL						UseWindow;

	bool		CameraWindow;
};

