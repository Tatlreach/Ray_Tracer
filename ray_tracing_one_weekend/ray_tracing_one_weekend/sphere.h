#pragma once

#include "hitable.h"

class sphere : public hitable {
public:
	vec3 center;
	float radius;

	sphere() {}
	sphere(vec3 cen, float r) : center(cen), radius(r) {};

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {

}