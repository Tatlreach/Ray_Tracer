#include <iostream>

// basic file operations
#include <fstream>
#include "ray.h"
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
	cout << in[0] << " " << in[1] << " " << in[2] << '\n';
	return;
}
int printCount = 20;

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


void testVecFuncs() {
	vec3 temp(1, 1, 1);

}

int main() {
	/*
	ofstream myImageFile;
	myImageFile.open("example.txt");
	myImageFile << "Writing this to a file.\n";
	myImageFile.close();
	*/

	ofstream image;
	image.open("testPPM.ppm");

	int width = 200;
	int height = 100;
	float fWidth = float(width);
	float fHeight = float(height);

	int ir, ig, ib;

	///give background fade white to blue upward

	//our coordinate system plane of pixels
	//x goes from -2 to 2
	//y goes from -1 to 1
	//z is set at -1
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	image << "P3\n" << width << " " << height << "\n255\n";

	float xPercent;
	float yPercent;

	vec3 sphereLoc(0.0f, 0.0f, -1.0f);

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			xPercent = float(j) / fWidth;
			yPercent = float(i) / fHeight;
			
			ray r(origin, lower_left_corner + (xPercent * horizontal) + (yPercent * vertical));
			vec3 col = getSphereHitVec(r, sphereLoc, 0.5f);
			if (col == vec3(0,0,0)) {
				col = giveFadeBlueDownward(r);
			}
			else {
				vec3 N = unit_vector(r.point_at_param(col.length()) - sphereLoc);
				col = 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
				//or nothing, comment this entire else out
			}
			ir = int(255.99f * col[0]);
			ig = int(255.99f * col[1]);
			ib = int(255.99f * col[2]);
			image << ir << " " << ig << " " << ib << '\n';
		}
	}

	/*
	float r, g, b;
	b = 0.2f;

	
	///loop through colors, write to file

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			ir = int(255.99 * (float(j) / wFloat));
			ig = int(255.99 * (float(i) / hFloat));
			ib = int(255.99 * b);
			image << ir << " " << ig << " " << ib << '\n';
		}
	}
	*/

	/*
	for (int i = height-1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			ir = int(255.99 * (float(j) / wFloat));
			ig = int(255.99 * (float(i) / hFloat));
			ib = int(255.99 * b);
			image << ir << " " << ig << " " << ib << '\n';
		}
	}
	*/
	/*
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			float r = float(i) / float(width);
			float g = float(j) / float(height);
			float b = 0.2f;

			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			image << ir << " " << ig << " " << ib << '\n';

		}
	}
	*/
	image.close();
	if (printCount < 20) {
		cin >> xPercent;
	}
	return 0;
}

