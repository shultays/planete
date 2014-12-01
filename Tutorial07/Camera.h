#pragma once

#ifndef CAMERA_H
#define CAMERA_H


#include <directxmath.h>
#include "SimpleMath.h"

using namespace DirectX;
using namespace SimpleMath;

class Camera{
public:

	Vector3 eye;
	Vector3 pos;
	Vector3 up;

	void setEye(Vector3 eye){
		this->eye = eye;
	}
	void setPos(Vector3 pos){
		this->pos = pos;
	}
	void setUp(Vector3 up){
		this->up = up;
	}
	void setEye(float x, float y, float z){
		this->eye = DirectX::XMVectorSet(x, y, z, 0.0f);
	}
	void setPos(float x, float y, float z){
		this->pos = DirectX::XMVectorSet(x, y, z, 0.0f);
	}
	void setUp(float x, float y, float z){
		this->up = DirectX::XMVectorSet(x, y, z, 0.0f);
	}


	DirectX::XMMATRIX getViewMatrix(){
		return DirectX::XMMatrixLookAtLH(pos, pos+eye, up);
	}
};

#endif