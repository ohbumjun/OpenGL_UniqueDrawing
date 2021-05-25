#include "cg.h"
#include "vec.h"

void rect(vector3D a, vector3D b)
/*
*  a : 왼쪽 위 코너
*  b : 오른쪽 아래 코너
*/
{
	glBegin(GL_POLYGON);
	glVertex3f(a.x, a.y, 0);
	glVertex3f(b.x, a.y, 0);
	glVertex3f(b.x, b.y, 0);
	glVertex3f(a.x, b.y, 0);
	glEnd();
}

void circle(vector3D center, float radius)
{
	float x, y;
	glBegin(GL_POLYGON);
	// 마지막 증감분 f += M_PI / 36.0 : 얼마나 세세하게 점을 찍을 것인가 
	// M_PI : 3.14 = 파이 --> 2*파이 : 360 도에 해당한다

	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 36.0) // 36.0 으로 나눈다는 것은 10씩 증가시킨다 
	{
		// 원을 나타내는 수식 : x^2  + y^2 = r^2
		// parametric 형식 : X = r * cos (f) -> f: 각도 ( 0 ~ 360 )
		// parametric 형식 : Y = r * sin (f) -> f: 각도 
		x = center.x + radius * cos(f);
		y = center.y + radius * sin(f);
		glVertex3f(x, y,0); // 원위를 지나가는 점 하나하나를 명시하는 것이다 
	}
	glEnd();
}

void ellipse(vector3D center, float width, float height) // 원 
{
	float x, y;

	glBegin(GL_POLYGON);
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 36.0)
	{
		x = center.x + width * cos(f);  // 반지름 대신에 width
		y = center.y + height * sin(f); // 반지름 대신에 height
		glVertex3f(x, y,0);
	}
	glEnd();
}

void triangle(vector3D a, vector3D b, vector3D c)
{
	glBegin(GL_TRIANGLES);
	glVertex3f(a[0], a[1], 0);
	glVertex3f(b[0], b[1], 0);
	glVertex3f(c[0], c[1], 0);
	glEnd();
}

void line(vector3D a, vector3D b)
{
	glBegin(GL_LINES);
	glVertex3f(a[0], a[1], 0);
	glVertex3f(b[0], b[1], 0);
	glEnd();
}

void threeline(vector3D a, vector3D b, vector3D c, vector3D d)
{
	glBegin(GL_LINES);
		glVertex3f(a[0], a[1], 0);
		glVertex3f(b[0], b[1], 0);

		glVertex3f(b[0], b[1], 0);
		glVertex3f(c[0], c[1], 0);

		glVertex3f(c[0], c[1], 0);
		glVertex3f(d[0], d[1], 0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3f(d[0], d[1], 0);
		glVertex3f(d[0]-0.05,d[1]+0.05,0);
		glVertex3f(d[0]+0.05,d[1]+0.05,0);
	glEnd();
}