#include "Planete.h"
#include "Tools.h"
#include "Sphere.h"
#include <vector>

void Planete::init(){
	ps.init_static();

	HRESULT hr = S_OK;

	shader.buildShader(L"Tutorial07.fx");

	std::vector<Vector3> vertice_vector;
	Sphere::build(4, vertice_vector);



	// Create vertex buffer
	s = vertice_vector.size();
	SimpleVertex* vertices = new SimpleVertex[s];

	for (int i = 0; i < s; i += 3){
		vertices[i].Pos = vertice_vector[i];
		vertices[i+1].Pos = vertice_vector[i+1];
		vertices[i+2].Pos = vertice_vector[i+2];


		Vector3 mid = vertices[i].Pos + vertices[i + 1].Pos + vertices[i + 2].Pos;
		mid.Normalize();


		vertices[i].Normal = vertices[i + 1].Normal = vertices[i + 2].Normal = mid;

		vertices[i].Tex = vertices[i + 1].Tex = vertices[i + 2].Tex = Vector2(0.0);
	}

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex)* s;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
	if (FAILED(hr))
		return;
	delete[] vertices;

	// Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);





	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBNeverChanges);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pCBNeverChanges);
	if (FAILED(hr))
		return;

	bd.ByteWidth = sizeof(CBChangeOnResize);
	hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pCBChangeOnResize);
	if (FAILED(hr))
		return;

	bd.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = g_pd3dDevice->CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
	if (FAILED(hr))
		return;

	// Load the Texture
	hr = CreateDDSTextureFromFile(g_pd3dDevice, L"seafloor.dds", nullptr, &g_pTextureRV);
	if (FAILED(hr))
		return;

	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
	if (FAILED(hr))
		return;

	// Initialize the world matrices
	g_World = XMMatrixIdentity();

	// Initialize the view matrix
	camera.setPos(0.0f, 0.0f, -4.0f);
	camera.setEye(0.0f, 0.0f, 1.0f);
	camera.setUp(0.0f, 1.0f, 0.0f);
	g_View = camera.getViewMatrix();

	CBNeverChanges cbNeverChanges;
	cbNeverChanges.mView = XMMatrixTranspose(g_View);
	g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, nullptr, &cbNeverChanges, 0, 0);

	// Initialize the projection matrix
	g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, screen_width / (FLOAT)screen_height, 0.01f, 100.0f);

	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
	g_pImmediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);

	g_vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);

	ps.init();
	
}

void Planete::render(){


	//
	// Update variables that change once per frame
	//
	CBChangesEveryFrame cb;
	cb.mWorld = XMMatrixTranspose(g_World);
	cb.vMeshColor = g_vMeshColor;
	g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);

	//
	// Render the cube
	//
	shader.activate();
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
	g_pImmediateContext->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
	g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
	g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
	g_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
	g_pImmediateContext->Draw(s, 0);


}

void Planete::tick(float dt){


	// Rotate cube around the origin
	g_World = XMMatrixRotationY(dt*0.2);
	//g_World = XMMatrixIdentity();
	/*// Modify the color
	g_vMeshColor.x = (sinf(dt * 1.0f) + 1.0f) * 0.5f;
	g_vMeshColor.y = (cosf(dt * 3.0f) + 1.0f) * 0.5f;
	g_vMeshColor.z = (sinf(dt * 5.0f) + 1.0f) * 0.5f;*/
}

void Planete::release(){
	if (g_pSamplerLinear) g_pSamplerLinear->Release();
	if (g_pTextureRV) g_pTextureRV->Release();
	if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
	if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
	if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	shader.release();


}