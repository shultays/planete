#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include <directxmath.h>
#include <vector>
#include "SimpleMath.h"

using namespace DirectX;
using namespace SimpleMath;

class Sphere{

	static void build_int(int d, Vector3  p1, Vector3  p2, Vector3  p3, std::vector<Vector3> &out){

		if (d == 1){
			out.push_back(p1);
			out.push_back(p2);
			out.push_back(p3);
		}
		else
		{
			Vector3 p12 = (p1 + p2) / 2;
			Vector3 p13 = (p1 + p3) / 2;
			Vector3 p23 = (p2 + p3) / 2;

			p12 *= 1 / p12.Length();
			p13 *= 1 / p13.Length();
			p23 *= 1 / p23.Length();

			d--;

			build_int(d, p1, p12, p13, out);
			build_int(d, p12, p2, p23, out);
			build_int(d, p13, p23, p3, out);
			build_int(d, p12, p23, p13, out);
		}
	}


	static void build_int(int d, int  p1, int  p2, int  p3, std::vector<Vector3>  &out_vertex, std::vector<int> &out_index, int print = 0){

		if (d == 1){
			out_index.push_back(p1);
			out_index.push_back(p2);
			out_index.push_back(p3);

		}
		else
		{
			Vector3 vp12 = (out_vertex[p1] + out_vertex[p2]) / 2;
			Vector3 vp13 = (out_vertex[p1] + out_vertex[p3]) / 2;
			Vector3 vp23 = (out_vertex[p2] + out_vertex[p3]) / 2;

			vp12 *= 1 / vp12.Length();
			vp13 *= 1 / vp23.Length();
			vp23 *= 1 / vp23.Length();

			int p12 = -1;
			int p13 = -1;
			int p23 = -1;

			for (int i = 0; i < out_vertex.size(); i++){
				if (Vector3::DistanceSquared(out_vertex[i], vp12) <= FLT_EPSILON){
					p12 = i;
				}
				if (Vector3::DistanceSquared(out_vertex[i], vp13) <= FLT_EPSILON){
					p13 = i;
				}
				if (Vector3::DistanceSquared(out_vertex[i], vp23) <= FLT_EPSILON){
					p23 = i;
				}
			}

			if (p12 == -1){
				p12 = out_vertex.size();
				out_vertex.push_back(vp12);
			}
			if (p13 == -1){
				p13 = out_vertex.size();
				out_vertex.push_back(vp13);
			}
			if (p23 == -1){
				p23 = out_vertex.size();
				out_vertex.push_back(vp23);
			}

			d--;

			build_int(d, p1, p12, p13, out_vertex, out_index, print);
			build_int(d, p12, p2, p23, out_vertex, out_index, print);
			build_int(d, p13, p23, p3, out_vertex, out_index, print);
			build_int(d, p12, p23, p13, out_vertex, out_index, print);
		}
	}


public:
	static void build(int d, std::vector<Vector3>  &out){
		build_int(d, Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1), out);
		build_int(d, Vector3(0, 1, 0), Vector3(-1, 0, 0),  Vector3(0, 0, 1), out);

		build_int(d, Vector3(0, -1, 0), Vector3(1, 0, 0), Vector3(0, 0, 1), out);
		build_int(d, Vector3(-1, 0, 0), Vector3(0, -1, 0), Vector3(0, 0, 1), out);

		build_int(d, Vector3(1, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0), out);
		build_int(d, Vector3(-1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, -1), out);
		build_int(d, Vector3(1, 0, 0), Vector3(0, -1, 0), Vector3(0, 0, -1), out);
		build_int(d, Vector3(-1, 0, 0), Vector3(0, 0, -1),Vector3(0, -1, 0),  out);
	}

	static void build(int d, std::vector<Vector3>  &out_vertex, std::vector<int> &out_index){
		out_vertex.push_back(Vector3(1, 0, 0)); //0
		out_vertex.push_back(Vector3(0, 1, 0)); //1
		out_vertex.push_back(Vector3(0, 0, 1)); //2

		out_vertex.push_back(Vector3(-1, 0, 0)); //3
		out_vertex.push_back(Vector3(0, -1, 0)); //4
		out_vertex.push_back(Vector3(0, 0, -1)); //5



		build_int(d, 0, 1, 2, out_vertex, out_index);
		build_int(d, 1, 3, 2, out_vertex, out_index);

		build_int(d, 4, 0, 2, out_vertex, out_index);
		build_int(d, 3, 4, 2, out_vertex, out_index);

		build_int(d, 0, 5, 1, out_vertex, out_index);
		build_int(d, 3, 1, 5, out_vertex, out_index);
		build_int(d, 0, 4, 5, out_vertex, out_index);
		build_int(d, 3, 5, 4, out_vertex, out_index);
	}

	std::vector<Vector3>  vertex;
	std::vector<int> index;

	void init(int d){
		build(d, vertex);
	}

	void initWithIndex(int d){
		build(d, vertex, index);
	}

	void randomize(float min, float max){
		for (int i = 0; i < vertex.size(); i++){
			vertex[i].x = min + (max - min)*(((float)rand()) / RAND_MAX);
			vertex[i].y = min + (max - min)*(((float)rand()) / RAND_MAX);
			vertex[i].z = min + (max - min)*(((float)rand()) / RAND_MAX);
		}
	}

	float getHeightAt(Vector3 v)
	{

			return 0;
	}
};

#endif