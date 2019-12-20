#pragma once
#include "material.h"

/// Determines how a reflective surface material scatters light
class metal : public material {
public:
	vec3 albedo;	/// whiteness of a surface : relfectivity of a surface
	float blur;		/// Determines how randomly light reflects off the surface

	// TODO(Mike): set a way so blur_in default value removes blur & removes blur computation
	metal(vec3 a, float blur_in=1.0f) : albedo(a){
		if (blur < 1.0f) {
			blur = blur_in;
		}
		else {
			blur = 1.0f;
		}
	};

	/// Determines the scattered light from ray r_in that hit the surface at hit_record
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect( unit_vector(ray_in.direction()), rec.normal );
		reflected += (blur*random_in_sphere());
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};