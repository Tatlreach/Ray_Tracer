#pragma once
#include "hitable.h"
//#include "ray.h"

vec3 reflect(const vec3& reflected, const vec3& normal) {
	return reflected - 2*(dot(reflected, normal)*normal);
}

class material {
public:
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

