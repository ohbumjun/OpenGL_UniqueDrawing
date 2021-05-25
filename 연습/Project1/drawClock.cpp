#include "cg.h"
#include "drawClock.h"
#include "draw.h"
#include "vec.h"



// 2d drawing 
void drawClock(Clock2D Clock2d)
{
	glClear(GL_COLOR_BUFFER_BIT);
	float radius = 0.3;

	// 배경 시계
	glColor3f(1, 1, 1);
	circle(Clock2d.clock_center, radius);

	// 12시
	glColor3f(0, 0, 0);
	vector3D twelve_top = vector3D(Clock2d.clock_center.x, Clock2d.clock_center.y + radius, 0);
	vector3D twelve_down = vector3D(Clock2d.clock_center.x, Clock2d.clock_center.y + radius * 0.9, 0);
	line(twelve_top, twelve_down);
	// 3시
	vector3D three_left = vector3D(Clock2d.clock_center.x - radius, Clock2d.clock_center.y, 0);
	vector3D three_right = vector3D(Clock2d.clock_center.x - radius * 0.9, Clock2d.clock_center.y, 0);
	line(three_left, three_right);
	// 6시
	vector3D six_down = vector3D(Clock2d.clock_center.x, Clock2d.clock_center.y - radius, 0);
	vector3D six_up = vector3D(Clock2d.clock_center.x, Clock2d.clock_center.y - radius * 0.9, 0);
	line(six_down, six_up);
	// 9시
	vector3D nine_left = vector3D(Clock2d.clock_center.x + radius * 0.9, 0, 0);
	vector3D nine_right = vector3D(Clock2d.clock_center.x + radius, 0, 0);
	line(nine_left, nine_right);

	// 2개 축 세팅 
	glPushMatrix();

	vector3D small_end = vector3D(Clock2d.clock_center.x, Clock2d.clock_center.y + radius * 0.3, 0);
	glLineWidth(10);
	glRotatef(-Clock2d.clock_rotate_angle, Clock2d.clock_center.x, Clock2d.clock_center.y, 1);
	glColor3f(
		Clock2d.clock_smalltick_color[0],
		Clock2d.clock_smalltick_color[1],
		Clock2d.clock_smalltick_color[2]
	);
	glBegin(GL_LINES);
	glVertex3f(Clock2d.clock_center.x, Clock2d.clock_center.y, 0);
	glVertex3f(small_end.x, small_end.y, 0);
	glEnd();
	line(0, small_end);
	glLineWidth(1);

	vector3D big_end = vector3D(Clock2d.clock_center.x, Clock2d.clock_center.y + radius * 0.6, 0);
	glLineWidth(10);
	glRotatef(-Clock2d.clock_rotate_angle * 1.1, Clock2d.clock_center.x, Clock2d.clock_center.y, 1);
	glColor3f(
		Clock2d.clock_bigtick_color[0],
		Clock2d.clock_bigtick_color[1],
		Clock2d.clock_bigtick_color[2]
	);
	glBegin(GL_LINES);
	glVertex3f(Clock2d.clock_center.x, Clock2d.clock_center.y, 0);
	glVertex3f(big_end.x, big_end.y, 0);
	glEnd();
	glLineWidth(1);
	glRotatef(0, 0, 0, 1);

	glPopMatrix();

	// cout << "clock rotate angle" << clock_rotate_angle << endl;
}

