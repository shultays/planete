#pragma once

#ifndef PERLIN_SPHERE_H
#define PERLIN_SPHERE_H

#include "stdlib.h"

#include <directxmath.h>
#include <vector>
#include "SimpleMath.h"
#include "Sphere.h"
#include "Tools.h"
#include "PerlinSphereLevel.h"

using namespace DirectX;
using namespace SimpleMath;

class PerlinSphere{
	PerlinSphereLevel *levels[5];

public:
	PerlinSphere();
	float getHeight(Vector3 &p);
};

#endif