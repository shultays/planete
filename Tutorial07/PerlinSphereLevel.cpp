#include "PerlinSphereLevel.h"

Quaternion PerlinSphereLevel::qs[2][2][2];

PerlinSphereLevel::PerlinSphereLevel(int level, float minHeight, float maxHeight, unsigned int seed)
{
	this->level = level;
	this->minHeight = minHeight;
	this->maxHeight = maxHeight;
	this->rotateQuaterninon = 
		Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), Tools::getRandom(-PI,PI)) * 
		Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), Tools::getRandom(-PI,PI)) * 
		Quaternion::CreateFromAxisAngle(Vector3(0, 0, 1), Tools::getRandom(-PI,PI));

	rotateQuaterninon.Inverse(rotateQuaterninonInverse);

	r.setSeed(seed);
}

float PerlinSphereLevel::getHeight(Vector3 &orig_p){
	Vector3 p = fix(orig_p);

	VertexCoordinate p0, p1, p2;
	float u, v;

	findTriangleOfVector(p, p0, p1, p2, u, v);

	int p0r = p0.vertical_coordinate * 4;
	int p1r = p1.vertical_coordinate * 4;
	int p2r = p2.vertical_coordinate * 4;
	if (orig_p.z < 0 && orig_p.x < 0){
		p0.horizontal_coordinate += p0.vertical_coordinate * 2;
		p1.horizontal_coordinate += p1.vertical_coordinate * 2;
		p2.horizontal_coordinate += p2.vertical_coordinate * 2;
	} else if (orig_p.z < 0){
		p0.horizontal_coordinate = p0.vertical_coordinate * 2 - p0.horizontal_coordinate;
		p1.horizontal_coordinate = p1.vertical_coordinate * 2 - p1.horizontal_coordinate;
		p2.horizontal_coordinate = p2.vertical_coordinate * 2 - p2.horizontal_coordinate;
	}else if (orig_p.x < 0){
		p0.horizontal_coordinate = p0r - p0.horizontal_coordinate;
		p1.horizontal_coordinate = p1r - p1.horizontal_coordinate;
		p2.horizontal_coordinate = p2r - p2.horizontal_coordinate;
	}

	if (p0.horizontal_coordinate < 0)
		p0.horizontal_coordinate += p0r;
	else if (p0.horizontal_coordinate >= p0r)
		p0.horizontal_coordinate -= p0r;

	if (p1.horizontal_coordinate < 0)
		p1.horizontal_coordinate += p1r;
	else if (p1.horizontal_coordinate >= p1r)
		p1.horizontal_coordinate -= p1r;

	if (p2.horizontal_coordinate < 0)
		p2.horizontal_coordinate += p2r;
	else if (p2.horizontal_coordinate >= p2r)
		p2.horizontal_coordinate -= p2r;

	if (orig_p.y < 0)
	{
		int total_v = (1 << level);
		p0.vertical_coordinate = total_v - p0.vertical_coordinate;
		p1.vertical_coordinate = total_v - p1.vertical_coordinate;
		p2.vertical_coordinate = total_v - p2.vertical_coordinate;
	}

	float r0 = r.randomFloat((level+1)*4*p0.vertical_coordinate + p0.horizontal_coordinate);
	float r1 = r.randomFloat((level+1)*4*p0.vertical_coordinate + p1.horizontal_coordinate);
	float r2 = r.randomFloat((level+1)*4*p0.vertical_coordinate + p2.horizontal_coordinate);

	r0 = r0*(maxHeight-minHeight) + minHeight;
	r1 = r1*(maxHeight-minHeight) + minHeight;
	r2 = r2*(maxHeight-minHeight) + minHeight;

	float m_uv = 1.0f - u - v;

	return m_uv*r0 + u*r1 + v*r2;
}


void PerlinSphereLevel::findTriangleOfVector(Vector3 &p, VertexCoordinate &output_p0, VertexCoordinate &output_p1, VertexCoordinate &output_p2, float &u, float &v)
{

	Vector2 sp = Tools::normalizedXyzToSpherical(p);

	float horizontal_ang = sp.x;
	float vertical_ang = sp.y;

	int row = 1 << (level - 1);

	float v_l = PI_2 / row;


	int index_v = (int)(vertical_ang / v_l);
	if (index_v == row){
		index_v = row - 1;
	}

	float top_v = (index_v)*v_l;
	float bottom_v = top_v + v_l;

	float top_h_l = 0.0f;

	int top_p_count = index_v + 1;
	int bottom_p_count = top_p_count + 1;
	float bottom_h_l = PI_2 / (bottom_p_count - 1);

	int bottom_h_index = (int)(horizontal_ang / bottom_h_l);

	if(index_v == 0)
	{
		sp.x *= sp.y/v_l;
	}

	Vector2 p0 = Vector2(bottom_h_index*bottom_h_l, bottom_v);
	Vector2 p1 = Vector2(bottom_h_index*top_h_l, top_v);
	Vector2 p2 = Vector2(p0.x + bottom_h_l, bottom_v);

	if (Tools::pointInTriangle(p0, p1, p2, sp, u, v)){

		output_p0.vertical_coordinate = index_v + 1;
		output_p1.vertical_coordinate = index_v;
		output_p2.vertical_coordinate = index_v + 1;

		output_p0.horizontal_coordinate = bottom_h_index;
		output_p1.horizontal_coordinate = bottom_h_index;
		output_p2.horizontal_coordinate = bottom_h_index + 1;
		//printf("0\n");
		return;
	}


	if (index_v > 0){

		float top_h_l = PI_2 / (top_p_count - 1);

		Vector2 p3 = Vector2((bottom_h_index + 1)*top_h_l, top_v);

		if (Tools::pointInTriangle(p1, p2, p3, sp, u, v)){
			output_p0.vertical_coordinate = index_v;
			output_p1.vertical_coordinate = index_v + 1;
			output_p2.vertical_coordinate = index_v;

			output_p0.horizontal_coordinate = bottom_h_index;
			output_p1.horizontal_coordinate = bottom_h_index + 1;
			output_p2.horizontal_coordinate = bottom_h_index + 1;
			//printf("1\n");
			return;
		}
		if (bottom_h_index > 0)
		{
			Vector2 p4 = Vector2((bottom_h_index - 1)*top_h_l, top_v);


			if (Tools::pointInTriangle(p4, p1, p0, sp, u, v)){
				output_p0.vertical_coordinate = index_v;
				output_p1.vertical_coordinate = index_v;
				output_p2.vertical_coordinate = index_v + 1;

				output_p0.horizontal_coordinate = bottom_h_index - 1;
				output_p1.horizontal_coordinate = bottom_h_index;
				output_p2.horizontal_coordinate = bottom_h_index;
				//printf("2\n");
				return;
			}
		}
	}
	printf("err\n");
}