#include "cg.h"
#include "draw.h"
#include "vec.h"
#include <cmath>
#include<iostream>

struct Robot
{
	int rightarm_z_angle_upper = -45;
	int rightarm_y_angle_upper = -45;
	int rightarm_angle_low = -45;

	int rightleg_z_angle_upper = -90;
	int rightleg_x_angle_upper = 45;
	int rightleg_angle_low = 30;

	int leftarm_z_angle_upper = 45;
	int leftarm_y_angle_upper = -45;
	int leftarm_angle_low = 45;

	int leftleg_z_angle_upper = 90;
	int leftleg_x_angle_upper = -45;
	int leftleg_angle_low = 30;

	int dir_arm_left_upper = 1;
	int dir_arm_right_upper = 1;
	int dir_leg_left_upper = 1;
	int dir_leg_right_upper = 1;
	int dir_low = 4;

	bool robot_anim_on = true;
	vector3D robot_color = vector3D(1, 1, 1);
};

void drawAxis();
void drawXAxis();
void drawSimpleDrawing(vector3D a, vector3D b, vector3D color);
void drawCube();
void drawCuboid(GLfloat sx, GLfloat sy, GLfloat sz);
// ÆÈ 
void drawUpperLeftArm(GLfloat z_angle, GLfloat y_angle);
void drawUpperRightArm(GLfloat z_angle, GLfloat y_angle);
void drawLowerRightArm(GLfloat angle);
void drawLowerLeftArm(GLfloat angle);
void drawLowerRightLeg(GLfloat angle);
void drawLowerLeftLeg(GLfloat angle);
void drawRightHand();
void drawLeftHand();
// ´Ù¸®
void drawUpperRightLeg(GLfloat z_angle, GLfloat x_angle);
void drawUpperLeftLeg(GLfloat z_angle, GLfloat x_angle);
// ¸öÅë 
void drawBody();
void drawFinger();
void drawFinger2();
// ¸Ó¸®
void drawHead();