#include <iostream>

// basic file operations
#include <fstream>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include <time.h>
#include "lambertian.h"
#include "metal.h"
using namespace std;

inline vec3 giveFadeBlueDownward(const ray& r) {
	//goal color is vec3(.5, .7, 1.0)	//blue
	//start is white(1,1,1)
	//r's original y val goes from -1, 1
		//+1 then *.5, to go 0-1
	vec3 unit_direction = unit_vector( r.direction() );
	float t = 0.5f*(1.0f + unit_direction.y());

	return lerp(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 0.7f, 1.0f), t);
}

inline void print(vec3 in) {
	cout << "("<<in[0] << ", " << in[1] << ", " << in[2] <<")"<< '\n';
	return;
}
int printCount = 41;


vec3 color(const ray& r, hitable *world) {
	hit_record rec;

	if (world->hit(r, 0.001, 20000.0, rec)) {		//TODO: include float.h & init this with MAXFLOAT
		
		//target = 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
		vec3 reflected_end( rec.p + rec.normal + random_in_sphere() );
		//.5 is the absorbtion level
		return 0.5*color( ray( rec.p, reflected_end-rec.p), world);
	}
	else {
		return giveFadeBlueDownward(r);
	}
}


int main() {

	//collision debugging
	/*
	vec3 center(0, -100, -1);
	ray r(vec3(0,0,0), vec3(-2, 0.48, -1));
	vec3 perpendic(18, 96, 10);
	//vec3 look(18, -4, 9);
	vec3 look(unit_vector(r.direction()));

	float dist = abs(dot(center, look));
	
	cout << "dist: " << dist << '\n';

	look *= dist;
	cout << "look: ";
	print(look);
	//(look - relSphereLoc) gives us a vector perpendicular to our ray, from our sphere center
	perpendic=(look - center);
	if (perpendic.length() < 100.0f) {
		cout << "HIT!" << '\n';
		//return vec3(0, 0, 0);
	}
	*/

	ofstream image;
	image.open("testPPM.ppm");

	int width = 200;
	int height = 100;
	float fWidth = float(width);
	float fHeight = float(height);

	camera view;
	int sample_count = 64;
	srand((unsigned int)time(NULL));

	int ir, ig, ib;

	///give background fade white to blue upward

	//pixel coordinates
		//x goes from 0 to 4
		//y goes from 0 to 2
		//z is set at -1

	image << "P3\n" << width << " " << height << "\n255\n";

	float xPercent;
	float yPercent;

	hitable *list[4];
	list[0] = new sphere( vec3(0, 0.0f, -1), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f)) );
	list[1] = new sphere( vec3(0, -100.5f, -1), 100.0f, new lambertian(vec3(0.8f, 0.8f, 0.0f)) );

	list[2] = new sphere(vec3(1, 0, -1), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f)));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5f, new metal(vec3(0.8f, 0.8f, 0.8f)));
	hitable* world = new hitable_list(list, 4);

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			vec3 col = vec3(0, 0, 0);
			for (int s = 0; s < sample_count; s++) {
				xPercent = (float(j) + float(rand())/float(RAND_MAX) ) / fWidth;
				yPercent = (float(i) + float(rand())/float(RAND_MAX) ) / fHeight;
				//xPercent = (float(j) + dist(e2)) / fWidth;
				//yPercent = (float(i) + dist(e2)) / fHeight;

				//xPercent = (float(j)) / fWidth;
				//yPercent = (float(i)) / fHeight;
				ray r = view.get_ray(xPercent, yPercent);
				col += color(r, world);
			}
			col /= sample_count;


			ir = int(255.99f * col[0]);
			ig = int(255.99f * col[1]);
			ib = int(255.99f * col[2]);
			image << ir << " " << ig << " " << ib << '\n';
		}
	}

	image.close();
	if (printCount < 20) {
		cin >> xPercent;
	}
	return 0;
}

