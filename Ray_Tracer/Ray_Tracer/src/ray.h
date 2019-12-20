#pragma once
#include "vec3.h"

/// Represents a vector(vec3) starting from some other place than (0,0) implicitly
class ray {
public:
	vec3 A;		/// Origin of the ray
	vec3 B;		/// Direction of the ray

	ray() {}
	ray(const vec3& Origin, const vec3& Direction) {
		A = Origin;
		B = Direction;
	}

	vec3 origin() const { return A; }
	vec3 direction() const { return B; }

	/// Temporarily scales Direction by dist & adds in Origin.
	vec3 point_at_parameter(float dist) const { return A + (dist*B); }
};
