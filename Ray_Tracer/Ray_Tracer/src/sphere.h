#pragma once

#include "hitable.h"

// used for debugging
// #include <iostream>
// #include <fstream>

class material;

class sphere : public hitable {
public:
	// std::ofstream vecLog;
	vec3 center;
	float radius;
	material* mat;

	sphere() {}
	sphere(vec3 cen, float r, material* mat_in) : center(cen), radius(r), mat(mat_in) {}

	virtual bool hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const;
	virtual bool hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const;

	// virtual vec3 hit_occured(const ray & r) const;
	// virtual vec3 get_normal(const ray& r, vec3 perpendic, hit_record& rec) const;
};

bool sphere::hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const {
	vec3 relSphereLoc(center - r.origin());
	vec3 look(r.direction());

	float dist = abs(dot(relSphereLoc, look));
	if ((dist < dist_min) || (dist > dist_max)) return false;

	look.scale_to(dist);
	// (look - relSphereLoc) gives us a vector perpendicular to our ray, from our sphere center
	vec3 perpendic(look - relSphereLoc);
	float perpendic_len = perpendic.length();
	if (perpendic_len > radius) {
		return false;
		// return vec3(0, 0, 0);
	}
	
	bool is_inside = (relSphereLoc.length() < radius);

	float surface_dist_from_perpendic = sqrt((radius * radius) - (perpendic_len * perpendic_len));
	
	/// get distance from ray origin to sphere surface
	rec.dist = dist + (float(is_inside * -1)*surface_dist_from_perpendic);
	// TODO(Mike): if within sphere rec.dist = dist + hit_dist_from_perpendic?

	look.scale_to(surface_dist_from_perpendic * static_cast<float>(is_inside * -1));

	rec.normal = (perpendic + look);	// not unit vector yet

	rec.p = (center + rec.normal);

	rec.normal.make_unit_vector();
	rec.mat = mat;
	return true;
	// return (perpendic + look);	//return normal;	//return rec.normal;
}

	/// authors version of hit detection
bool sphere::hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - (radius * radius);
	float discriminant = (b * b) - (a * c);
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		rec.mat = mat;
		if (temp < dist_max && temp > dist_min) {
			rec.dist = temp;
			rec.p = r.point_at_parameter(rec.dist);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < dist_max && temp > dist_min) {
			rec.dist = temp;
			rec.p = r.point_at_parameter(rec.dist);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}

/*
vec3 sphere::hit_occured(const ray& r) const {
	vec3 relSphereLoc(center - r.origin());
	vec3 look(unit_vector(r.direction()));

	float dist = dot(relSphereLoc, look);

	look *= dist;
	//(look - relSphereLoc) gives us a vector perpendicular to our ray, from our sphere center
	vec3 perpendic(look - relSphereLoc);
	
	if (perpendic.length() > radius) {
		return vec3(0, 0, 0);
	}
	return perpendic;
}

inline vec3 sphere::get_normal(const ray & r, vec3 perpendic, hit_record & rec) const
{
	vec3 relSphereLoc(center - r.origin());
	float dist = perpendic.length();
	vec3 look( unit_vector(r.direction) );
	look = (-look);

	look *= sqrt((radius*radius) - (dist*dist));
	rec.p = (perpendic + look) + relSphereLoc + r.origin;

	return vec3();
}
*/
