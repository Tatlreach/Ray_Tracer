#pragma once

#include "hitable.h"

class sphere : public hitable {
public:
	vec3 center;
	float radius;

	sphere() {}
	sphere(vec3 cen, float r) : center(cen), radius(r) {};

	virtual bool hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const;
//	virtual vec3 hit_occured(const ray & r) const;
//	virtual vec3 get_normal(const ray& r, vec3 perpendic, hit_record& rec) const;
};

bool sphere::hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const {
	vec3 relSphereLoc(center - r.origin());
	vec3 look(unit_vector(r.direction()));

	float dist = dot(relSphereLoc, look);

	look *= dist;
	//(look - relSphereLoc) gives us a vector perpendicular to our ray, from our sphere center
	vec3 perpendic(look - relSphereLoc);
	if (perpendic.length() > radius) {
		return false;
		//return vec3(0, 0, 0);
	}

	//how to get normal vec
		//scale look to sqrt(radius^2 - perpendic.length()^2)
		//normal = perpendic+look

	float hit_dist_from_perpendic = sqrt((radius*radius) - (perpendic.length()*perpendic.length()));
	rec.dist = dist - hit_dist_from_perpendic;	///get distance from ray origin to sphere surface

	look.make_unit_vector();
	look = (-look);
	look *= hit_dist_from_perpendic;
	rec.normal = (perpendic + look);	//not unit vector yet

	rec.p = (center + rec.normal);

	rec.normal.make_unit_vector();
	return true;
	//return (perpendic + look);	//return normal;	//return rec.normal;
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