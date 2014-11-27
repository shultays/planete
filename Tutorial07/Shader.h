#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <d3d11_1.h>
#include "Tools.h"

extern ID3D11Device*                       g_pd3dDevice;
extern ID3D11DeviceContext*					g_pImmediateContext;

class Shader{
public:
	ID3D11VertexShader*                 g_pVertexShader;
	ID3D11PixelShader*                  g_pPixelShader;
	ID3D11InputLayout*                  g_pVertexLayout;


	bool buildShader(WCHAR* fileName){

		HRESULT hr = S_OK;

		ID3DBlob* pVSBlob = nullptr;
		hr = Tools::CompileShaderFromFile(fileName, "VS", "vs_4_0", &pVSBlob);
		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return false;
		}

		// Create the vertex shader
		hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
		if (FAILED(hr))
		{
			pVSBlob->Release();
			return false;
		}

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);

		// Create the input layout
		hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(), &g_pVertexLayout);
		pVSBlob->Release();
		if (FAILED(hr))
			return false;

		// Set the input layout
		g_pImmediateContext->IASetInputLayout(g_pVertexLayout);

		// Compile the pixel shader
		ID3DBlob* pPSBlob = nullptr;
		hr = Tools::CompileShaderFromFile(fileName, "PS", "ps_4_0", &pPSBlob);
		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return false;
		}

		// Create the pixel shader
		hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
		pPSBlob->Release();
		if (FAILED(hr))
			return false;

		return true;
	}

	void activate(){
		g_pImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
		g_pImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);
	}
	void release(){
		if (g_pVertexLayout) g_pVertexLayout->Release();
		if (g_pVertexShader) g_pVertexShader->Release();
		if (g_pPixelShader) g_pPixelShader->Release();
	}
};

#endif