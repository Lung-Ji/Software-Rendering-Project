#include "../include/PCH.h"
#include "EditorManager.h"

IMPLEMENT_SINGLETON(EditorManager)
EditorManager::EditorManager(){}


ImGuiWindowFlags EditorManager::Flags = ImGuiWindowFlags_None;

ImGuiDockNodeFlags EditorManager::DockspaceFlags = ImGuiDockNodeFlags_None;

EditorManager::STATE EditorManager::State = EditorManager::STATE::ACTIVE;

bool EditorManager::FullScreen = true;

map<wstring, EditorWindow*> EditorManager::EditorWindows;

D3DXVECTOR2 EditorManager::ViewportBounds[2] = {};
D3DXVECTOR2 EditorManager::ViewportSize;
bool EditorManager::ViewportFocused = false;
bool EditorManager::ViewportHovered = false;
//ya::graphics::RenderTarget* EditorManager::mFrameBuffer = nullptr;

void EditorManager::OpenProject() {
}
void EditorManager::NewScene() {
}
void EditorManager::SaveScene() {
}
void EditorManager::SaveSceneAs() {
}

void EditorManager::Initialize() {
	IMGUIInitialize();
    //Inspector* InspectorWindow = new Inspector();
    //EditorWindows.insert({ L"InspectorWindow", InspectorWindow });
}
void EditorManager::Update() {

}
void EditorManager::Release() {
    for (auto iter : EditorWindows)
    {
        delete iter.second;
        iter.second = nullptr;
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
void EditorManager::Render() {
    IMGUIRender();
}

void EditorManager::IMGUIInitialize() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    DarkTheme();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
   
    ImGuiStyle& Style = ImGui::GetStyle();
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        Style.WindowRounding = 0.f;
        Style.Colors[ImGuiCol_WindowBg].w = 1.f;
    }
    ImGui_ImplWin32_EnableDpiAwareness();
    ImGui_ImplDX9_Init(GraphicDevice::GetInstance()->Get_Device());
    ImGui_ImplWin32_Init(hWnd);
}

void EditorManager::IMGUIRender() {
    _bool Show_DemoWindow = TRUE;
    _bool Show_AnotherWindow = FALSE;
    ImVec4 Clear_Color = { 0.45f, 0.55f, 0.6f, 1.f };
    static int counter = 0;

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DockSpaceUpdate();
    DockSpaceRender();

    for (auto iter : EditorWindows) {

        iter.second->Render();
    }

    //ImGuizmo::SetOrthographic(FALSE);
    //ImGuizmo::SetDrawlist(ImGui::GetCurrentWindow()->DrawList);
    //
    //GameObject* Cam = SceneManager::GetInstance()->Get_CurrentScene()->Get_GameObject(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_CAMERA);
    //
    //ImGuizmo::Manipulate((float*)dynamic_cast<CameraObject*>(Cam)->Get_ViewMatrix()->m,
    //   (float*)dynamic_cast<CameraObject*>(Cam)->Get_ProjMatrix()->m,
    //   ImGuizmo::TRANSLATE | ImGuizmo::ROTATE | ImGuizmo::SCALE, ImGuizmo::WORLD,
    //   (float*)dynamic_cast<CameraObject*>(Cam)->Get_WorldMatrix()->m);
   
       //if (Show_DemoWindow)
       //     ImGui::ShowDemoWindow(&Show_DemoWindow);
   

       ImGui::Begin("Camera Setting");
       ImGui::Text("Transform");
      
       //ImGui::InputFloat3("EYEX", EyeX);
       //ImGui::InputFloat3("EYEY", EyeY);
       //ImGui::InputFloat3("EYEZ", EyeZ);
       ////ImGui::InputFloat3("EYE", &Show_DemoWindow);
       //ImGui::Checkbox("ANOTHER", &Show_AnotherWindow);
       //
       //FLOAT V = 0.f;
       ////ImVec4 Clear_Color = { 0.45f, 0.55f, 0.6f, 1.f };
       //ImGui::SliderFloat("Camera", &V, 0.f, 1.f);
       //ImGui::ColorEdit3("Clear Color", (FLOAT*)&Clear_Color);
       //
       //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
       //    counter++;
       //ImGui::SameLine();
       //ImGui::Text("counter = %d", counter);
       //
       //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
       ImGui::End();
   
   if (Show_AnotherWindow)
   {
       ImGui::Begin("Another Window", &Show_AnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
       ImGui::Text("Hello from another window!");
       if (ImGui::Button("Close Me"))
           Show_AnotherWindow = false;
       ImGui::End();
   }
   
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    
    UpdatePlatform();
}

void EditorManager::UpdatePlatform() {
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void EditorManager::DarkTheme() {
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}

void EditorManager::DockSpaceUpdate() {
    if (State == STATE::DISABLE)    return;

    Flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    
    if (FullScreen) {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        Flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse  | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
        Flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    if (DockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        Flags |= ImGuiWindowFlags_NoBackground;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    bool Active = static_cast<bool>(State);
    ImGui::Begin("EditorApplication", &Active, Flags);
    ImGui::PopStyleVar();
  
    if (FullScreen) ImGui::PopStyleVar(2);
    
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 400.f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), DockspaceFlags);
    }
 
    style.WindowMinSize.x = minWinSizeX;
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            if (ImGui::MenuItem("Open Project", "Ctrl + 0"))                OpenProject();
            ImGui::Separator();
            if (ImGui::MenuItem("New Scene", "Ctrl + N"))                   NewScene();
            if (ImGui::MenuItem("Save Scene", "Ctrl + S"))                  SaveScene();
            if (ImGui::MenuItem("Save Scene As", "Ctrl + Shift + S"))       SaveSceneAs();
            ImGui::Separator();
            ImGui::EndMenu();
        }
            if (ImGui::BeginMenu("Script"))
            {
                if (ImGui::MenuItem("Reload assembly", "Ctrl+R"))
                {
                   
                }
    
                ImGui::EndMenu();
            }
    
        }
    ImGui::EndMenuBar();
    for (auto iter : EditorWindows) {
        iter.second->Update();
    }
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Viewport");
    auto viewportMinRegion = ImGui::GetWindowContentRegionMin(); // ������ �ּ� ��ǥ
    auto viewportMaxRegion = ImGui::GetWindowContentRegionMax(); // ������ �ִ� ��ǥ
    auto viewportOffset = ImGui::GetWindowPos(); // ������ ��ġ
    
    const int letTop = 0;
    ViewportBounds[letTop] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
    
    const int rightBottom = 1;
    ViewportBounds[rightBottom] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
    
    // check if the mouse,keyboard is on the Sceneview
    ViewportFocused = ImGui::IsWindowFocused();
    ViewportHovered = ImGui::IsWindowHovered();
    
    // to do : mouse, keyboard event
    // 
    
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
    //ImGui::Image((ImTextureID)myTextureID, ViewportSize, ImVec2(0, 1), ImVec2(1, 0));
    //ya::graphics::Texture* texture = mFrameBuffer->GetAttachmentTexture(0);
    
    
    ImGui::Image((ImTextureID)(GraphicDevice::GetInstance()->Get_TempSurface()), ImVec2{ViewportSize.x, ViewportSize.y}
    , ImVec2{ 0, 0 }, ImVec2{ 1, 1 });
    
    // Open Scene by drag and drop
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PROJECT_ITEM"))
        {
            const wchar_t* path = (const wchar_t*)payload->Data;
            //OpenScene(path);
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::End();
}

void EditorManager::DockSpaceRender() {
   
}


