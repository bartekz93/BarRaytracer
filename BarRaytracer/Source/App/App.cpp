#include"App.h"

using namespace framework;

App* App::Instance = NULL;

void App::Init(int w, int h) {
	App::Instance = this;
	CreateMainWindow(w, h);
	Logger::Init(hWnd);
	width = w;
	height = h;
	OnInit();
}

void App::Close() {
	isRunning = false;
}

void App::Release() {
	OnRelease();
}

void App::Run()
{
	isRunning = true;

	MSG msg;
	msg.message = WM_NULL;

	while (isRunning && !Logger::isError)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			OnUpdate();
			OnRender();
		}
	}
}

HRESULT CALLBACK App::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return App::Instance->WndProc(hwnd, msg, wParam, lParam);
}


void App::CreateMainWindow(int w, int h)
{
	WNDCLASSEX wincl;
	string sClassName = "Framework";

	wincl.hInstance = GetModuleHandle(0);
	wincl.lpszClassName = sClassName.c_str();
	wincl.lpfnWndProc = &App::StaticWndProc;
	wincl.style = 0;
	wincl.cbSize = sizeof(WNDCLASSEX);

	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	if (!RegisterClassEx(&wincl))
	{
		Logger::Error("Nie uda³o siê zarejestrowaæ klasy okna");
	}

	hWnd = CreateWindowEx(0, sClassName.c_str(), "Okno DX11", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, w, h, 0, NULL, GetModuleHandle(0), NULL);

	if (hWnd == NULL)
	{
		Logger::Error("Nie uda³o siê utworzyæ okna");
	}

	ShowWindow(hWnd, SW_NORMAL);
}

void App::AddInputListener(IInputListener& listener) 
{
	inputListeners.push_back(&listener);
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UINT button = 0;
	switch (msg)
	{
	case WM_CLOSE: isRunning = false;

	case WM_DESTROY:
		PostQuitMessage(0);       /* sWM_MBUTTON       end a WM_QUIT to the message queue */
		break;


	//---------------------------------------------------------------------------------------
	//										Obs³uga wejœcia
	//---------------------------------------------------------------------------------------
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	{
		for each (auto listener in inputListeners)
		{
			listener->OnMouseDown(
				LOWORD(lParam), HIWORD(lParam),
				(wParam & MK_LBUTTON) ? MK_LBUTTON :
				(wParam & MK_RBUTTON) ? MK_RBUTTON :
				(wParam & MK_MBUTTON) ? MK_MBUTTON : 0,
				(wParam & MK_SHIFT) ? MK_SHIFT :
				(wParam & MK_CONTROL) ? MK_CONTROL : 0);
		}
	}
	break;


	case WM_LBUTTONUP: if (button == 0) button = MK_LBUTTON;
	case WM_RBUTTONUP: if (button == 0) button = MK_RBUTTON;
	case WM_MBUTTONUP: if (button == 0) button = MK_MBUTTON;
	{
		for each (auto listener in inputListeners)
		{
			listener->OnMouseUp(
				LOWORD(lParam), HIWORD(lParam), button,
				(wParam & MK_SHIFT) ? MK_SHIFT :
				(wParam & MK_CONTROL) ? MK_CONTROL : 0);
		}
		button = 0;
	}
	break;

	case WM_MOUSEMOVE:
	{
		static int x, y;

		for each (auto listener in inputListeners)
		{
			listener->OnMouseMove(LOWORD(lParam), HIWORD(lParam), LOWORD(lParam) - x, HIWORD(lParam) - y,
				(wParam & MK_LBUTTON) ? MK_LBUTTON :
				(wParam & MK_RBUTTON) ? MK_RBUTTON :
				(wParam & MK_MBUTTON) ? MK_MBUTTON : 0,
				(wParam & MK_SHIFT) ? MK_SHIFT :
				(wParam & MK_CONTROL) ? MK_CONTROL : 0);
		}
		x = LOWORD(lParam);
		y = HIWORD(lParam);
	}
	break;

	case WM_MOUSEWHEEL:
	{
		for each (auto listener in inputListeners)
		{
			listener->OnMouseWheel(LOWORD(lParam), HIWORD(lParam), HIWORD(wParam));
		}
	}
	break;

	case WM_KEYDOWN:
	{
		for each (auto listener in inputListeners)
		{
			listener->OnKeyDown(wParam);
		}
	} 
	break;

	case WM_KEYUP:
	{
		for each (auto listener in inputListeners)
		{
			listener->OnKeyUp(wParam);
		}
	}
	break;

	case WM_CHAR:
	{
		for each (auto listener in inputListeners)
		{
			listener->OnChar(wParam);
		}
	}
	break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}