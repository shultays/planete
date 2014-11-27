
#include <directxmath.h>

class Camera{
public:

	DirectX::XMVECTOR eye;
	DirectX::XMVECTOR pos;
	DirectX::XMVECTOR up;

	void setEye(DirectX::XMVECTOR eye){
		this->eye = eye;
	}
	void setPos(DirectX::XMVECTOR pos){
		this->pos = pos;
	}
	void setUp(DirectX::XMVECTOR up){
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
		return DirectX::XMMatrixLookAtLH(eye, pos, up);
	}
};