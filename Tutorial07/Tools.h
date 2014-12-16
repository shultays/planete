#pragma once
#ifndef TOOLS_H
#define TOOLS_H

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"

#define PI 3.14159265359f
#define PI_2 1.57079632679f
#define PI3_2 4.71238898038f
#define PI2 6.28318530718f

using namespace DirectX;
using namespace SimpleMath;

class Tools{
public:

	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		// Disable optimizations to further improve shader debugging
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		ID3DBlob* pErrorBlob = nullptr;
		hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hr))
		{
			if (pErrorBlob)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
				pErrorBlob->Release();
			}
			return hr;
		}
		if (pErrorBlob) pErrorBlob->Release();

		return S_OK;
	}


	static inline Vector2 normalizedXyzToSpherical(Vector3 v){
		return Vector2(atan2(v.x, v.z), acos(v.y));
	}


	static inline Vector3 xyzToSpherical(Vector3 v){
		float l = v.Length();
		return Vector3(l, atan2(v.x, v.z), acos(v.y / l));
	}



	static inline Vector3 SphericalToXyz(Vector3 v){
		return SphericalToXyz(v.x, v.y, v.z);

	}

	static inline Vector3 SphericalToXyz(float r, float horizontal, float vertical){
		float sh = sin(horizontal);
		float ch = cos(horizontal);
		float sv = sin(vertical);
		float cv = cos(vertical);

		return Vector3(r*sv*sh, r*cv, r*sv*ch);
	}

	static inline Vector3 SphericalToXyz(Vector2 v){
		return SphericalToXyz(1.0f, v.x, v.y);
	}
	static inline Vector3 SphericalToXyz(float horizontal, float vertical){
		return SphericalToXyz(1.0f, horizontal, vertical);
	}


	static inline bool pointInTriangleSpherical(Vector3 &A, Vector3 &B, Vector3 &C, Vector3& P){
		Vector3 v0 = C - A;
		Vector3 v1 = B - A;


		Vector3 n = v1.Cross(v0);


		float a = -(n.x*A.x + n.y*A.y + n.z*A.z) / (P.x + P.y + P.z);

		P *= a;

		Vector3 v2 = P - A;

		float dot00 = dot(v0, v0);
		float dot01 = dot(v0, v1);
		float dot02 = dot(v0, v2);
		float dot11 = dot(v1, v1);
		float dot12 = dot(v1, v2);

		float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
		float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

		return (u >= 0) && (v >= 0) && (u + v < 1.0f);
	}


	static inline bool pointInTriangle(Vector3 &A, Vector3 &B, Vector3 &C, Vector3 P){


		Vector3 v0 = C - A;
		Vector3 v1 = B - A;
		Vector3 v2 = P - A;

		float dot00 = dot(v0, v0);
		float dot01 = dot(v0, v1);
		float dot02 = dot(v0, v2);
		float dot11 = dot(v1, v1);
		float dot12 = dot(v1, v2);

		float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
		float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

		return (u >= 0) && (v >= 0) && (u + v < 1.0f);
	}


	static inline bool pointInTriangle(Vector2 &A, Vector2 &B, Vector2 &C, Vector2 &P, float &u, float &v){
		Vector3 v0 = C - A;
		Vector3 v1 = B - A;
		Vector3 v2 = P - A;

		float dot00 = dot(v0, v0);
		float dot01 = dot(v0, v1);
		float dot02 = dot(v0, v2);
		float dot11 = dot(v1, v1);
		float dot12 = dot(v1, v2);

		float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
		u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		v = (dot00 * dot12 - dot01 * dot02) * invDenom;

		return (u >= -0.000001f) && (v >= -0.000001f) && (u + v < 1.0f + 0.000001f);
	}
	static inline bool pointInTriangle(Vector2 &A, Vector2 &B, Vector2 &C, Vector2 &P){

		float u, v;
		return pointInTriangle(A, B, C, P, u, v);
	}

	static inline float dot(Vector3 &v, Vector3 v2){
		return v.Dot(v2);
	}

	static float getRandom(){
		return ((float)rand()) / RAND_MAX;
	}

	static float getRandom(float a, float b){
		float l = b - a;
		float r = getRandom();
		return a + l*r;
	}
};

#endif