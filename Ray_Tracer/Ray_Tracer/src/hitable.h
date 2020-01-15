#pragma once

#include "ray.h"
class material;

// TODO(Mike): consider moving hit_record to it's own .h
/// Stores data pertaining to the collision of a light vector
struct hit_record {
public:
	float dist;		/// from ray_origin to p (hit_coordinate)
	vec3 p;			/// coordinate of collision
	vec3 normal;	/// normal vector of object surface (at collision point)
	material *mat;	/// uses above data to generate a color
};

/// Contains pure virtual function's to check if a vector collides with the object
class hitable {
public:
	/// Returns whether or not a collision occured.
	/// If it did, writes a hit_record to "rec" parameter.
	virtual bool hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const = 0;

	/// the author's version of the hit() function
	virtual bool hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const = 0;
};
