#pragma once
#ifndef PLANETE_H
#define PLANETE_H

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"
#include "SimpleMath.h"
#include "Camera.h"
#include "Shader.h"
#include "PerlinSphere.h"

using namespace DirectX;
using namespace SimpleMath;


extern ID3D11DeviceContext*					g_pImmediateContext;
extern ID3D11DeviceContext1*               g_pImmediateContext1;
extern ID3D11Device*                       g_pd3dDevice;
extern ID3D11Device1*                      g_pd3dDevice1;

extern UINT screen_width;
extern UINT screen_height;

class Planete {
	struct SimpleVertex
	{
		Vector3 Pos;
		Vector2 Tex;
		Vector3 Normal;
	};

	struct CBNeverChanges
	{
		XMMATRIX mView;
	};

	struct CBChangeOnResize
	{
		XMMATRIX mProjection;
	};

	struct CBChangesEveryFrame
	{
		XMMATRIX mWorld;
		XMFLOAT4 vMeshColor;
	};


	ID3D11Buffer*                       g_pVertexBuffer;
	ID3D11Buffer*                       g_pCBNeverChanges;
	ID3D11Buffer*                       g_pCBChangeOnResize;
	ID3D11Buffer*                       g_pCBChangesEveryFrame;
	ID3D11ShaderResourceView*           g_pTextureRV;
	ID3D11SamplerState*                 g_pSamplerLinear;
	XMMATRIX                            g_World;
	XMMATRIX                            g_View;
	XMMATRIX                            g_Projection;
	XMFLOAT4                            g_vMeshColor;

	int s;

	Camera camera;
	Shader shader;
	PerlinSphere ps;

public:
	void init();

	void tick(float dt);

	void render();

	void release();

};

#endif