#pragma once
#include "cg.h"
#include "draw.h"
#include <cmath>
#include <iostream>
class Clock2D {
public:
	float clock_rotate_angle = 0.0;
	bool clock_anim_on = true;
	vector3D clock_center = vector3D(0, 0, 0);
	vector3D clock_bigtick_color = vector3D(0.8, 0.8, 0.8);
	vector3D clock_smalltick_color = vector3D(0.9, 0.9, 0.9);
};
void drawClock(Clock2D Clock2d);