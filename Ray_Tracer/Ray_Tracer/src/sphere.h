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
	return true;

	//how to get normal vec
		//scale look to sqrt(radius^2 - perpendic.length()^2)
		//normal = perpendic+look

	dist = perpendic.length();
	look.make_unit_vector();
	look = (-look);

	look *= sqrt((radius*radius) - (dist*dist));
	rec.p = (perpendic + look)+relSphereLoc+r.origin;
	//return (perpendic + look);	//return normal;
}