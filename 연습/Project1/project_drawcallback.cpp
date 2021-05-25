#include "cg.h"
#include "vec.h"

void rect(vector3D a, vector3D b)
/*
*  a : ���� �� �ڳ�
*  b : ������ �Ʒ� �ڳ�
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
	// ������ ������ f += M_PI / 36.0 : �󸶳� �����ϰ� ���� ���� ���ΰ� 
	// M_PI : 3.14 = ���� --> 2*���� : 360 ���� �ش��Ѵ�

	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 36.0) // 36.0 ���� �����ٴ� ���� 10�� ������Ų�� 
	{
		// ���� ��Ÿ���� ���� : x^2  + y^2 = r^2
		// parametric ���� : X = r * cos (f) -> f: ���� ( 0 ~ 360 )
		// parametric ���� : Y = r * sin (f) -> f: ���� 
		x = center.x + radius * cos(f);
		y = center.y + radius * sin(f);
		glVertex3f(x, y,0); // ������ �������� �� �ϳ��ϳ��� ����ϴ� ���̴� 
	}
	glEnd();
}

void ellipse(vector3D center, float width, float height) // �� 
{
	float x, y;

	glBegin(GL_POLYGON);
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 36.0)
	{
		x = center.x + width * cos(f);  // ������ ��ſ� width
		y = center.y + height * sin(f); // ������ ��ſ� height
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