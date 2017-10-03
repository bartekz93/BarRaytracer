#define D3D_DEBUG_INFO
#include"RaytracerApp\RaytracerApp.h"

using namespace raytracerApp;

int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow )
{
	//Memory leak detection
#if defined _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(196);
#endif // _DEBUG

	RaytracerApp app;
	app.Init(800, 600);
	app.Run();
	app.Release();

	return 0;
}

