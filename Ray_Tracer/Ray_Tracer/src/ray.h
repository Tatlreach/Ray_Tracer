#pragma once
#include "vec3.h"

class ray {

public:
	vec3 A;
	vec3 B;

	ray() {}
	ray(const vec3& Origin, const vec3& Direction) {
		A = Origin;
		B = Direction;
	}

	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_param(float t) const { return A + (t*B); }
};