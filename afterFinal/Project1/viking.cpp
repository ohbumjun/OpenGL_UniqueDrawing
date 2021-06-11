/*

#include "cg.h"
#include "draw.h"

int w = 1000;
int h = 1000;
float t  = 0.0;
float tI = 0.01;

using namespace std;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.6, 0.6, 0.6, 1.0);
	// center
	glColor3f(1.0, 1.0, 1.0);
	circle(vector3D(0, 0, 0), 0.1);
	glPushMatrix();
		line(vector3D(0.5, -0.5, 0), vector3D(-0.5, -0.5, 0));
		line(vector3D(0.0, 0.0, 0), vector3D(-0.5, -0.5, 0));
		line(vector3D(0.0, 0.0, 0), vector3D(0.5, -0.5, 0));
	glPopMatrix();

	

	// boat center
	glPushMatrix(); // ���⼭ push,pop�� ���ϸ�, �Ʒ��� transformation�� ���� sun���� ��� ����Ǿ� ������
	glRotatef(3.0 * t, 0.0, 0.0, 1.0); // ���� z�� �߽� ȸ����Ű��
	line(vector3D(0,0,0), vector3D(0,-0.4,0));
	glTranslatef(0.0, -0.4, 0.0);  //instancing --> �켱 �¾����κ��� �������� �����س��´�
	glColor3f(0.0, 0.0, 1.0);
	ellipse(vector3D(0,0,0),0.1,0.05);

	// boat right
	glPushMatrix();
		glRotatef(-15, 0.0, 0.0, 1.0); // instancing  : ���⼱��
		glTranslatef(-0.2, 0.0, 0.0);   // instancing  : ��ġ����
		ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPushMatrix();
			glRotatef(-15, 0.0, 0.0, 1.0); // instancing  : ���⼱��
			glTranslatef(-0.2, 0.0, 0.0);   // instancing  : ��ġ����
			ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPopMatrix();
	glPopMatrix();

	// boat left
	glPushMatrix();
		glRotatef(15, 0.0, 0.0, 1.0); // instancing  : ���⼱��
		glTranslatef(0.2, 0.0, 0.0);   // instancing  : ��ġ����
		ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPushMatrix();
			glRotatef(15, 0.0, 0.0, 1.0); // instancing  : ���⼱��
			glTranslatef(0.2, 0.0, 0.0);   // instancing  : ��ġ����
			ellipse(vector3D(0, 0, 0), 0.1, 0.05);
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void idle()
{
	t += tI;
	if (t <= -20|| t >= 20) tI *= -1;
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