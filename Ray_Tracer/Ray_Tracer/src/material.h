#pragma once
#include "hitable.h"
// #include "ray.h"

/// Generates a vector that perfectly reflected of a surface(normal)
vec3 reflect(const vec3& reflected, const vec3& normal) {
	return reflected - 2*(dot(reflected, normal)*normal);
}

/// Determines how light interacts with a surface
class material {
public:
	/// Determines the scattered light from ray r_in that hit the surface at hit_record
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

