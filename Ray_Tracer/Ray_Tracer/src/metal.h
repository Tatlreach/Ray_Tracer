#pragma once
#include "material.h"

class metal : public material {
public:
	vec3 albedo;
	float blur;

	// TODO(Mike): set a way so blur_in default value removes blur & removes blur computation
	metal(vec3 a, float blur_in=1.0f) : albedo(a){
		if (blur < 1.0f) {
			blur = blur_in;
		}
		else {
			blur = 1.0f;
		}
	};
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect( unit_vector(ray_in.direction()), rec.normal );
		reflected += (blur*random_in_sphere());
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};