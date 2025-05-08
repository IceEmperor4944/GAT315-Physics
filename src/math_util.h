#pragma once
#include "raymath.h"

float randf() {
	return rand() / (float)RAND_MAX;
}

float randf(int max) {
	return randf() * max;
}

float DegToRad(float degrees) {
	return degrees * (PI / 180);
}

float RadToDeg(float radians) {
	return radians * (180 / PI);
}