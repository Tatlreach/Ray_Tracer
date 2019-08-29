#include <iostream>

// basic file operations
#include <fstream>
#include "sphere.h"
#include "hitable_list.h"
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

inline vec3 getSphereHitVec(ray& r, vec3& center, float radius) {

	vec3 relSphereLoc(center - r.origin());
	vec3 look( unit_vector(r.direction()) );

	float dist = dot( relSphereLoc, look );

	look *= dist;
	//(look - relSphereLoc) gives us a vector perpendicular to our ray, from our sphere center
	vec3 perpendic(look - relSphereLoc);
	if (perpendic.length() > radius) {
		return vec3(0, 0, 0);
	}

	//how to get normal vec
		//scale look to sqrt(radius^2 - perpendic.length()^2)
		//normal = perpendic+look

	dist = perpendic.length();
	look.make_unit_vector();
	look = (-look);

	look *= sqrt((radius*radius) - (dist*dist));

	return (perpendic + look);	//return normal;
}


vec3 color(const ray& r, hitable *world) {
	hit_record rec;

	vec3 col;// = getSphereHitVec(r, sphereLoc, 0.5f);
	if (world->hit(r, 0.0, 2000.0, rec)) {		//TODO: include float.h & init this with MAXFLOAT
		col = 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
		//or nothing, comment this entire else out
		return col;
	}
	else {
		col = giveFadeBlueDownward(r);
	}
	return col;
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

	int ir, ig, ib;

	///give background fade white to blue upward

	//pixel coordinates
		//x goes from 0 to 4
		//y goes from 0 to 2
		//z is set at -1
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	image << "P3\n" << width << " " << height << "\n255\n";

	float xPercent;
	float yPercent;

	hitable *list[2];
	list[1] = new sphere(vec3(0, 0.0f, -1), 0.5f);
	list[0] = new sphere(vec3(0, -100.5f, -1), 100.0f);
	//list[1] = new sphere(vec3(0.5, 0.0f, -1), 0.5f);

	hitable* world = new hitable_list(list, 2);

	vec3 sphereLoc(0.0f, 0.0f, -1.0f);

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			xPercent = float(j) / fWidth;
			yPercent = float(i) / fHeight;
			
			ray r(origin, lower_left_corner + (xPercent*horizontal) + (yPercent*vertical));

			vec3 col = color(r, world);

			ir = int(255.99f * col[0]);
			ig = int(255.99f * col[1]);
			ib = int(255.99f * col[2]);
			if (printCount > 0) {
				//cout << ir << " " << ig << " " << ib << '\n';
				printCount--;
			}
			image << ir << " " << ig << " " << ib << '\n';
		}
	}

	image.close();
	if (printCount < 20) {
		cin >> xPercent;
	}
	cin >> xPercent;
	return 0;
}

