#include "../Include/PCH.h"
#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

HWND        hWnd;       HINSTANCE   hInst;
WCHAR       szTitle[MAX_LOADSTRING];
WCHAR       szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
//#ifdef _DEBUG
//    if (::AllocConsole() == TRUE)
//    {
//        FILE* nfp[3];
//        freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//        freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//        freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//        std::ios::sync_with_stdio();
//    }
//#endif // _DEBUG
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) return FALSE;
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
    GameManager* GM = GameManager::Create();
    GUIManager::GetInstance()->Ready_GUIManager();
   // EditorManager::GetInstance()->Initialize();
    MSG msg;
    msg.message = WM_NULL;

    if (!GM) return FALSE;

    TimeManager::GetInstance()->Ready_TimeManager();                        // 전체 타이머 초기화
    
    TimeManager::GetInstance()->Activate_Timer(TIMERTYPE::TIMER_WORLD);     // 월드  타이머 활성화
    TimeManager::GetInstance()->Activate_Timer(TIMERTYPE::TIMER_FPS);       // FPS용 타이머 활성화
    FLOAT FixedFPS = 60.f;
    
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (WM_QUIT == msg.message) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            
            TimeManager::GetInstance()->Update_TimeManager(TIMERTYPE::TIMER_WORLD);
            
            if (TimeManager::GetInstance()->Check_FixedFrame(TimeManager::GetInstance()->Get_DeltaTime(TIMERTYPE::TIMER_WORLD), FixedFPS)) {

                TimeManager::GetInstance()->Update_TimeManager(TIMERTYPE::TIMER_FPS);

                TimeManager::GetInstance()->Count_FrameAndDeltaTime(hWnd, TIMERTYPE::TIMER_FPS);            // FPS & DT 카운트 (+윈도우 타이틀 바 출력)

                GUIManager::GetInstance()->Update_GUIManager();
                GM->Update_GameManager(TimeManager::GetInstance()->Get_DeltaTime(TIMERTYPE::TIMER_FPS));
                GM->LateUpdate_GameManager(TimeManager::GetInstance()->Get_DeltaTime(TIMERTYPE::TIMER_FPS));
                GM->Render_GameManager();

                GUIManager::GetInstance()->LateUpdate_GUIManager();
                GUIManager::GetInstance()->Render_GUIManager();

                GM->Get_DeviceClass()->Render_End();
            }
        }
    }

    GUIManager::GetInstance()->Release_GUIManager();
    ULONG ReferenceCount = 0;

    if (ReferenceCount = Engine::Safe_Release(GM)) {
        MSG_BOX("Cannot Release GameManager");
        return FALSE;
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(NULL);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;
    RECT    rc{ 0,0, WINCX, WINCY };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    POINT Resolution = { GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN) };

    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));
    //SetProcessDPIAware();
    hWnd = CreateWindowW(szWindowClass, L"Software Rendering Project", WS_OVERLAPPEDWINDOW,
       (Resolution.x - WINCX)/2, (Resolution.y - WINCY) / 2 - 50, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

    
    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return TRUE;

    switch (message)
    {
    //case WM_DPICHANGED:
    //    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
    //    {
    //        //const int dpi = HIWORD(wParam);
    //        //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
    //        const RECT* suggested_rect = (RECT*)lParam;
    //        ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
    //    }
    //    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            DestroyWindow(hWnd);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
