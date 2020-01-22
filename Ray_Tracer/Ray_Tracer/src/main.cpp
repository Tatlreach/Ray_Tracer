#include <iostream>
#include <fstream>
#include <time.h>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
using namespace std;
// TODO(Mike): phase in std::  over including the whole namespace

inline float zero_to_one() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

/// Generate a color vector between blue-white based on how upward the parameter is facing.
inline vec3 giveFadeBlueDownward(const ray& r) {
	// goal color is vec3(.5, .7, 1.0)	//blue
	// start is white(1,1,1)
	// r's original y val goes from -1, 1
		// +1 then *.5, to go 0-1
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f*(1.0f + unit_direction.y());

	return lerp(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.7f, 1.0f), t);
}

inline void print(vec3 in) {
	cout << "(" << in[0] << ", " << in[1] << ", " << in[2] << ")" << '\n';
	return;
}
int printCount = 41;

/// Return the color of the world from the perspective of the ray parameter
vec3 color(const ray& r, hitable *world, int reflects_left = 25) {
	hit_record rec;

	// TODO(Mike): include float.h & init this with MAXFLOAT
	// check hit & assign hit_record parameter
	if (world->hit(r, 0.001f, 20000.0f, rec)) {
		vec3 attenuation;
		ray scatter;

		// call hit_record's own material->scatter() to get attenuation & reflected_ray
		if ((reflects_left > 0) && rec.mat->scatter(r, rec, attenuation, scatter)) {

			// recursively get color() of reflected_ray & apply attenuation (^gotten in the prev step^)
			return attenuation * color(scatter, world, reflects_left - 1);
		}
		return vec3(0, 0, 0);
	} else {
		return giveFadeBlueDownward(r);
	}
}

inline hitable *default_scene() {
	hitable **list = new hitable*[4];
	list[0] = new sphere(
		vec3(0.0f, -100.5f, -1.0f),
		100.0f,
		new lambertian(vec3(0.8f, 0.8f, 0.0f))
	);

	list[1] = new sphere(
		vec3(-1.0f, 0.0f, -1.0f),
		0.5f,
		new dielectric(1.5f)
	);

	list[2] = new sphere(
		vec3(0.0f, 0.0f, -1.0f),
		0.5f,
		new lambertian(vec3(0.1f, 0.2f, 0.5f))
	);

	list[3] = new sphere(
		vec3(1.0f, 0.0f, -1.0f),
		0.5f,
		new metal(vec3(0.8f, 0.6f, 0.2f), 1.0f)
	);

	return new hitable_list(list, 4);
}


int main() {

	ofstream image;
	image.open("spheres_image.ppm");

	int width = 200;
	int height = 100;
	float fWidth = static_cast<float>(width);
	float fHeight = static_cast<float>(height);

	// camera cam;
	camera cam(vec3(-2, 2, 1), vec3(0, 0, -1), vec3(0, 1, 0), 45, fWidth / fHeight);
	// camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 90, fWidth / fHeight);
	int sample_count = 5;
	srand((unsigned int)time(NULL));

	int ir, ig, ib;

	// pixel coordinates
		// x goes from 0 to 4
		// y goes from 0 to 2
		// z is set at -1

	image << "P3\n" << width << " " << height << "\n255\n";

	float xPercent;
	float yPercent;

	hitable* world = default_scene();

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			vec3 col = vec3(0.0f, 0.0f, 0.0f);

			for (int s = 0; s < sample_count; s++) {
				// TODO(Mike): cleanly rewrite with updated float cast
				// TODO(Mike): look into rand_r() over rand()

				// Goes from (i,j) screen pixel coordinates
				// to screen percentage coordinates
				// to world vectors protruding out of the screen from camera.origin

				/// Percent = (pixel_coord + rand(0 to 1)) / screen_width
				xPercent = (static_cast<float>(j) + zero_to_one()) / fWidth;
				yPercent = (static_cast<float>(i) + zero_to_one()) / fHeight;
				ray r = cam.get_ray(xPercent, yPercent);
				col += color(r, world);
			}
			col /= sample_count;


			ir = static_cast<int>(255.99f * col[0]);
			ig = static_cast<int>(255.99f * col[1]);
			ib = static_cast<int>(255.99f * col[2]);
			image << ir << " " << ig << " " << ib << '\n';
		}
	}

	image.close();
	if (printCount < 20) {
		cin >> xPercent;
	}
	return 0;
}

