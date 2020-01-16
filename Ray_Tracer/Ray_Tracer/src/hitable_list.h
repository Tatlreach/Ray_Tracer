#pragma once
#include "hitable.h"

/// Contains a list of hitables to be checked against with hit()
class hitable_list : public hitable {
public:
	hitable **list;
	int list_size;

	hitable_list() {}
	hitable_list(hitable** l, int l_size) {
		list = l;
		list_size = l_size;
	}

	/// Calls hit() against all in the list.
	/// Writes to 'hit_record' parameter for the closest hit.
	virtual bool hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const;

	/// The author's version of hit()
	virtual bool hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const;
};

bool hitable_list::hit(const ray& r, float dist_min, float dist_max, hit_record& rec) const {
	bool has_hit = false;
	hit_record temp_rec;

	// loop through hitlist
		// find the closest hit using generated record
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit_author(r, dist_min, dist_max, temp_rec)) {
			if (!has_hit || (temp_rec.dist < rec.dist)) {
				rec = temp_rec;
			}
			has_hit = true;
		}
	}

	return has_hit;
}
bool hitable_list::hit_author(const ray& r, float dist_min, float dist_max, hit_record& rec) const {
	return hit(r, dist_min, dist_max, rec);
}

/// legacy
/// my version of iterating the hitable_list
/*
bool hitable_list::hit(const ray& r, float dist_min, float dist_max, hit_record& rec) {
	bool has_hit = false;
	float min_dist = INT_MAX;

	hit_record temp_rec;
	vec3 nullVec(vec3(0, 0, 0));
	vec3 temp_vec;
	// loop through hitlist
		// find the closest hit
	// get normal vec of hit

	for (int i = 0; i < list_size; i++) {
		if ( (temp_vec = list[i]->hit_occured(r)) != nullVec ) {

			//call hit on that specific hitable to generate a hit_record
			//compare generated temp_rec to min_dist
				//if less than, set the outgoing record to it

			list[i]->get_normal(r, temp_vec, temp_rec);
			if (!has_hit || (temp_rec.dist < rec.dist)) {
				rec = temp_rec;
				min_dist = temp_rec.dist;
			}
			has_hit = true;
		}
	}

	return has_hit;
}
*/
