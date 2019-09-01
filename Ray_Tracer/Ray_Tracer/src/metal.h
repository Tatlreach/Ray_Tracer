#pragma once
#include "material.h"

class metal : public material {
public:
	vec3 albedo;
	metal(vec3 a) : albedo(a) {};
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect( unit_vector(ray_in.direction()), rec.normal );
		reflected += random_in_sphere(0.2f);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};