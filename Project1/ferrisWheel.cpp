/*
#include "cg.h"
#include "draw.h"

int w = 1000;
int h = 1000;
float t = 0.0;

using namespace std;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.6, 0.6, 0.6, 1.0);

	// sun
	glColor3f(1.0, 1.0, 0.0);
	circle(vector3D(0, 0, 0), 0.1);
	glPushMatrix();
	line(vector3D(0.8, -0.8, 0), vector3D(-0.8, -0.8, 0));
	line(vector3D(0.0, 0.0, 0), vector3D(-0.8, -0.8, 0));
	line(vector3D(0.0, 0.0, 0), vector3D(0.8, -0.8, 0));
	glPopMatrix();

	//earth
	float cx = 0.0, cy = 0.0, radius = 0.6;
	float px = 0.0, pmx = 0.0;
	float py = 0.0, pmy = 0.0;
	for (float f = 0.0; f < 2 * M_PI; f += M_PI / 6.0) // 6.0 ���� �����ٴ� ���� 60�� ������Ų�� --> 12�� �׷����� 
	{
		// ���� ��Ÿ���� ���� : x^2  + y^2 = r^2
		// parametric ���� : X = r * cos (f) -> f: ���� ( 0 ~ 360 )
		// parametric ���� : Y = r * sin (f) -> f: ���� 
		px = cx + radius * cos(f);
		py = cx + radius * sin(f);
		// RT �� TR �� ���� ����� ��
		glPushMatrix(); // ���⼭ push,pop�� ���ϸ�, �Ʒ��� transformation�� ���� sun���� ��� ����Ǿ� ������
		glRotatef(3.0 * t, 0.0, 0.0, 1.0); // ���� z�� �߽� ȸ����Ű��
		line(vector3D(cx, cy, 0), vector3D(px, py, 0));
		glTranslatef(px, py, 0.0);  //instancing --> �켱 �¾����κ��� �������� �����س��´�
		glColor3f(0.0, 0.0, 1.0);
		circle(vector3D(0, 0, 0), 0.05);

		//moon
		for (float f = 0.0; f < 2 * M_PI; f += M_PI / 45) // 6.0 ���� �����ٴ� ���� 60�� ������Ų�� --> 12�� �׷����� 
		{
			glPushMatrix(); // --> ������ ���õ� x,y,z �� �����Ͽ� transformation�� �̷���� ���̴�
			glColor3f(1.0, 0.0, 1.0);
			glRotatef(5 * t, 0.0, 0.0, 1.0);
			pmx = cx + (radius / 4) * cos(f);
			pmy = cx + (radius / 4) * sin(f);
			line(vector3D(cx, cy, 0), vector3D(pmx, pmy, 0));
			glTranslatef(pmx, pmy, 0.0);// instancing
			rect(vector3D(-0.01, 0.02, 0), vector3D(0.01, -0.02, 0));
			glPopMatrix();

		}
		glPopMatrix();
	}

	glutSwapBuffers();
}

void idle()
{
	t += 0.01;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutCreateWindow("transformations");

	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
}

*/

