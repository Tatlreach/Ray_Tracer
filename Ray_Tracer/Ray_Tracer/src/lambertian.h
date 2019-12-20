#pragma once
#include "material.h"

/// Determines how a matte colored material scatters light
class lambertian : public material {
public:
	vec3 albedo;	/// whiteness of a surface : relfectivity of a surface
	lambertian(vec3 a) : albedo(a) {}

	/// Determines the scattered light from ray r_in that hit the surface at hit_record
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected_end(rec.p + rec.normal + random_in_sphere() );
		scattered = ray(rec.p, reflected_end - rec.p);
		attenuation = albedo;
		return true;
	}
};
