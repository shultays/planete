#include "DebugDraw.h"


DebugDraw dd;

void DebugDraw::init(){

	shader.buildShader(L"DebugDraw.fx");


	vertices = new DebugVertex[1000];


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(DebugVertex)* 1000;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;

	g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);


}