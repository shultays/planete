#pragma once

#ifndef PERLIN_SPHERE_H
#define PERLIN_SPHERE_H

#include "stdlib.h"

#include <directxmath.h>
#include <vector>
#include "SimpleMath.h"
#include "Sphere.h"

using namespace DirectX;
using namespace SimpleMath;

class PerlinSphere{
public:
	Sphere p1;
	Sphere p2;
	Sphere p3;
	Sphere p4;


	void init(){
		p1.initWithIndex(1);
		p2.initWithIndex(2);
		p3.initWithIndex(3);
		p4.initWithIndex(4);


		printf("%d\n", p1.vertex.size());
		printf("%d\n", p2.vertex.size());
		printf("%d\n", p3.vertex.size());
		printf("%d\n", p4.vertex.size());
	}
	float getRandom(){
		return ((float)rand()) / RAND_MAX;
	}


	float getHeightAt(int depth, Vector3 point){


		return 0.0f;
	}

};

#endif