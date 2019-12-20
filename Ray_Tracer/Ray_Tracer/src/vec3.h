#pragma once
#include <math.h>

/// Stores (x, y, z) or (r, g, b) data & vector operations for that data
class vec3 {
public:
	float e[3];
	vec3() {}
	vec3(const vec3& vecIn);
	vec3(float e0, float e1, float e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	///+ left hand opperator gets the positive version
	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](const int i) const { return e[i]; }
	inline float& operator[](const int i) { return e[i]; }

	inline vec3& operator+=(const vec3& v2);
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);

	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);
	inline vec3& operator-=(const float t);
	inline vec3& operator+=(const float t);

	inline float length() {
		// return sqrt((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
		return sqrt(squared_length());
	}
	inline float squared_length() {
		return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	void make_unit_vector();

	inline void scale_to(const float len);
};

/// Reduce (*this) vector's length to 1
void vec3::make_unit_vector() {
	(*this) /= length();
	return;
}

void vec3::scale_to(const float len) {
	(*this) *= (len / length());
	return;
}

vec3::vec3(const vec3& vecIn) {
	e[0] = vecIn[0];
	e[1] = vecIn[1];
	e[2] = vecIn[2];
}

inline bool operator==(const vec3 v1, const vec3 v2) {
	return ((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2]));
}

inline bool operator!=(const vec3 v1, const vec3 v2) {
	return ((v1[0] != v2[0]) || (v1[1] != v2[1]) || (v1[2] != v2[2]));
}

inline vec3 operator/(const vec3& v, float t) {
	return vec3(v[0] / t, v[1] / t, v[2] / t);
}

/// Scale a vector's length down to 1
inline vec3 unit_vector(vec3 v) {
	return  (v / v.length());
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
	return vec3(
		v1[0] - v2[0],
		v1[1] - v2[1],
		v1[2] - v2[2]
	);
}

/// Linearly interpolate from start-to-end. Take a percentage of that.
inline vec3 lerp(const vec3& start, const vec3& end, const float percent) {
	vec3 result(end - start);
	result *= percent;
	result += start;
	return result;
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
	return vec3(
		v1[0] + v2[0],
		v1[1] + v2[1],
		v1[2] + v2[2]
	);
}

inline vec3 operator*(const vec3& v, float t) {
	return vec3(
		v[0] * t,
		v[1] * t,
		v[2] * t
	);
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
	return vec3(
		v1[0] * v2[0],
		v1[1] * v2[1],
		v1[2] * v2[2]
	);
}



/// Return the dot product of paramters
inline float dot(const vec3& v1, const vec3& v2) {
	return ((v1[1] * v2[1]) + (v1[2] * v2[2]) + (v1[0] * v2[0]));
}

/// Generate a cross product vector of paramters.
inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(
		(v1[1] * v2[2]) - (v1[2] * v2[1]),
		-(v1[0] * v2[2] - v1[2] * v2[0]),
		(v1[0] * v2[1]) - (v1[1] * v2[0]));
}

inline vec3 operator*(float t, const vec3& v1) {
	return vec3(
		t * v1[0],
		t * v1[1],
		t * v1[2]
	);
}


inline vec3 operator+(const float f, const vec3& v) {
	return vec3(
		v[0] + f,
		v[1] + f,
		v[2] + f
	);
}

inline vec3& vec3::operator+=(const vec3& v2) {
	e[0] += v2.x();
	e[1] += v2.y();
	e[2] += v2.z();
	return *this;
}

inline vec3& vec3::operator-=(const vec3& v2) {
	e[0] -= v2.x();
	e[1] -= v2.y();
	e[2] -= v2.z();
	return *this;
}

inline vec3& vec3::operator*=(const vec3& v2) {
	e[0] *= v2.x();
	e[1] *= v2.y();
	e[2] *= v2.z();
	return *this;
}

inline vec3& vec3::operator/=(const vec3& v2) {
	e[0] /= v2.x();
	e[1] /= v2.y();
	e[2] /= v2.z();
	return *this;
}

inline vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

inline vec3& vec3::operator/=(const float t) {
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}

inline vec3& vec3::operator-=(const float t) {
	e[0] -= t;
	e[1] -= t;
	e[2] -= t;
	return *this;
}

// TODO(Mike): integrate rand_r() instead of rand()
// TODO(Mike): integrate static_cast<float>() over float()
/// Generate a vector in a random direction(+ or -) with a length 0->radius_max
inline vec3 random_in_sphere(float radius_max = 1.0f) {
	vec3 rand_sphere;
	do {
		rand_sphere = vec3(
			float(rand()) / float(RAND_MAX),
			float(rand()) / float(RAND_MAX),
			float(rand()) / float(RAND_MAX)
		);
		rand_sphere -= 0.5f;
		rand_sphere *= (2.0f * radius_max);
	} while (rand_sphere.length() > radius_max);
	return rand_sphere;
}

/// Generate a vector in a random direction(+ or -) with a length 0->1
inline vec3 random_in_sphere_author() {
	vec3 rand_sphere;
	do {
		rand_sphere = vec3(
			float(rand()) / float(RAND_MAX),
			float(rand()) / float(RAND_MAX),
			float(rand()) / float(RAND_MAX)
		);
		rand_sphere *= 2.0f;
		rand_sphere -= vec3(1, 1, 1);
	} while (rand_sphere.length() > 1.0f);
	return rand_sphere;
}
