#pragma once

#ifndef PERLIN_SPHERE_H
#define PERLIN_SPHERE_H

#include "stdlib.h"

#include <directxmath.h>
#include <vector>
#include "SimpleMath.h"
#include "Sphere.h"
#include "Tools.h"

using namespace DirectX;
using namespace SimpleMath;

class PerlinSphere{
public:
	Sphere p1;
	Sphere p2;
	Sphere p3;
	Sphere p4;


	void init(){
		p1.init(1);
		p2.init(2);
		p3.init(3);
		p4.init(4);


	}
	static float getRandom(){
		return ((float)rand()) / RAND_MAX;
	}

	static float getRandom(float a, float b){
		float l = b - a;
		float r = getRandom();
		return a + l*r;
	}

	Quaternion qs[2][2][2];

	//x y z
	void init_static(){
		Quaternion q;


		qs[1][0][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1 ), PI3_2);
		qs[1][1][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI);
		qs[0][1][0] = Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI_2);


		qs[0][0][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI) * Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI_2);
		qs[1][0][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI) * Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI);
		qs[1][1][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI) * Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), PI3_2);
		qs[0][1][1] = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), PI);

		/*
		Vector2 p0 = Vector2(0.392699093, 1.17809737);
		Vector2 p1 = Vector2(0.285599351, 1.07992256 );
		Vector2 p2 = Vector2(0.523598790, 1.17809737);
		Vector2 p3 = Vector2(0.428399026, 1.07992256);
		Vector2 p4 = Vector2(0.405583918, 1.07992256);

		Vector2 sp = Vector2(0.405583918, 1.07992256);


		Vector3 pp0 = Tools::SphericalToXyz(p0);
		Vector3 pp1 = Tools::SphericalToXyz(p1);
		Vector3 pp2 = Tools::SphericalToXyz(p2);
		Vector3 pp4 = Tools::SphericalToXyz(p4);


		Vector3 psp = Tools::SphericalToXyz(sp);

		if (Tools::pointInTriangle(p0, p1, p2, sp)){
			printf("win 1 !!\n");
		}

		if (Tools::pointInTriangle(p1, p2, p3, sp)){
			printf("win 2 !!\n");
		}*/

		
		for (int i = 0; i < 0; i++){
			Vector3 v1 = Vector3(getRandom(-1, 1), getRandom(-1, 1), getRandom(-1, 1));
			v1.Normalize();


			Vector2 sp = Tools::normalizedXyzToSpherical(v1);
			Vector3 spp = Tools::SphericalToXyz(sp);

			//printf("%f\n", Vector3::Distance(v1, spp));

			if (getHeightAt(5, v1) < 0)
			{
				printf("i = %d ", i);
				getHeightAt(5, v1);
			}

		}
	}

	Vector3 fix(Vector3 &v){
		return Vector3::Transform(v,qs[v.x < 0][v.y < 0][v.z < 0]);
	}

	float getHeightAt(int d, Vector3 point){

		Vector3 p = fix(point);
		Vector2 sp = Tools::normalizedXyzToSpherical(p);


		float horizontal_ang = sp.x;
		float vertical_ang = sp.y;

		int row = 1 << (d - 1);

		float v_l = PI_2 / row;


		int index_v = (int)(vertical_ang / v_l);
		if (index_v == row){
			index_v = row - 1;
		}
		float top_v = (index_v)*v_l;
		float bottom_v = top_v + v_l;


		int top_p_count = index_v + 1;
		int bottom_p_count = top_p_count + 1;


		float bottom_h_l = PI_2 / (bottom_p_count - 1);


		float left_h_bottom = ((int)(horizontal_ang / bottom_h_l))*bottom_h_l;


		float left_h_top = 0.0f;
		float top_h_l = 0.0f;

		if (top_p_count > 1){
			top_h_l = PI_2 / (top_p_count - 1);
			left_h_top = ((int)(horizontal_ang / top_h_l))*top_h_l;
		}



		Vector2 p0 = Vector2(left_h_bottom, bottom_v);
		Vector2 p1 = Vector2(left_h_top, top_v);
		Vector2 p2 = Vector2(left_h_bottom + bottom_h_l, bottom_v);
		
		if (Tools::pointInTriangle(p0, p1, p2, sp)){
			//printf("win 1 !!\n");
			return 0.0f;
		}

		if (top_p_count != 1){
			Vector2 p3 = Vector2(left_h_top + top_h_l, top_v);

			if (Tools::pointInTriangle(p1, p2, p3, sp)){
				//printf("win 2 !!\n");
				return 0.0f;
			}

			Vector2 p4 = Vector2(left_h_bottom + bottom_h_l * 2, bottom_v);


			if (Tools::pointInTriangle(p2, p3, p4, sp)){
				//printf("win 3 !!\n");
				return 0.0f;
			}


			Vector2 p5 = Vector2(left_h_top - top_h_l, top_v);


			if (Tools::pointInTriangle(p5, p0, p1, sp)){
				//printf("win 4 !!\n");
				return 0.0f;
			}

			Vector2 p6 = Vector2(left_h_bottom - bottom_h_l, bottom_v);


			if (Tools::pointInTriangle(p5, p1, p6, sp)){
				//printf("win 5 !!\n");
				return 0.0f;
			}
		}
		else{



			Vector2 p5 = Vector2(left_h_top + PI2, top_v);

			if (Tools::pointInTriangle(p1, p2, p5, sp)){
				//printf("win 8 !!\n");
				return 0.0f;
			}



			Vector2 p3 = Vector2(left_h_bottom - bottom_h_l, bottom_v);


			if (Tools::pointInTriangle(p0, p1, p3, sp)){
				//printf("win 6 !!\n");
				return 0.0f;
			}


			Vector2 p4 = Vector2(left_h_bottom + bottom_h_l * 2, bottom_v);


			if (Tools::pointInTriangle(p1, p2, p4, sp)){
				//printf("win 7 !!\n");
				return 0.0f;
			}
		}


		printf("lose!! index_v = %d \n", index_v);

		return -1.0f;
	}

};

#endif