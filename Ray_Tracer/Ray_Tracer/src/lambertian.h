#pragma once
#include "material.h"

class lambertian : public material {
public:
	vec3 albedo;	//reflectivity?? / color??
	lambertian(vec3 a) : albedo(a) {};
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected_end(rec.p + rec.normal + random_in_sphere() );
		scattered = ray(rec.p, reflected_end - rec.p);
		attenuation = albedo;
		return true;
	}
};