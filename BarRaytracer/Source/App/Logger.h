#pragma once
#include"Common.h"


namespace framework
{
	class Logger {

	public:
		static HWND hWnd;
		static bool isError;

		static void Init(HWND hwnd);
		static void Error(const string& err, HRESULT hr = 0);
		static void Info(const string& err);
	};
};