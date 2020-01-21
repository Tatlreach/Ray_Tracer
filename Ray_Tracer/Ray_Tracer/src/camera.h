#pragma once
#include "ray.h"

#define Pi 3.14159f

class camera {
public:
	vec3 lower_left_corner;
	vec3 screen_width;		/// width_scaler
	vec3 screen_height;		/// height_scaler
	vec3 origin;
	 
	/// default camera positions
	camera() {
		lower_left_corner = vec3(-2.0f, -1.0f, 1.0);
		screen_width = vec3(4.0f, 0.0f, 0.0f);
		screen_height = vec3(0.0f, 2.0f, 0.0f);
		origin = vec3(0.0f, 0.0f, 0.0f);
	}

	/// allows for customizable camera position & orientation
	camera(vec3 lookfrom, vec3 lookdir, vec3 vup, float vfov, float aspect) {
		// vfov: is top to bottom in degrees
		vec3 u, v, w;
		float theta = vfov * (Pi / 180.0f);
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookdir);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = vec3(-half_width, -half_height, -1.0);
		lower_left_corner = origin - (half_width*u) - (half_height*v) - w;
		screen_width = 2 * half_width * u;
		screen_height = 2 * half_height * v;
	}

	/// given x,y coordinate of screen in percentages
	/// returns a ray protruding from the camera
	ray get_ray(const float screen_x_percent, const float screen_y_percent) {
		vec3 direction = lower_left_corner;
		direction += (screen_x_percent * screen_width);
		direction += (screen_y_percent * screen_height);
		direction -= origin;

		return ray(origin, direction);
	}
};
