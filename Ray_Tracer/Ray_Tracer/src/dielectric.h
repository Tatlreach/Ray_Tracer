#pragma once
#include "material.h"

// TODO(Mike): document schlick
/// Determines how reflective a surface is at wide angles
/// e.g. when looking at a window at a wide angle it becomes mirror-like
float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

/// Describes how light vectors change when passing through a clear material
/// return:  whether the light is completely reflected
bool refract_author(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt*(1.0f - (dt * dt));
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - (n * dt)) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

/// Determines how light passes through & relfects off a semi-clear material
class dielectric : public material {
public:
	float ref_idx;

	// TODO(Mike): set a way so blur_in default value removes blur & removes blur computation
	dielectric(float ref_idx_in) : ref_idx(ref_idx_in) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		float reflect_prob;
		float cosine;
		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
		} else {
			outward_normal = rec.normal;
			ni_over_nt = (1.0f / ref_idx);
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}

		if (refract_author(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, ref_idx);
		} else {
			scattered = ray(rec.p, reflected);
			return true;
			// reflect_prob = 1.0f;
		}

		if ((float(rand()) / float(RAND_MAX)) < reflect_prob) {
			scattered = ray(rec.p, reflected);
		} else {
			scattered = ray(rec.p, refracted);
		}

		return true;
	}
};
