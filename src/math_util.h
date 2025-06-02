#pragma once
#include "raylib.h"
#include <cstdlib>
#include <algorithm>

inline float randf() {
	return rand() / (float)RAND_MAX;
}

inline float randf(int min, int max) {
	if (min > max) std::swap(min, max);
	return min + ((max - min) * randf());
}

inline float randf(int max) {
	return randf(0, max);
}

inline float DegToRad(float degrees) {
	return degrees * (PI / 180);
}

inline float RadToDeg(float radians) {
	return radians * (180 / PI);
}

inline Vector2 randomOnUnitCircle() {
	float theta = randf(0, 2 * PI);
	return { cosf(theta), sinf(theta) };
}