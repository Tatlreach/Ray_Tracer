#pragma once

#include "ray.h"
class material;

// TODO(Mike): consider moving hit_record to it's own .h
struct hit_record {
public:
	float dist;		/// direction distance : dist from origin to sphere surface
	vec3 p;			/// coordinate of collision
	vec3 normal;
	material *mat;
};

class hitable {
public:
	virtual bool hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const = 0;
	virtual bool hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const = 0;

	// depreciated functions
	// virtual vec3 hit_occured(const ray& r) const = 0;
	// virtual vec3 get_normal(const ray& r, vec3 perpendic, hit_record& rec) const = 0;
};
