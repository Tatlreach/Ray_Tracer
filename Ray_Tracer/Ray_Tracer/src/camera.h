#pragma once
#include "ray.h"

class camera {
public:
	vec3 lower_left_corner;
	vec3 screen_width;		/// width_scaler
	vec3 screen_height;		/// height_scaler
	vec3 origin;

	camera() {
		lower_left_corner = vec3(-2.0f, -1.0f, 1.0);
		screen_width = vec3(4.0f, 0.0f, 0.0f);
		screen_height = vec3(0.0f, 2.0f, 0.0f);
		origin = vec3(0.0f, 0.0f, 0.0f);
	}

	/// given x,y coordinate of screen in percentages
	/// returns a ray protruding from the camera
	ray get_ray(const float screen_x_percent, const float screen_y_percent) {
		vec3 direction = lower_left_corner;
		direction += (screen_x_percent * screen_width);
		direction += (screen_y_percent * screen_height);

		return ray(origin, direction);
	}
};
