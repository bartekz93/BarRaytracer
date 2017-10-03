#pragma once
#include<D3DX11.h>
#include<DxErr.h>
#include"Logger.h"

using namespace framework;

bool Logger::isError = false;
HWND Logger::hWnd = 0;

void Logger::Init(HWND hwnd) {
	isError = false;
	hWnd = hwnd;
}

void Logger::Error(const string& err, HRESULT hr)
{
	string errstr = DXGetErrorDescription(hr);
	MessageBox(hWnd, (err + "\n" + (hr ? errstr : "")).c_str(), "Error", MB_ICONERROR);
	isError = true;
}

void Logger::Info(const string& err)
{
	MessageBox(hWnd, err.c_str(), "Error", MB_ICONINFORMATION);
}
