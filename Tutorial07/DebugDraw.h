#pragma once
#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"
#include "SimpleMath.h"
#include "Shader.h"
#include "Tools.h"

using namespace DirectX;
using namespace SimpleMath;

typedef struct 
{
	Vector3 Pos;
	Vector3 Color;
	Vector3 Data;
}DebugVertex;




class DebugDraw{
public:
	void init();

	Shader shader;
	DebugVertex* vertices;
	int vertexCount;
	ID3D11Buffer*                       g_pVertexBuffer;
};

extern DebugDraw dd;
#endif