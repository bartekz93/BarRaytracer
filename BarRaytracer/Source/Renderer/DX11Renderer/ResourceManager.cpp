#pragma once
#include<D3Dcompiler.h>
#include<D3DX11.h>
#include<DxErr.h>
#include"ResourceManager.h"

using namespace std;
using namespace framework;
using namespace dx11renderer;

DX11ResourceManager::DX11ResourceManager(ID3D11Device* dev, ID3D11DeviceContext* context) {
	Dev = dev;
	DevContext = context;
}

void DX11ResourceManager::OnRelease()
{
	for (int i = 0; i<VertexBuffers.size(); i++)
		VertexBuffers[i]->Release();
	for (int i = 0; i<IndexBuffers.size(); i++)
		IndexBuffers[i]->Release();
	for (int i = 0; i<InputLayouts.size(); i++)
		InputLayouts[i]->Release();
	for (int i = 0; i<VertexShaders.size(); i++)
		VertexShaders[i]->Release();
	for (int i = 0; i<PixelShaders.size(); i++)
		PixelShaders[i]->Release();
	for (int i = 0; i<ConstantBuffers.size(); i++)
		ConstantBuffers[i]->Release();
	for (int i = 0; i<StructuredBuffers.size(); i++)
		StructuredBuffers[i]->Release();
	for (int i = 0; i<StructuredBuffersViews.size(); i++)
		StructuredBuffersViews[i]->Release();
}


ConstantBuffer* DX11ResourceManager::CreateConstantBuffer(void* data, uint size)
{
	ConstantBuffer* CB = new ConstantBuffer();
	ID3D11Buffer* buff;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	if (data)
	{
		D3D11_SUBRESOURCE_DATA subresdata;
		subresdata.pSysMem = data;

		HRESULT hr = Dev->CreateBuffer(&bd, &subresdata, &buff);

		if (FAILED(hr))
		{
			Logger::Error("Create constant buffer failed", hr);
			return false;
		}
	}
	else
	{
		HRESULT hr = Dev->CreateBuffer(&bd, NULL, &buff);

		if (FAILED(hr))
		{
			Logger::Error("Create constant buffer failed", hr);
			return false;
		}
	}
	
	ConstantBuffers.push_back(buff);
	CB->SetId(ConstantBuffers.size() - 1);
	Resources.push_back(CB);
	return CB;
}

CompiledPixelShader* DX11ResourceManager::CompilePixelShader(const string& file, const string& funName)
{
	CompiledPixelShader* compiled = new CompiledPixelShader();
	ID3D10Blob* PixelShaderBlob;
	ID3D10Blob* ErrorBuffer;
	// Create the pixel shader

	HRESULT hr;
	if (FAILED(hr = D3DX11CompileFromFile(file.c_str(), NULL, NULL, funName.c_str(), "ps_4_0", D3DCOMPILE_PREFER_FLOW_CONTROL | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_SKIP_VALIDATION, NULL, NULL, &PixelShaderBlob, &ErrorBuffer, NULL)))
	{
		if (ErrorBuffer) Logger::Error((char*)ErrorBuffer->GetBufferPointer());
		Logger::Error("Pixel Shader compile failed", hr);
		return false;
	}

	compiled->Size = PixelShaderBlob->GetBufferSize();
	compiled->Data = new char[compiled->Size];
	for (int i = 0; i<compiled->Size; i++)
		compiled->Data[i] = ((char*)(PixelShaderBlob->GetBufferPointer()))[i];

	if (PixelShaderBlob) PixelShaderBlob->Release();
	if (ErrorBuffer) ErrorBuffer->Release();

	Resources.push_back(compiled);

	return compiled;
}

bool DX11ResourceManager::CreateBufferShaderResourceView(ID3D11Buffer* pBuffer)
{
	ID3D11ShaderResourceView* pSRVOut;

	D3D11_BUFFER_DESC descBuf;
	ZeroMemory(&descBuf, sizeof(descBuf));
	pBuffer->GetDesc(&descBuf);

	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	desc.BufferEx.FirstElement = 0;

	if (descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS)
	{
		// This is a Raw Buffer

		desc.Format = DXGI_FORMAT_R32_TYPELESS;
		desc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		desc.BufferEx.NumElements = descBuf.ByteWidth / 4;
	}
	else
		if (descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED)
		{
			// This is a Structured Buffer

			desc.Format = DXGI_FORMAT_UNKNOWN;
			desc.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;
		}
		else
		{
			return false;
		}

	HRESULT hr = Dev->CreateShaderResourceView(pBuffer, &desc, &pSRVOut);
	if (FAILED(hr))
	{
		Logger::Error("CreateShaderResourceView", hr);
		return false;
	}

	StructuredBuffersViews.push_back(pSRVOut);
	return true;
}

StructuredBuffer* DX11ResourceManager::CreateStructuredBuffer(void* data, uint stride, uint objects)
{
	StructuredBuffer* structuredBuffer = new StructuredBuffer();
	ID3D11Buffer* buffer = NULL;

	bool unordered = false;
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = unordered ? D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE : D3D11_BIND_SHADER_RESOURCE;
	desc.ByteWidth = stride*objects;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = stride;
	desc.Usage = D3D11_USAGE_DEFAULT;
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ

	if (data)
	{
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = data;
		HRESULT hr = Dev->CreateBuffer(&desc, &InitData, &buffer);
		if (FAILED(hr))
		{
			Logger::Error("Create buffer failed", hr);
			return false;
		}
	}
	else
	{
		HRESULT hr = Dev->CreateBuffer(&desc, NULL, &buffer);
		if (FAILED(hr))
		{
			Logger::Error("Create empty buffer failed", hr);
			return false;
		}
	}
	
	StructuredBuffers.push_back(buffer);
	structuredBuffer->SetId(StructuredBuffers.size() - 1);
	Resources.push_back(structuredBuffer);

	CreateBufferShaderResourceView(buffer);

	return structuredBuffer;
}


PixelShader* DX11ResourceManager::CreatePixelShader(const CompiledPixelShader& compiled)
{
	PixelShader* PS = new PixelShader;
	ID3D11PixelShader* DxPixelShader = NULL;

	HRESULT hr = Dev->CreatePixelShader(compiled.Data, compiled.Size, NULL, &DxPixelShader);
	if (FAILED(hr))
	{
		Logger::Error("CreatePixelShader failed", hr);
		return NULL;
	}


	PixelShaders.push_back(DxPixelShader);
	PS->SetId(PixelShaders.size() - 1);
	Resources.push_back(PS);
	return PS;
}

VertexShader* DX11ResourceManager::CreateVertexShader(const string& file, VertexLayout& inlayout, const string& funName)
{
	VertexShader* VS = new VertexShader;
	ID3D11VertexShader* DxVertexShader = NULL;
	ID3D11InputLayout* DxInputLayout = NULL;
	ID3D10Blob* VertexShaderBlob = NULL;
	ID3D10Blob* ErrorBuffer = NULL;

	// Create the vertex shader
	HRESULT hr;
	if (FAILED(hr = D3DX11CompileFromFile(file.c_str(), NULL, NULL, funName.c_str(), "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, NULL, NULL, &VertexShaderBlob, &ErrorBuffer, NULL)))
	{
		if (ErrorBuffer) Logger::Error((char*)ErrorBuffer->GetBufferPointer());
		Logger::Error("VertexShader compile failed", hr);
		return NULL;
	}

	SIZE_T size = VertexShaderBlob->GetBufferSize();
	hr = Dev->CreateVertexShader(VertexShaderBlob->GetBufferPointer(), size, NULL, &DxVertexShader);
	if (FAILED(hr))
	{
		Logger::Error("CreateVertexShader failed", hr);
		return NULL;
	}

	if (inlayout.GetId() < 0)
	{
		D3D11_INPUT_ELEMENT_DESC* lay = new D3D11_INPUT_ELEMENT_DESC[inlayout.GetSize()];

		for (int i = 0; i<inlayout.GetSize(); i++)
		{
			lay[i].SemanticName = inlayout.Get(i).SemanticName.c_str();
			lay[i].InputSlot = lay[i].SemanticIndex = 0;
			lay[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			lay[i].AlignedByteOffset = inlayout.Get(i).Offset;
			lay[i].InstanceDataStepRate = 0;


			switch (inlayout.Get(i).Type)
			{
			case VertexElement::VEC2:	lay[i].Format = DXGI_FORMAT_R32G32_FLOAT; break;
			case VertexElement::VEC3:	lay[i].Format = DXGI_FORMAT_R32G32B32_FLOAT; break;
			case VertexElement::VEC4:	lay[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT; break;
			}
		}

		if (FAILED(hr = Dev->CreateInputLayout(lay, inlayout.GetSize(), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &DxInputLayout)))
		{
			Logger::Error("CreateInputLayout failed", hr);
			return NULL;
		}

		InputLayouts.push_back(DxInputLayout);
		inlayout.SetId(InputLayouts.size() - 1);

		delete[] lay;
	}

	if (ErrorBuffer) ErrorBuffer->Release();
	if (VertexShaderBlob) VertexShaderBlob->Release();
	VertexShaders.push_back(DxVertexShader);
	VS->SetId(VertexShaders.size() - 1);
	VS->InputLayout = &inlayout;

	Resources.push_back(VS);
	return VS;
}

VertexBuffer* DX11ResourceManager::CreateVertexBuffer(void* data, uint size)
{
	VertexBuffer* VB = new VertexBuffer;
	ID3D11Buffer* buff;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = data;
	HRESULT hr = Dev->CreateBuffer(&bd, &InitData, &buff);
	if (FAILED(hr))
	{
		Logger::Error("CreateBuffer failed", hr);
		return NULL;
	}
	VertexBuffers.push_back(buff);
	VB->SetId(VertexBuffers.size() - 1);
	Resources.push_back(VB);
	return VB;
}

IndexBuffer* DX11ResourceManager::CreateIndexBuffer(void* data, uint size)
{
	IndexBuffer* ib = new IndexBuffer;
	ID3D11Buffer* buffer;

	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;        // 36 vertices needed for 12 triangles in a triangle list
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	//ZeroMemory( &InitData, sizeof(InitData) );
	InitData.pSysMem = data;
	hr = Dev->CreateBuffer(&bd, &InitData, &buffer);
	if (FAILED(hr))
	{
		Logger::Error("Create Index Buffer failed", hr);
		return false;
	}

	IndexBuffers.push_back(buffer);
	ib->SetId(IndexBuffers.size() - 1);
	Resources.push_back(ib);
	return ib;
}


ID3D11Buffer* DX11ResourceManager::GetDXVertexBuffer(VertexBuffer* vb)
{
	return VertexBuffers[vb->GetId()];
}

ID3D11Buffer* DX11ResourceManager::GetDXIndexBuffer(IndexBuffer* ib)
{
	return IndexBuffers[ib->GetId()];
}

ID3D11Buffer* DX11ResourceManager::GetDXStructuredBuffer(StructuredBuffer* sb)
{
	return StructuredBuffers[sb->GetId()];
}

ID3D11Buffer* DX11ResourceManager::GetDXConstantBuffer(ConstantBuffer* cb)
{
	return ConstantBuffers[cb->GetId()];
}

ID3D11InputLayout* DX11ResourceManager::GetDXInputLayout(VertexLayout* inlayout)
{
	return InputLayouts[inlayout->GetId()];
}

ID3D11VertexShader* DX11ResourceManager::GetDXVertexShader(VertexShader* vs)
{
	return VertexShaders[vs->GetId()];
}

ID3D11PixelShader* DX11ResourceManager::GetDXPixelShader(PixelShader* ps)
{
	return PixelShaders[ps->GetId()];
}

ID3D11ShaderResourceView* DX11ResourceManager::GetDXStructuredBuffersView(StructuredBuffer* sb)
{
	return StructuredBuffersViews[sb->GetId()];
}

void DX11ResourceManager::UpdateConstantBuffer(ConstantBuffer* buffer, void* data)
{
	DevContext->UpdateSubresource(GetDXConstantBuffer(buffer), 0, NULL, data, 0, 0);
}