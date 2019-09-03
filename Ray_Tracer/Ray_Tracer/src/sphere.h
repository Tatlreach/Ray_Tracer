#pragma once

#include "hitable.h"
//#include <iostream>
//#include <fstream>
class material;

class sphere : public hitable {
public:
	//std::ofstream vecLog;
	vec3 center;
	float radius;
	material* mat;

	sphere() {}
	sphere(vec3 cen, float r, material* mat_in) : center(cen), radius(r), mat(mat_in) {};

	virtual bool hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const;
	virtual bool hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const;
//	virtual vec3 hit_occured(const ray & r) const;
//	virtual vec3 get_normal(const ray& r, vec3 perpendic, hit_record& rec) const;
};

bool sphere::hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const {
	vec3 relSphereLoc(center - r.origin());
	vec3 look( unit_vector(r.direction()) );

	float dist = abs(dot(relSphereLoc, look));
	if ((dist < dist_min) || (dist > dist_max)) return false;

	look *= dist;
	//(look - relSphereLoc) gives us a vector perpendicular to our ray, from our sphere center
	vec3 perpendic(look - relSphereLoc);
	if (perpendic.length() > radius) {
		return false;
		//return vec3(0, 0, 0);
	}

	//collision debugging
	/*
	if (radius == 100.0f) {
		//printing first 50 big sphere collisions
		if (r.direction().y() < 0.5f) {
			if (((printInterval % 20) == 0) && printCount>0) {
				vecLog.open("vecLog.txt", std::ios_base::app);
				//vecLog.open("vecLog.txt");
				//print
				vecLog << "center: (" << (int)center[0] << ", " << (int)center[1] << ", " << (int)center[2] << ")\n";
				vecLog <<"ray: ("<< r.direction()[0] << ", " << r.direction()[1] << ", " << r.direction()[2] << ")\n";
				vecLog << "perpendic: (" << (int)perpendic[0] << ", " << (int)perpendic[1] << ", " << (int)perpendic[2] << ")\n";
				vecLog << "look: (" << (int)look[0] << ", " << (int)look[1] << ", " << (int)look[2] << ")\n";
				vecLog << '\n';
				vecLog.close();
				printCount--;
			}
			printInterval++;
		}
	}*/

	//how to get normal vec
		//scale look to sqrt(radius^2 - perpendic.length()^2)
		//normal = perpendic+look

	float hit_dist_from_perpendic = sqrt((radius*radius) - (perpendic.length()*perpendic.length()));

	//check in t_range
	/*
	if ((dist_min > (dist - hit_dist_from_perpendic)) || ((dist - hit_dist_from_perpendic) > dist_max) ) {
		return false;
	}*/
	rec.dist = dist - hit_dist_from_perpendic;	///get distance from ray origin to sphere surface

	look.make_unit_vector();
	look = (-look);
	look *= hit_dist_from_perpendic;
	rec.normal = (perpendic + look);	//not unit vector yet

	rec.p = (center + rec.normal);

	rec.normal.make_unit_vector();
	rec.mat = mat;
	return true;
	//return (perpendic + look);	//return normal;	//return rec.normal;
}

	///authors version of hit detection
bool sphere::hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
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