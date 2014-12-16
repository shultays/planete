#include "PerlinSphere.h"

PerlinSphere::PerlinSphere(){
	for(int i=0; i<5; i++)	{
		levels[i] = new PerlinSphereLevel(i+1);
	}
	Vector3 v = Vector3( 1.0f, 0, 0.001f);
	v.Normalize();
	levels[2]->getHeight(v);
	v = Vector3(1.0f, 0, -0.001f);
	v.Normalize();
	levels[2]->getHeight(v);
}

float PerlinSphere::getHeight(Vector3 &p){
	float height = 0.0f;
	for(int i=0; i<5; i++)	{
		height += levels[i]->getHeight(p);
	}
	return height;
}