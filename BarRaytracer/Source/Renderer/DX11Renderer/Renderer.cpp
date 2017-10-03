#pragma once
#include<D3DX11.h>
#include<DxErr.h>
#include"Renderer.h"

using namespace std;
using namespace framework;
using namespace dx11renderer;


//resolves unresolved external symbol in DxErr.lib in Win > 7
int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;

bool DX11Renderer::CreateRT()
{
	ID3D11Texture2D *pBackBuffer;
	HRESULT hr;
	if (FAILED(hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
	{
		Logger::Error("SwapChain->GetBuffer failed", hr);
		return false;
	}

	hr = Dev->CreateRenderTargetView(pBackBuffer, NULL, &PrimaryRenderTarget);
	pBackBuffer->Release();
	if (FAILED(hr))
	{
		Logger::Error("CreateRenderTargetView failed", hr);
		return false;
	}
	DevContext->OMSetRenderTargets(1, &PrimaryRenderTarget, NULL);
	return true;
}

bool DX11Renderer::Init(uint width, uint height, HWND hWnd, bool fullscreen)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = !fullscreen;

	HRESULT hr;

#ifdef _DEBUG 
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG | D3D11_RLDO_DETAIL, 0, 0, D3D11_SDK_VERSION, &sd, &SwapChain, &Dev, NULL, &DevContext)))
	{
		Logger::Error("D3D11CreateDeviceAndSwapChain failed");
		Logger::Error(DXGetErrorString(hr));
		return false;
	}
#endif

#ifndef _DEBUG
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, 0, 0,
		D3D11_SDK_VERSION, &sd, &SwapChain, &Dev, NULL, &DevContext)))
	{
		Logger::Error("D3D11CreateDeviceAndSwapChain failed");
		Logger::Error(DXGetErrorString(hr));
		return false;
	}
#endif

	if (!CreateRT()) return false;

	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = false;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(Dev->CreateRasterizerState(&rasterDesc, &RasterizerState)))
	{
		Logger::Error("CreateRasterizerState failed");
		Logger::Error(DXGetErrorString(hr));
		return false;
	}

	DevContext->RSSetState(RasterizerState);
	DevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Manager = new DX11ResourceManager(Dev, DevContext);
}

void DX11Renderer::SetViewport(float topLeftX, float topLeftY, float width, float height)
{
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = topLeftX;
	vp.TopLeftY = topLeftY;
	DevContext->RSSetViewports(1, &vp);
}

void DX11Renderer::Render(uint startIndex, uint indexCount)
{
	DevContext->ClearRenderTargetView(PrimaryRenderTarget, ClearColor);
	DevContext->DrawIndexed(indexCount, startIndex, 0);
	SwapChain->Present(0, 0);
}


void DX11Renderer::SetVertexBuffer(VertexBuffer* vb, uint stride, uint offset)
{
	auto buff = Manager->GetDXVertexBuffer(vb);
	DevContext->IASetVertexBuffers(0, 1, &buff, (UINT*)&stride, (UINT*)&offset);
}

void DX11Renderer::SetIndexBuffer(IndexBuffer* ib)
{
	DevContext->IASetIndexBuffer(Manager->GetDXIndexBuffer(ib), DXGI_FORMAT_R16_UINT, 0);
}

void DX11Renderer::SetVertexLayout(VertexLayout* layout)
{
	if (LastLayout == layout) return;
	DevContext->IASetInputLayout(Manager->GetDXInputLayout(layout));
	LastLayout = layout;
}

void DX11Renderer::SetVertexShader(VertexShader* vs)
{
	SetVertexLayout(vs->InputLayout);
	DevContext->VSSetShader(Manager->GetDXVertexShader(vs), NULL, 0);
}

void DX11Renderer::SetPixelShader(PixelShader* pshader)
{
	DevContext->PSSetShader(Manager->GetDXPixelShader(pshader), NULL, 0);
}

void DX11Renderer::SetConstantBuffer(ConstantBuffer* cb, uint slot)
{
	auto buff = Manager->GetDXConstantBuffer(cb);
	DevContext->PSSetConstantBuffers(slot, 1, &buff);
}

void DX11Renderer::SetStructuredBuffer(StructuredBuffer* sb, uint slot)
{
	auto view = Manager->GetDXStructuredBuffersView(sb);
	DevContext->PSSetShaderResources(slot, 1, &view);
}


void DX11Renderer::Release()
{
	Manager->Release();

	if (PrimaryRenderTarget) 
	{
		PrimaryRenderTarget->Release();
		PrimaryRenderTarget = NULL;
	}
	if (RasterizerState)
	{
		RasterizerState->Release();
		RasterizerState = NULL;
	}
	if (SwapChain) 
	{ 
		SwapChain->Release(); 
		SwapChain = NULL; 
	}
	if (DevContext) 
	{ 
		DevContext->Release(); 
		DevContext = NULL; 
	}
	if (Dev) 
	{ 
		Dev->Release();	
		Dev = NULL; 
	}

	delete Manager;
}

