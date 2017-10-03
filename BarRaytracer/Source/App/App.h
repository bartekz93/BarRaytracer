#pragma once
#include"Common.h"
#include"Interfaces/IInputListener.h"

namespace framework
{

	class App {

	public:
		static App* Instance;

		void Init(int w, int h);
		void Run();
		void Release();
		void Close();

		void AddInputListener(IInputListener& listener);

	protected:
		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnRelease() {}
		virtual void OnInit() {}

		vector<IInputListener*> inputListeners;
		HWND hWnd;
		uint width;
		uint height;
		bool isRunning;

		static	HRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		HRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void CreateMainWindow(int w, int h);
	};
};