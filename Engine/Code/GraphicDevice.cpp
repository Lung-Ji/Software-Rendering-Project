#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(GraphicDevice)

GraphicDevice::GraphicDevice() : SDK(nullptr), GRPDEV(nullptr) {}
GraphicDevice::~GraphicDevice() {}

HRESULT GraphicDevice::Ready_GraphicDevice(HWND _hWnd, WINMODE _WMODE, const UINT& _SX, const UINT& _SY, GraphicDevice** _GRPD) {
	SDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (!SDK) return E_FAIL;

	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	D3DPRESENT_PARAMETERS PreParam;
	ZeroMemory(&PreParam, sizeof(D3DPRESENT_PARAMETERS));

	if (FAILED(SDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))	return E_FAIL;
	
	_ulong DeviceFlag = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)	DeviceFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else														DeviceFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	PreParam.BackBufferWidth = _SX;
	PreParam.BackBufferHeight = _SY;
	PreParam.BackBufferFormat = D3DFMT_A8R8G8B8;
	PreParam.BackBufferCount = 1;

	PreParam.SwapEffect = D3DSWAPEFFECT_DISCARD;

	PreParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	PreParam.MultiSampleQuality = 0;

	PreParam.hDeviceWindow = _hWnd;
	PreParam.Windowed = _WMODE;

	PreParam.AutoDepthStencilFormat = D3DFMT_D24S8;
	PreParam.EnableAutoDepthStencil = TRUE;

	PreParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	PreParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(SDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, DeviceFlag, &PreParam, &GRPDEV)))	return E_FAIL;

	*_GRPD = this;


	
	return S_OK;
}
void GraphicDevice::Render_Begin(D3DXCOLOR _CLR) {
	//GraphicDevice::GetInstance()->Get_Device()->GetRenderTarget(0, &BackSurface);
	//GraphicDevice::GetInstance()->Get_Device()->SetRenderTarget(0, TempSurface);
	GRPDEV->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, _CLR, 1.f, 0);
	GRPDEV->BeginScene();
}
void GraphicDevice::Render_End() {
	GRPDEV->EndScene();
	GRPDEV->Present(NULL, NULL, NULL, NULL);
	//GraphicDevice::GetInstance()->Get_Device()->SetRenderTarget(0, BackSurface);
	//BackSurface->Release();
}
void GraphicDevice::Free() {
	

	Safe_Release(GRPDEV);
	Safe_Release(SDK);
}
