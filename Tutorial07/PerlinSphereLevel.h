#pragma once
#ifndef PERLIN_SPHERE_LEVEL_H
#define PERLIN_SPHERE_LEVEL_H


#include "stdlib.h"

#include <directxmath.h>
#include <vector>
#include "SimpleMath.h"

#include "Tools.h"

class PerlinSphereLevel{
public:
	typedef struct{
		int vertical_coordinate;
		int horizontal_coordinate;
	}VertexCoordinate;

	static Quaternion qs[2][2][2];
	static void init_static(){
		qs[0][0][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), 0);
		qs[1][0][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1 ), PI3_2);
		qs[1][1][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI);
		qs[0][1][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI_2);


		qs[0][0][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI) * Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI_2);
		qs[1][0][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI) * Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI);
		qs[1][1][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI) * Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI3_2);
		qs[0][1][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI);
	}
	static Vector3 fix(Vector3 &v){
		Vector3 v2 = v;
		if (v2.x < 0) v2.x = -v2.x;
		if (v2.y < 0) v2.y = -v2.y;
		if (v2.z < 0) v2.z = -v2.z;
		return v2;
	}

	Quaternion rotateQuaterninon, rotateQuaterninonInverse;
	int level;

	PerlinSphereLevel(int level);
	float getHeight(Vector3 &p);

	void findTriangleOfVector(Vector3 &p, VertexCoordinate &p0, VertexCoordinate &p1, VertexCoordinate &p2, float &u, float &v);
};



#endif